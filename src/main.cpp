#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>
#include <sstream>
#include <csignal>
#include <cstring>
#include <thread>
#include <chrono>
#include <string>
#include <atomic>

#include "socket.hpp"
#include "utils.hpp"
#include "db.hpp"

using namespace std;

atomic<bool> stopFlag(false);

int main() {
    signal(SIGINT, handleSignal);
    signal(SIGTERM, handleSignal);

    string host = "localhost";
/* 
/!\ NEVER USE A PUBLIC DESTINATION DIRECTLY WITH THIS PROGRAM
IT'S NOT SECURE AT ALL, ALL OF DATA SENT ISN'T ENCRYPTED, 
CONSIDER TO USE SSH OR VPN TUNNEL /!\ 
*/

    int port = 25575;
    string password = "Bonjour";

    Database db("localhost", "user", "password", "db");
    if (!db.connect()) {
        cerr << "Impossible de se connecter à la base de données.\n";
        return 1;
    }

    map<string, bool> previousState;
    
    while (!stopFlag) {
        int sock = -1;

        // Connexion + auth with retry
        while (!stopFlag) {
            sock = initSocket(host, port);
            sendPacket(sock, 1, 3, password);
            string authResponse = readPacket(sock);

            if (!authResponse.empty())
                break;

            cerr << "Échec auth, retry dans 3s...\n";
            close(sock);
            sleep(3);
        }

        cout << "Authentification réussie.\n";

        while (!stopFlag) {
            auto users = db.getPlayers();

            for (const auto& u : users) {
                auto it = previousState.find(u.pseudonym);


                bool changed = (it == previousState.end()) || (it->second != u.whitelisted);
                if (changed) {
                    string cmd = u.whitelisted
                        ? "whitelist add " + u.pseudonym
                        : "whitelist remove " + u.pseudonym;

                    cout << "Envoi : " << cmd << "\n";
                    sendPacket(sock, 4, 2, cmd);
                    string response = readPacket(sock);

                    if (response.empty()) {
                        cerr << "Connexion perdue, reconnexion...\n";
                        close(sock);
                        goto reconnect; // exit of to loops and retry connection
                    }
                    
                    previousState[u.pseudonym] = u.whitelisted;
                }
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }

        reconnect: ;
    }

    return 0;
}