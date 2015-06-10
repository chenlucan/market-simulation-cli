#ifndef CONFIG_CONFIG_H
#define CONFIG_CONFIG_H

#include "boost/property_tree/json_parser.hpp"
#include "boost/property_tree/ptree_fwd.hpp"

#include <string>

#include "config/fwd.h"

namespace config {

class Config {
public:
  Config(std::string filename = "src/config/config.json");

  virtual ~Config();

  bp::ptree get_tree();

private:
  std::string filename_;
};

}
#endif  // CONFIG_CONFIG_H
