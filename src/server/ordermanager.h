#ifndef SERVER_ORDEROOOK_H
#define SERVER_ORDEROOOK_H

#include <map>
#include <vector>

#include "server/message.h"

namespace server {

class OrderManager {
public:
  OrderManager();
  virtual ~OrderManager();

  Order AddOrder(std::string account, double price, int quantity, std::string ticker, OrderSide os);
  void RemoveOrder(int id);
  std::vector<Order> RemoveBidAbove(double price, std::string ticker);
  std::vector<Order> RemoveAskBelow(double price, std::string ticker);

private:
  int id_;
  std::map<int, Order> bid_;
  std::map<int, Order> ask_;
};

}
#endif  // SERVER_ORDEROOOK_H
