#include "socket.hpp"
#include <iostream>
#include <string>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>

using namespace std;

struct RconPacket {
    int32_t size;
    int32_t id;
    int32_t type;
    string body;

    string serialize() {
        int32_t body_len = body.size();
        int32_t size_le = body_len + 10; // id(4) + type(4) + body + 2 null bytes

        string packet;
        packet.resize(4 + size_le);

        memcpy(&packet[0], &size_le, 4);
        memcpy(&packet[4], &id, 4);
        memcpy(&packet[8], &type, 4);
        memcpy(&packet[12], body.c_str(), body_len);

        packet[12 + body_len] = 0;
        packet[13 + body_len] = 0;

        return packet;
    }
};

int sendPacket(int sock, int id, int type, const string &cmd) {
    RconPacket p{0, id, type, cmd};
    string data = p.serialize();
    return send(sock, data.data(), data.size(), 0);
}

string readPacket(int sock) {
    char buffer[4096];
    int bytes = recv(sock, buffer, sizeof(buffer), 0);
    if (bytes <= 0) return "";
    return string(buffer, bytes);
}

int initSocket(string host, int port) {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0)
    {   
        cerr << "Erreur : Impossible de créer le socket.\n";
        return -1;
    }
    
    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);

    if (inet_pton(AF_INET, host.c_str(), &addr.sin_addr) <= 0)
    {
        cerr << "Erreur : Adresse IP invalide.\n";
        close(sock);
        return -1;
    }

    if (connect(sock, (sockaddr*)&addr, sizeof(addr)) < 0)
    {
        cerr << "Erreur : Impossible de se connecter au serveur.\n";
        close(sock);
        return -1;
    }

    cout << "Connexion TCP établie avec succès à " << host << ":" << port << ".\n";
    return sock;
}