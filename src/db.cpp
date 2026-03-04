#include <mysql_driver.h>
#include <iostream>

#include "db.hpp"

Database::Database(const std::string& host, int port, const std::string& user,
                   const std::string& password, const std::string& dbname)
    : host(host), port(port), user(user), password(password), dbname(dbname),
      driver(nullptr), con(nullptr) {}

Database::~Database() {
    disconnect();
}

bool Database::connect() {
    try {
        driver = sql::mysql::get_driver_instance();
        con = driver->connect("tcp://" + host + ":" + std::to_string(port), user, password);
        con->setSchema(dbname);
        std::cout << "Connecté à la base de données.\n";
        return true;
    } catch (sql::SQLException& e) {
        std::cerr << "Erreur DB : " << e.what() << "\n";
        return false;
    }
}

void Database::disconnect() {
    if (con) {
        delete con;
        con = nullptr;
        std::cout << "Déconnecté de la base de données.\n";
    }
}

bool Database::isConnected() const {
    return con != nullptr;
}

std::vector<Player> Database::getPlayers() {
    std::vector<Player> players;

    try
    {
        sql::Statement* stmt = con->createStatement();
        sql::ResultSet* res = stmt->executeQuery("SELECT pseudonym, whitelisted FROM users");

        while (res->next()) {
            Player p;
            p.pseudonym = res->getString("pseudonym");
            p.whitelisted = res->getBoolean("whitelisted");
            players.push_back(p);
        }

        delete res;
        delete stmt;
    }
    catch(const std::exception& e)
    {
        std::cerr << "Erreur lors de la récupération des utilisateurs" << e.what() << '\n';
    }
    return players;
    
}