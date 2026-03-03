#include "socket.hpp"
#include <string>
#include <vector>
#include <csignal>
#include <iostream>

using namespace std;

vector<string> getWhitelistedPlayers(int sock) {
    sendPacket(sock, 4, 2, "whitelist list");
    string response = readPacket(sock);
    vector<string> players;
    //size_t colonPos = response.find(":");

    return players;
}

void handleSignal(int signal) {
    if (signal == SIGINT) {
        cout << "Interrupt signal received. Exiting..." << endl;
        exit(0);
    } else if (signal == SIGTERM) {
        cout << "Termination signal received. Exiting..." << endl;
        exit(0);
    }
}

string sendCommand(int sock, const string &cmd) {
    sendPacket(sock, 5, 2, cmd);
    return readPacket(sock);
}

bool isValidMinecraftUsername(const string &username) {
    if (username.length() < 3 || username.length() > 16) return false;
    for (char c : username) {
        if (!isalnum(c) && c != '_') return false;
    }
    return true;
}

bool addPlayerToWhitelist(int sock, const string &username) {
    if (!isValidMinecraftUsername(username)) {
        cerr << "Invalid Minecraft username: " << username << endl;
        return false;
    }
    string command = "whitelist add " + username;
    string response = sendCommand(sock, command);

    return response.find("Added") != string::npos;
}