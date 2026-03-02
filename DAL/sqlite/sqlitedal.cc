#include "sqlitedal.hpp"


namespace cppgoat::DAL
{

    SqliteDAL::SqliteDAL() : _db(NULL)
    {
      auto result = sqlite3_open_v2("users.db", &_db, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE | SQLITE_OPEN_FULLMUTEX, NULL);

      auto x = result == SQLITE_OK;
      int y = 0;
    }

    SqliteDAL::~SqliteDAL()
    {
      sqlite3_close_v2(_db);
    }

    bool SqliteDAL::ValidateLogin(const std::string& username, const std::string& password)
    {

      return false;
    }
    
    bool SqliteDAL::CreateUser(const std::string& username, const std::string& password)
    {
      return false;
    }

}