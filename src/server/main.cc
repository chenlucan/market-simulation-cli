#include "boost/asio/io_service.hpp"

#include "config/config.h"

#include "server/exchange.h"

int main() {
  boost::asio::io_service io_service;
  config::Config config;

  boost::asio::signal_set signals(io_service);
  signals.add(SIGINT);
  signals.add(SIGTERM);

  server::Exchange exchange(io_service, config.get_tree());
  exchange.Start();

  signals.async_wait([&](boost::system::error_code /*ec*/, int /*signo*/) {
    exchange.Stop();
  });

  io_service.run();

  return 0;
}
