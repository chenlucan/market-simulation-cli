#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "server/submanager.h"
#include "server/mockconnectionmanager.h"

namespace server {

TEST(SubManagerTest, should_publish_events_according_to_subscriptions) {
  MockConnectionManager connection_manager;
  SubManager manager(&connection_manager);

  auto k1 = "k1", k2 = "k2", k3 = "k3", n1 = "n1", n2 = "n2", n3 = "n3", n4 = "n4";
  manager.Subscribe(k1, n1);
  manager.Subscribe(k2, n2);
  manager.Subscribe(k1, n3);
  manager.Subscribe(k2, n3);
  manager.SubscribeAll(n4);

  auto data1 = "data1";
  EXPECT_CALL(connection_manager, Publish(n1, data1));
  EXPECT_CALL(connection_manager, Publish(n3, data1));
  EXPECT_CALL(connection_manager, Publish(n4, data1));
  manager.Publish(k1, data1);

  EXPECT_CALL(connection_manager, Publish(n2, data1));
  EXPECT_CALL(connection_manager, Publish(n3, data1));
  EXPECT_CALL(connection_manager, Publish(n4, data1));
  manager.Publish(k2, data1);

  manager.Subscribe(k3, n1);

  EXPECT_CALL(connection_manager, Publish(n1, data1));
  EXPECT_CALL(connection_manager, Publish(n4, data1));
  manager.Publish(k3, data1);

  manager.UnSubscribe(k3, n1);
  EXPECT_CALL(connection_manager, Publish(n4, data1));
  manager.Publish(k3, data1);
}

}
