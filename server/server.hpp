#ifndef __SERVER_HPP__
#define __SERVER_HPP__

#include <string>
#include <filesystem>
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
    std::filesystem::path _content;
    

    bool is_logged_in(const httplib::Request &req);

    void handle_file_request(const httplib::Request &req, httplib::Response &res);
    void handle_login_request(const httplib::Request &req, httplib::Response &res);
    void handle_create_user_request(const httplib::Request &req, httplib::Response &res);
    void handle_urlencode_request(const httplib::Request &req, httplib::Response &res);
    bool redirecting_authenticated_user(const httplib::Request &req, httplib::Response &res);
    bool is_authenticated(const httplib::Request &req);

    void log(const httplib::Request &req, const httplib::Response &res);
    void log(const httplib::Error& err, const httplib::Request* req);

    std::string get_request_log_str(const httplib::Request* req);
    std::string get_response_log_str(const httplib::Response &res);


    public:
    GoatServer(cppgoat::DAL::IUserAccountDAL* dal, int listen_port, std::string content_path, const char* interface);
    GoatServer(cppgoat::DAL::IUserAccountDAL* dal, int listen_port, std::string content_path);

    void serve_forever();

  };


}

#endif
