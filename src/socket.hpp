#ifndef SOCKET_HPP
#define SOCKET_HPP

#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

int sendPacket(int sock, int id, int type, const std::string &cmd);
std::string readPacket(int sock);
int initSocket(std::string host, int port);

#endif // SOCKET_HPP