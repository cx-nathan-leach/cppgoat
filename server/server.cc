#include "server.hpp"
#include <iostream>
#include <chrono>
#include "jwt/jwt.hpp"

namespace cppgoat::server
{

  GoatServer::GoatServer(cppgoat::DAL::IUserAccountDAL* dal, int listen_port, std::string content_path, const char* interface) :
    _dal(dal), _port(listen_port), _interface(interface), _content(content_path)
  {

    _svr.Get("/login", [&](const auto &req, auto &res){
      if (!this->redirecting_authenticated_user(req, res))
      {
        auto path = std::filesystem::path(_content) /= "login.html";
        res.set_file_content(path);
      }
    });

    _svr.Get("/create", [&](const auto &req, auto &res){
      if (!this->redirecting_authenticated_user(req, res))
      {
        auto path = std::filesystem::path(_content) /= "create.html";
        res.set_file_content(path);
      }
    });

    _svr.Get("/app", [&](const auto &req, auto &res){
      // auto path = std::filesystem::path(_content) /= "create.html";
      // res.set_file_content(path);
      if (!this->is_authenticated(req))
        res.set_redirect("/login");
      else
        res.set_content("APP PLACEHOLDER", "text/plain");
    });

    _svr.Get("/logout", [&](const auto &req, auto &res){
      res.set_header("Set-Cookie", std::string("auth_token=; expires=Thu, 01 Jan 1970 00:00:00 UTC;"));
      res.set_redirect("/login");
    });



    _svr.Post("/login", [&](const auto &req, auto &res){
      this->handle_login_request(req, res);
    });

    _svr.Post("/create", [&](const auto &req, auto &res){
      this->handle_create_user_request(req, res);
    });


    _svr.Get(R"(/(.*))", [&](const auto &req, auto &res){
      this->handle_file_request(req, res);
    });

    _svr.set_logger([&](const auto &req, const auto &res){
      this->log(req, res);
    });

    _svr.set_pre_compression_logger([&](const auto &req, const auto &res){
      this->log(req, res);
    });

    _svr.set_error_logger([&](const auto& err, const auto* req){
      this->log(err, req);
    });

  }

  GoatServer::GoatServer(cppgoat::DAL::IUserAccountDAL* dal, int listen_port, std::string content_path) : 
    GoatServer(dal, listen_port, content_path, "0.0.0.0")
  {

  }
  
  bool GoatServer::is_authenticated(const httplib::Request &req)
  {
    auto cookies = req.get_header_value("Cookie");

    return false;
  }

  bool GoatServer::redirecting_authenticated_user(const httplib::Request &req, httplib::Response &res)
  {

    if (is_authenticated(req))
    {
      res.set_redirect("/app");
      return true;
    }

    return false;
  }
  
  std::string GoatServer::get_request_log_str(const httplib::Request* req)
  {
    return req->method + " " + req->path;
  }

  std::string GoatServer::get_response_log_str(const httplib::Response &res)
  {
    return res.status + " " + res.reason;
  }

  void GoatServer::log(const httplib::Request &req, const httplib::Response &res)
  {
    using namespace std;
    cout << "INFO " << get_request_log_str(&req) << endl;
  }

  void GoatServer::log(const httplib::Error& err, const httplib::Request* req)
  {
    using namespace std;
    cerr << "ERROR " << get_request_log_str(req) << ": " << err << endl;
  }

  void GoatServer::serve_forever()
  {
    _svr.listen(_interface, _port);
  }

  void GoatServer::handle_file_request(const httplib::Request &req, httplib::Response &res)
  {
    auto path = std::filesystem::path(_content) += req.path;

    if (!path.has_filename())
      path += "index.html";

    res.set_file_content(path);
  }

  void GoatServer::handle_login_request(const httplib::Request &req, httplib::Response &res)
  {
    auto email = req.get_param_value("email");
    auto password = req.get_param_value("password");

    if (_dal->ValidateLogin(email, password))
    {
      _dal->LoadUser(email);
      using namespace jwt::params;

      jwt::jwt_object obj{algorithm("HS256"), payload({
        {"username", _dal->LoadUser(email)},
        {"password", password},
        {"email", email}
      }), secret("x%jL*1")};
      obj.add_claim("iss", "cppgoat");
      obj.add_claim("authenticated", "true");

      res.set_header("Set-Cookie", std::string("auth_token=") + obj.signature());
      res.set_header("X-Goat", std::string("BAAAAAAH"));
      res.set_redirect(std::string("/app") );
    }
    else
      res.set_redirect(std::string("login?msg=Login failed for user id ") + email);
  }

  void GoatServer::handle_create_user_request(const httplib::Request &req, httplib::Response &res)
  {
    auto email = req.get_param_value("email");
    auto password = req.get_param_value("password");
    auto username = req.get_param_value("username");

    try
    {
      if (_dal->CreateUser(email, username, password))
        res.set_redirect(std::string("login?msg=Log in permitted for user id ") + email + " with password " + password);
      else
        res.set_redirect(std::string("login?msg=User id ") + email + " was not created");
    }
    catch(cppgoat::DAL::DALException ex)
    {
      res.set_content(ex.what(), "text/plain");
      res.status = httplib::StatusCode::BadRequest_400;
    }
  }

  void GoatServer::handle_urlencode_request(const httplib::Request &req, httplib::Response &res)
  {

  }


}
