#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>
#include <vector>

void handleSignal(int signal);
std::string sendCommand(int sock, const std::string &cmd);
std::vector<std::string> getWhitelistedPlayers(int sock);
bool isValidMinecraftUsername(const std::string &username);
bool addPlayerToWhitelist(int sock, const std::string &username);

#endif // UTILS_HPP
