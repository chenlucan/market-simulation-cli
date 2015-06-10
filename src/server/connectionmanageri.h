#ifndef SERVER_CONNECTIONMANAGERI_H
#define SERVER_CONNECTIONMANAGERI_H

#include "server/connection.h"

namespace server {

class ConnectionManagerI {
public:
  ConnectionManagerI() {}
  virtual ~ConnectionManagerI() {};

  virtual void Start(connection_ptr c) = 0;
  virtual void Stop(connection_ptr c)  = 0;
  virtual void StopAll() = 0;
  virtual void Publish(std::string name, std::string data) = 0;
};

}
#endif // SERVER_CONNECTIONMANAGERI_H
