#include "connectionmanager.h"

namespace server {

ConnectionManager::ConnectionManager() {}

void ConnectionManager::Start(connection_ptr c)
{
  connections_.insert(std::pair<std::string, connection_ptr>(c->name(), c));
  c->Start();
}

void ConnectionManager::Stop(connection_ptr c)
{
  connections_.erase(c->name());
  c->Stop();
}

void ConnectionManager::StopAll()
{
  for (auto c: connections_) {
    c.second->Stop();
  }
  connections_.clear();
}

void ConnectionManager::Publish(std::string name, std::string data) {
  auto it = connections_.find(name);
  if (it != connections_.end()) {
    it->second->Send(data);
  }
}

}
