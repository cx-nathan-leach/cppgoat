#ifndef __SERVER_HPP__
#define __SERVER_HPP__

#include "user_dal.hpp"
#include "httplib.h"


namespace cppgoat::server
{
  class GoatServer
  {
    private:
    
    httplib::Server _svr;

    int _port;
    const char* _interface;
    cppgoat::DAL::IUserAccountDAL* _dal;

    public:
    GoatServer(cppgoat::DAL::IUserAccountDAL* dal, int listen_port, const char* interface);
    GoatServer(cppgoat::DAL::IUserAccountDAL* dal, int listen_port);

    void serve_forever();

  };


}

#endif
