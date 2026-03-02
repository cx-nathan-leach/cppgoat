#include "dalfactory.hpp"
#include "sqlitedal.hpp"

namespace cppgoat::DAL
{
  std::shared_ptr<IUserAccountDAL> GetDALInstance()
  {
    return std::make_shared<SqliteDAL>();
  }
}