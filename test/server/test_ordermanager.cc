#include "gtest/gtest.h"

#include "server/ordermanager.h"

namespace server {

TEST(OrderManagerTest, should_assign_unique_order_id) {
  OrderManager manager;

  auto order1 = manager.AddOrder("account1", 100, 5, "1234", OrderSide::OS_Buy);
  auto order2 = manager.AddOrder("account1", 200, 5, "1234", OrderSide::OS_Sell);

  EXPECT_NE(order1.id, order2.id);
}

TEST(OrderManagerTest, should_remove_order_by_id) {
  OrderManager manager;

  auto order1 = manager.AddOrder("account1", 100, 5, "1234", OrderSide::OS_Buy);
  auto order2 = manager.AddOrder("account1", 200, 5, "1234", OrderSide::OS_Sell);

  manager.RemoveOrder(order1.id);
  manager.RemoveOrder(order2.id);

  auto bid = manager.RemoveBidAbove(100, "1234");
  auto ask = manager.RemoveAskBelow(200, "1234");

  EXPECT_EQ(0, bid.size());
  EXPECT_EQ(0, ask.size());
}

TEST(OrderManagerTest, should_remove_order_by_price) {
  OrderManager manager;

  auto order1 = manager.AddOrder("account1", 100, 5, "1234", OrderSide::OS_Buy);
  auto order2 = manager.AddOrder("account1", 110, 5, "1234", OrderSide::OS_Buy);
  auto order3 = manager.AddOrder("account1", 120, 5, "1234", OrderSide::OS_Buy);
  auto order4 = manager.AddOrder("account1", 130, 5, "1234", OrderSide::OS_Buy);
  auto order5 = manager.AddOrder("account1", 140, 5, "1234", OrderSide::OS_Buy);

  auto order6  = manager.AddOrder("account1", 200, 5, "1234", OrderSide::OS_Sell);
  auto order7  = manager.AddOrder("account1", 210, 5, "1234", OrderSide::OS_Sell);
  auto order8  = manager.AddOrder("account1", 220, 5, "1234", OrderSide::OS_Sell);
  auto order9  = manager.AddOrder("account1", 230, 5, "1234", OrderSide::OS_Sell);
  auto order10 = manager.AddOrder("account1", 240, 5, "1234", OrderSide::OS_Sell);

  auto order11 = manager.AddOrder("account1", 100, 5, "4321", OrderSide::OS_Buy);
  auto order12 = manager.AddOrder("account1", 110, 5, "4321", OrderSide::OS_Buy);
  auto order13 = manager.AddOrder("account1", 120, 5, "4321", OrderSide::OS_Buy);
  auto order14 = manager.AddOrder("account1", 130, 5, "4321", OrderSide::OS_Buy);
  auto order15 = manager.AddOrder("account1", 140, 5, "4321", OrderSide::OS_Buy);

  auto order16 = manager.AddOrder("account1", 200, 5, "4321", OrderSide::OS_Sell);
  auto order17 = manager.AddOrder("account1", 210, 5, "4321", OrderSide::OS_Sell);
  auto order18 = manager.AddOrder("account1", 220, 5, "4321", OrderSide::OS_Sell);
  auto order19 = manager.AddOrder("account1", 230, 5, "4321", OrderSide::OS_Sell);
  auto order20 = manager.AddOrder("account1", 240, 5, "4321", OrderSide::OS_Sell);

  auto opt1 = manager.RemoveBidAbove(120, "1234");
  auto opt2 = manager.RemoveAskBelow(220, "1234");
  auto opt3 = manager.RemoveBidAbove(1000, "4321");
  auto opt4 = manager.RemoveAskBelow(10,   "4321");

  EXPECT_EQ(3, opt1.size());
  EXPECT_EQ(3, opt2.size());
  EXPECT_EQ(0, opt3.size());
  EXPECT_EQ(0, opt4.size());

  auto opt5 = manager.RemoveBidAbove(0,    "1234");
  auto opt6 = manager.RemoveAskBelow(1000, "1234");
  auto opt7 = manager.RemoveBidAbove(0, "4321");
  auto opt8 = manager.RemoveAskBelow(1000,   "4321");

  EXPECT_EQ(2, opt5.size());
  EXPECT_EQ(2, opt6.size());
  EXPECT_EQ(5, opt7.size());
  EXPECT_EQ(5, opt8.size());
}

}
