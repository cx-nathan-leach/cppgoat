#ifndef __DALFACTORY_HPP__
#define __DALFACTORY_HPP__
#include <memory>
#include "user_dal.hpp"

namespace cppgoat::DAL
{
  std::shared_ptr<IUserAccountDAL> GetDALInstance();
}

#endif