#include<memory>
#include "sqlitedal.hpp"

extern "C"
{
  __attribute__((visibility("default"))) cppgoat::DAL::IUserAccountDAL* GetDALInstance()
  {
    return new cppgoat::DAL::sqlite3::SqliteDAL();
  }

}


namespace cppgoat::DAL::sqlite3
{

    void SqliteDAL::throw_sqlite_err_msg(char* msg)
    {
        auto ex = DALException(msg != NULL ? msg : "SQLite error" );
        if (msg != NULL)
          sqlite3_free(msg);
        throw ex;
    }

    std::string SqliteDAL::quote(std::string unquoted)
    {
      return std::string("'") + unquoted + std::string("'");

    }


    SqliteDAL::SqliteDAL() : _db(NULL)
    {
      auto result = sqlite3_open_v2("users.db", &_db, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE | SQLITE_OPEN_FULLMUTEX, NULL);

      if (result != SQLITE_OK)
      {
        throw cppgoat::DAL::DALException(std::string("sqlite3_open_v2 failed: ") + std::to_string(result));
      }

      char* msg;
      result = sqlite3_exec(_db, CREATE_USERS_TABLE, NULL, NULL, &msg);

      if (result != SQLITE_OK)
        throw_sqlite_err_msg(msg);

    }

    SqliteDAL::~SqliteDAL()
    {
      sqlite3_close_v2(_db);
    }

    int SqliteDAL::validate_callback(void* password_out_ptr, int cols, char** col_vals, char** col_names)
    {
      auto password_out = reinterpret_cast<std::string*>(password_out_ptr);

      (*password_out) = col_vals[0];

      return SQLITE_OK;
    }


    bool SqliteDAL::ValidateLogin(const std::string& username, const std::string& password)
    {
      std::string sql_query = std::string("SELECT password FROM users WHERE username='") + 
        quote(username) + std::string(";");

      char* msg;

      std::string loaded_password;

      auto result = sqlite3_exec(_db, sql_query.c_str(), validate_callback, &loaded_password, &msg);

      if (result != SQLITE_OK)
        throw_sqlite_err_msg(msg);

      return password == loaded_password;
    }
    
    bool SqliteDAL::CreateUser(const std::string& username, const std::string& password)
    {
      std::string sql_query = std::string("INSERT INTO users (username, password) VALUES (") + 
        quote(username) + std::string(",") + quote(password) + std::string(");");

      char* msg;
      auto result = sqlite3_exec(_db, sql_query.c_str(), NULL, NULL, &msg);

      if (result != SQLITE_OK)
        throw_sqlite_err_msg(msg);
      
      return true;
    }

}