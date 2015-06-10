#include "boost/asio/io_service.hpp"

#include <algorithm>
#include <iostream>
#include <string>
#include <thread>

#include "common/client.h"
#include "common/jsonxx.h"

#include "config/config.h"

std::vector<std::string> split(const std::string &s, char delim = ' ') {
  std::stringstream ss(s);
  std::vector<std::string> elems{};
  std::string item;
  while (std::getline(ss, item, delim)) {
      elems.push_back(item);
  }
  return elems;
}

int main(int argc, char* argv[]) {
  config::Config config;
  std::string operation = "";
  if (argc == 2) {
    operation = argv[1];
  }

  if (argc != 2 || operation != "oms") {
    std::cout << "Usage: connect oms" << std::endl;
    return 1;
  }

  std::string account = "";

  jsonxx::Object obj;
  auto port = config.get_tree().get("port", 9000);
  obj << "type" << "oms";

  boost::asio::io_service io_service;
  common::Client client(io_service, "127.0.0.1", port, [=, &account] (std::string data) {
    jsonxx::Object obj;
    if (!obj.parse(data)) {
      std::cout << "wrong json format order received"<< std::endl;
      return;
    }

    auto req = obj.get<jsonxx::String>("type", "");
    if (req == "account") {
      account = obj.get<jsonxx::String>("account", "");
      std::cout << "my account name is [" << account << "]" << std::endl;
    } else if (req == "order") {
      std::cout << "order update: " << data << std::endl;
    }
  });
  client.connect();

  auto str = obj.json();
  str.erase(std::remove(str.begin(), str.end(), '\n'), str.end());
  client.write(str);

  std::thread t([&] () {io_service.run();});

  std::string input = "";
  while (std::getline(std::cin, input)) {
    auto data = input;
    input = "";
    if (!data.empty()) {
      std::transform(data.begin(), data.end(), data.begin(), ::tolower);
      auto cmd = split(data);
      if (cmd.size() == 3) {
        jsonxx::Object json_format;
        if (cmd[0] == "buy") {
          json_format << "side" << "buy";
        } else if (cmd[0] == "sell") {
          json_format << "side" << "sell";
        } else {
          std::cerr << "Wrong format" << std::endl;
          continue;
        }

        json_format << "ticker" << cmd[1];

        auto pq = split(cmd[2], '@');
        if (pq.size() == 2) {
          int quantity = 0;
          quantity  = std::atoi(pq[0].c_str());

          json_format << "price"    << pq[1];
          json_format << "quantity" << quantity;
          json_format << "account"  << account;
          json_format << "type"     << "new_order";

          // this is multi line string, we need remvoe the inline \n
          auto str = json_format.json();
          str.erase(std::remove(str.begin(), str.end(), '\n'), str.end());

          client.write(str);
        } else {
          std::cerr << "Wrong format" << std::endl;
          continue;
        }
      }
    }
  }

  t.join();

  return 0;
}
