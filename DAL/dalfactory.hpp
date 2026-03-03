#ifndef __DALFACTORY_HPP__
#define __DALFACTORY_HPP__
#include <memory>
#include "user_dal.hpp"

namespace cppgoat::DAL
{
  using dal_ptr = IUserAccountDAL*(*)();

  class DALFactory
  {

    public:

    static IUserAccountDAL* Load(std::string lib_path, std::string name);
    

  };

}

#endif