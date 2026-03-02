#include <memory>
#include "httplib.h"
#include "argparse/argparse.hpp"
#include "DAL/dalfactory.hpp"


std::shared_ptr<argparse::ArgumentParser> get_args(int argc, char** argv)
{
  auto parser = std::make_shared<argparse::ArgumentParser>("cppgoat");
  
  parser->add_argument("-p", "--port")
    .help("The listening port for the server.")
    .default_value<int>({8080});

  parser->parse_args(argc, argv);

  return parser;
}


int main(int argc, char** argv)
{
  auto args = get_args(argc, argv);

  auto dal_ptr = cppgoat::DAL::GetDALInstance();

  httplib::Server svr;

  svr.Get("/hi", [](const httplib::Request &, httplib::Response &res) {
    res.set_content("Hello World!", "text/plain");
  });

  svr.listen("0.0.0.0", args->get<int>("port"));

  return 0;
}
