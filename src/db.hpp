#pragma once
#include <string>
#include <vector>
#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/statement.h>
#include <cppconn/resultset.h>
#include <cppconn/exception.h>

struct Player {
    std::string pseudonym;
    bool whitelisted;
};


class Database {
public:
    Database(const std::string& host, const std::string& user,
             const std::string& password, const std::string& dbname);
    ~Database();

    bool connect();
    void disconnect();
    bool isConnected() const;

    std::vector<Player> getPlayers();

private:
    std::string host, user, password, dbname;
    sql::mysql::MySQL_Driver* driver;
    sql::Connection* con;
};