#include "DbConnection.h"

DbConnection::DbConnection()
{
    // Подключение логирования ошибок
    this->mLogger = new Logger{"DB Connection"};

    // Создание базы данных в каталоге приложения
    this->mDbName = std::filesystem::current_path().string() + "/data.db";

    try
    {
        this->mDatabase = sqlite3pp::database(this->mDbName.c_str());
    }
    catch (const sqlite3pp::database_error& err)
    {
        mLogger->error(err.what());
        return;
    }

    this->initTable();
}

DbConnection::~DbConnection()
{
    this->mDatabase.disconnect();

    delete this->mLogger;
    this->mLogger = nullptr;
}


/**
 * Инициализация новой базы данных
 */
void DbConnection::initTable()
{
    // Создание таблиц в новой базе данных
    std::string sql = "create table if not exists user ("
                      "   id integer primary key autoincrement not null,"
                      "   age int,"
                      "   name text,"
                      "   weight real"
                      ");";

    sqlite3pp::command cmd(reinterpret_cast<sqlite3pp::database&>(this->mDatabase), sql.c_str());
    cmd.execute();
}


/**
 * Добавить пользователя в базу
 * @param user Пользователь
 */
void DbConnection::addUser(const DbItem& user)
{
    // inserts a new user record.
    // binds the fields to '?' .
    // note that only types allowed for bindings are :
    //      int ,long, long long, float, double
    //      string , u16string
    // sqlite3 only supports utf8 and utf16 strings, you should use std::string for utf8 and std::u16string for utf16.
    // note that u"my text" is a utf16 string literal of type char16_t * .
    std::string sql("insert into user (age, name, weight) values (?, ?, ?);");
    sqlite3pp::command cmd(this->mDatabase, sql.c_str());
    cmd.binder() <<user.age() <<user.name() <<user.weight();
    cmd.execute();
}

/**
 * ID последней вставленной записи
 * @return ID  записи
 */
long long DbConnection::lastInsertedId() const
{
    return this->mDatabase.last_insert_rowid();
}

/**
 * Получить список всех пользователей из таблицы БД
 * @return Список пользователей
 */
std::vector<DbItem> DbConnection::getUsers()
{
    std::vector<DbItem> result{};
    std::string sql("select id, age, name, weight from user;");
    sqlite3pp::query dbQuery(this->mDatabase, sql.c_str());

    for (auto v : dbQuery) {
        DbItem user{};
        std::string user_name;

        user.setId(v.get<int>(0));
        user.setAge(v.get<int>(1));
        user.setName(v.get<std::string>(2));
        user.setWeight(v.get<double>(3));

        result.push_back(user);
    }

    return result;
}
