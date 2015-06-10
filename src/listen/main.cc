#include "boost/asio/io_service.hpp"

#include <string>
#include <iostream>

#include "common/client.h"
#include "common/jsonxx.h"

#include "config/config.h"

class Formatter {
public:
  static void to_json(std::string data) {
    std::cout << data << std::endl;
  };

  static void to_table(std::string data) {
    static int title = 0;
    if (title == 0) {
      title++;
      std::cout << "|ticker|bid|ask|bidqty|askqty|last|turnover|" << std::endl;
    }

    jsonxx::Object o;
    auto ret = o.parse(data);

    auto ticker   = o.get<jsonxx::String>("ticker", "");
    auto bidqty   = o.get<jsonxx::Number>("bid_qty", 0);
    auto askqty   = o.get<jsonxx::Number>("ask_qty", 0);
    auto bid      = std::atof(o.get<jsonxx::String>("bid_price", "0").c_str());
    auto ask      = std::atof(o.get<jsonxx::String>("ask_price", "0").c_str());
    auto last     = std::atof(o.get<jsonxx::String>("last", "0").c_str());
    auto turnover = std::atof(o.get<jsonxx::String>("turnover", "0").c_str());
    std::cout << "\r" << ticker << "|" << bid << "|" << ask << "|" << bidqty << "|" << askqty << "|" << last << "|" << turnover << "|" << std::flush;
  };
};

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
    jsonxx::Object obj;
    if (!obj.parse(data)) {
      std::cout << "wrong json format order received"<< std::endl;
      return;
    }

    auto req = obj.get<jsonxx::String>("type", "");
    if (req == "quote") {
      if (format == 1) {
        Formatter::to_json(data);
      } else if (format == 2) {
        Formatter::to_table(data);
      }
    } else if (req == "order") {
      std::cout << "order update: " << data << std::endl;
    } else if (req == "trade") {
      std::cout << "trade update: " << data << std::endl;
    }
  });

  client.connect();

  auto str = obj.json();
  str.erase(std::remove(str.begin(), str.end(), '\n'), str.end());
  client.write(str);

  io_service.run();

  return 0;
}
