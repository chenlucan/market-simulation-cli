#ifndef SERVER_CONNECTIONMANAGER_H
#define SERVER_CONNECTIONMANAGER_H

#include <map>

#include "server/connection.h"

namespace server {

/// Manages open connections so that they may be cleanly stopped when the server
/// needs to shut down.
class ConnectionManager {
public:
  ConnectionManager(const ConnectionManager&) = delete;
  ConnectionManager& operator=(const ConnectionManager&) = delete;

  /// Construct a connection manager.
  ConnectionManager();

  /// Add the specified connection to the manager and start it.
  void Start(connection_ptr c);

  /// Stop the specified connection.
  void Stop(connection_ptr c);

  /// Stop all connections.
  void StopAll();

  void Publish(std::string name, std::string data);

private:
  /// The managed connections.
  std::map<std::string, connection_ptr> connections_;
};

}
#endif // SERVER_CONNECTIONMANAGER_H
