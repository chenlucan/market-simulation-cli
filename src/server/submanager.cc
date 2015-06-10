#include "server/submanager.h"

#include "boost/property_tree/ptree.hpp"

#include <iostream>

#include "server/connectionmanager.h"

namespace server {

SubManager::SubManager(ConnectionManager *sub_manager) : manager_(sub_manager) {}

SubManager::~SubManager() {}

void SubManager::SubscribeAll(std::string name) {
  std::vector<std::string> all_keys{};
  for (auto e : subs_) {
    all_keys.push_back(e.key);
  }
  for (auto e : all_keys) {
    Subscribe(e, name);
  }
}

void SubManager::Subscribe(std::string account_name, std::string connection_name) {
  auto& pair = bm::get<by_pair>(subs_);
  auto f_it = pair.find(boost::make_tuple(account_name, connection_name));
  if (f_it != pair.end()) {
    std::cerr << "Already subscribed account_name[" << account_name << "], connection_name[" << connection_name << "]" << std::endl;
    return;
  }

  auto it = subs_.insert(SubStruct(account_name, connection_name));
  if (!it.second) {
    std::cerr << "Failed to add new subscription account_name[" << account_name << "], connection_name[" << connection_name << "]" << std::endl;
    return;
  }
}

void SubManager::UnSubscribe(std::string account_name, std::string connection_name) {
  auto& pair = bm::get<by_pair>(subs_);
  auto it = pair.find(boost::make_tuple(account_name, connection_name));
  pair.erase(it);
}

void SubManager::Publish(std::string key, std::string data) {
  auto& pair = bm::get<by_pair>(subs_);
  auto cont_range = pair.equal_range(key);

  if (cont_range.first == cont_range.second) {
    return;
  }

  for (auto sit = cont_range.first; sit != cont_range.second; ++sit) {
    manager_->Publish(sit->name, data);
  }
}

}
