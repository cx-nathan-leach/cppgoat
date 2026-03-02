#include "sqlitedal.hpp"
#include "sqlite3.h"


namespace cppgoat::DAL
{

    SqliteDAL::SqliteDAL()
    {
      
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