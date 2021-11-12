#ifndef STL_DBCONNECTION_H
#define STL_DBCONNECTION_H

#include <string>
#include <filesystem>
#include <vector>

#include "Logger.h"
#include "sqlite3pp.h"
#include "DbItem.h"

class DbConnection
{
public:
    DbConnection();
    ~DbConnection();
    void addUser(const DbItem& user);
    [[nodiscard]] long long lastInsertedId() const;
    [[nodiscard]] std::vector<DbItem> getUsers();

private:
    void initTable();

    std::string mDbName;
    sqlite3pp::database mDatabase;
    Logger *mLogger;
};


#endif //STL_DBCONNECTION_H
