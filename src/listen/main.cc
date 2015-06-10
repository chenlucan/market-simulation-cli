#include "boost/asio/io_service.hpp"

#include <string>
#include <iostream>

#include "common/client.h"
#include "common/jsonxx.h"

#include "config/config.h"

int main(int argc, char* argv[]) {
  config::Config config;
  std::string operation = "", option = "";
  if (argc >= 2) {
    operation = argv[1];
    if (argc > 2) {
      option = argv[2];
    }
  }

  if (argc < 2 || (operation != "markets" && operation != "orders"  && operation != "trades")) {
    std::cout << "Usage: listen [markets[--current]|orders|trades]" << std::endl;
    return 1;
  }

  jsonxx::Object obj;
  auto tree = config.get_tree();
  auto port   = tree.get("port",   9000);
  auto ticker = tree.get("ticker", "");
  auto format = 1;
  if (option == "--current") {
    format = 2;
  }
  if (operation == "markets") {
    obj << "type"   << "markets";
    obj << "ticker" << ticker;
  } else if (operation == "orders") {
    obj << "type" << "orders";
    obj << "account" << option;
  } else if (operation == "trades") {
    obj << "type" << "trades";
    obj << "account" << option;
  }


  boost::asio::io_service io_service;
  common::Client client(io_service, "127.0.0.1", port, [=] (std::string data) {
    if (format == 1) {
      // json format
    } else if (format == 2) {
      // table format
    }
  });
  client.connect();

  io_service.run();

  return 0;
}
