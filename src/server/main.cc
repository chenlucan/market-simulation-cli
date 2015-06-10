#include "boost/asio/io_service.hpp"

#include "config/config.h"

#include "server/server.h"

int main() {
  boost::asio::io_service io_service;
  config::Config config;

  server::ConnectionManager manager;
  server::Server s("127.0.0.1", 9000, io_service, &manager, [](std::string, std::string){});
  s.Start();

  io_service.run();
  s.Stop();

  return 0;
}
