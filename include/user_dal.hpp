#ifndef __USER_DAL_H__
#define __USER_DAL_H__

#include<string>
#include<exception>

namespace cppgoat::DAL
{
  class DALException : public std::exception
  {
    private:

    std::string _what;

    public:

    DALException(std::string reason) : _what(reason)
    {
    }

    virtual const char* what() const noexcept
    {
      return _what.c_str();
    }
  };


  class DALLoadException : public DALException
  {
    public:
    DALLoadException(std::string reason) : DALException(reason)
    {
    }
  };


  class LoginFailedException : public DALException
  {
    public:
    LoginFailedException(std::string reason) : DALException(reason)
    {
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