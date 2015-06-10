#include "config/config.h"

#include <iostream>

namespace config {

Config::Config(std::string filename) : filename_(filename) {}

Config::~Config() {}

bp::ptree Config::get_tree() {
  bp::ptree p;
  boost::property_tree::json_parser::read_json(filename_, p);
  for (auto& e : p ) {
    std::cout << "Loading configuration, " << e.first << ": " << e.second.data() << std::endl;
  }
  return p;
};

}
