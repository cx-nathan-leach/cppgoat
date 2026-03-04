#ifndef __SQLITEDAL_HPP__
#define __SQLITEDAL_HPP__
#include "user_dal.hpp"
#include "sqlite3.h"

namespace cppgoat::DAL::sqlite3
{
  
  #define CREATE_USERS_TABLE \
    "CREATE TABLE IF NOT EXISTS users (email PRIMARY KEY, username, password)"

    class SqliteDAL : public cppgoat::DAL::IUserAccountDAL
  {
    private:
      ::sqlite3 *_db;

    static void throw_sqlite_err_msg(char* msg);
    static int validate_callback(void*, int, char**, char**);
    static int load_user_callback(void*, int, char**, char**);

    static std::string quote(std::string unquoted);

    public:
    SqliteDAL();

    virtual bool ValidateLogin(const std::string& email, const std::string& password);
    virtual bool CreateUser(const std::string& email, const std::string& username, const std::string& password);
    virtual std::string LoadUser(const std::string& email);
    virtual ~SqliteDAL();

  };

}

#endif