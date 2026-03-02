#ifndef __SQLITEDAL_HPP__
#define __SQLITEDAL_HPP__
#include "user_dal.hpp"
#include "sqlite3.h"

namespace cppgoat::DAL
{
  class SqliteDAL : public cppgoat::DAL::IUserAccountDAL
  {
    private:
      sqlite3 *_db;
    public:
    SqliteDAL();

    virtual bool ValidateLogin(const std::string& username, const std::string& password);
    virtual bool CreateUser(const std::string& username, const std::string& password);
    virtual ~SqliteDAL();

  };

}

#endif