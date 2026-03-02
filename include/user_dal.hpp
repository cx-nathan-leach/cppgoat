#ifndef __USER_DAL_H__
#define __USER_DAL_H__

#include<string>
#include<exception>

namespace cppgoat::DAL
{

  class LoginFailedException : std::exception
  {
    private:

    std::string _what;

    public:

    LoginFailedException(std::string& reason) : _what(reason)
    {
    }

    virtual const char* what() const noexcept
    {
      return _what.c_str();
    }


  };

  class IUserAccountDAL
  {
    public:
    virtual bool ValidateLogin(const std::string& username, const std::string& password)=0;
    virtual bool CreateUser(const std::string& username, const std::string& password)=0;
    virtual ~IUserAccountDAL() = default;

  };

}

#endif