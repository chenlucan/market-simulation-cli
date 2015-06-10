#include "boost/asio/io_service.hpp"

#include "config/config.h"

#include "server/server.h"

int main() {
  boost::asio::io_service io_service;
  config::Config config;

  server::Server s("127.0.0.1", 9000, io_service);
  s.Start();

  io_service.run();
  s.Stop();

  return 0;
}
