#ifndef SERVER_MOCKCONNECTIONMANAGER_H
#define SERVER_MOCKCONNECTIONMANAGER_H

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "server/connectionmanageri.h"

namespace server {

class MockConnectionManager : public ConnectionManagerI {
public:
  MockConnectionManager() {}
  virtual ~MockConnectionManager() {};

  MOCK_METHOD1(Start,   void(connection_ptr));
  MOCK_METHOD1(Stop,    void(connection_ptr));
  MOCK_METHOD0(StopAll, void());
  MOCK_METHOD2(Publish, void(std::string, std::string));
};

}
#endif // SERVER_MOCKCONNECTIONMANAGER_H
