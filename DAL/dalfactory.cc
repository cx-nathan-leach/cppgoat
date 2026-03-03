#include "dalfactory.hpp"
#include<filesystem>
#include <exception>
#include <dlfcn.h>

namespace cppgoat::DAL
{
    IUserAccountDAL* DALFactory::Load(std::string lib_path, std::string name)
    {
      auto libname = std::string("lib") + name + std::string("dal.so");
      auto load_path = std::filesystem::path(lib_path) /= std::filesystem::path(name) /= libname;
      auto handle = dlopen(load_path.c_str(), RTLD_NOW);

      if (handle == NULL)
        throw cppgoat::DAL::DALLoadException(std::string("Unable to load DAL from ") + load_path.c_str());

      auto func = dlsym(handle, "GetDALInstance");
      if (func == NULL)
        throw cppgoat::DAL::DALLoadException(std::string("Shared library doesn't implement the factory method."));

      return reinterpret_cast<dal_ptr>(func)();
    }

}