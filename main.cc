#include <memory>
#include "argparse/argparse.hpp"
#include "DAL/dalfactory.hpp"
#include "server/server.hpp"


std::shared_ptr<argparse::ArgumentParser> get_args(int argc, char** argv)
{
  auto parser = std::make_shared<argparse::ArgumentParser>("cppgoat");
  
  parser->add_argument("-p", "--port")
    .help("The listening port for the server.")
    .default_value<int>({8080});

  parser->add_argument("-d", "--dal")
    .help("The name of the database abstraction layer to load.")
    .default_value<std::string>({"sqlite"});
    
  parser->add_argument("-lp", "--load_path")
    .help("The root path for DALs.")
    .default_value<std::string>({"."});

  parser->parse_args(argc, argv);

  return parser;
}


int main(int argc, char** argv)
{
  auto args = get_args(argc, argv);
  auto dal_ptr = cppgoat::DAL::DALFactory::Load(args->get<std::string>("load_path"), args->get<std::string>("dal"));
  cppgoat::server::GoatServer server(dal_ptr, args->get<int>("port"));
  server.serve_forever();
  return 0;
}
