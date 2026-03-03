#include "server.hpp"



namespace cppgoat::server
{

  GoatServer::GoatServer(cppgoat::DAL::IUserAccountDAL* dal, int listen_port, const char* interface) :
    _dal(dal), _port(listen_port), _interface(interface)
  {

    // svr.Get("/hi", [](const httplib::Request &, httplib::Response &res) {
    //   res.set_content("Hello World!", "text/plain");
    // });


  }

  GoatServer::GoatServer(cppgoat::DAL::IUserAccountDAL* dal, int listen_port) : GoatServer(dal, listen_port, "0.0.0.0")
  {

  }

  void GoatServer::serve_forever()
  {
    _svr.listen(_interface, _port);
  }


}
