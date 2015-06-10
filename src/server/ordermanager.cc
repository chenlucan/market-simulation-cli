#include "server/ordermanager.h"

namespace server {

OrderManager::OrderManager() : id_(), bid_{}, ask_{} {}

OrderManager::~OrderManager() {}

Order OrderManager::AddOrder(std::string account, double price, int quantity, std::string ticker, OrderSide os) {
  Order order(id_++, account);
  order.price     = price;
  order.quantity  = quantity;
  order.ticker    = ticker;
  order.side      = os;
  order.status    = OrderStatus::OS_Working;

  if (os == OrderSide::OS_Buy) {
    bid_.insert(std::pair<int, Order>(order.id, order));
  } else {
    ask_.insert(std::pair<int, Order>(order.id, order));
  }

  return order;
}

void OrderManager::RemoveOrder(int id) {
  bid_.erase(id);
  ask_.erase(id);
}

std::vector<Order> OrderManager::RemoveBidAbove(double price, std::string ticker) {
  std::vector<Order> orders;
  for(auto it = bid_.begin(); it != bid_.end(); ) {
    if (it->second.price >= price && it->second.ticker == ticker) {
      orders.push_back(it->second);
      it = bid_.erase(it);
    } else {
      ++it;
    }
  }
  return orders;
}

std::vector<Order> OrderManager::RemoveAskBelow(double price, std::string ticker) {
  std::vector<Order> orders;
  for(auto it = ask_.begin(); it != ask_.end(); ) {
    if (it->second.price <= price && it->second.ticker == ticker) {
      orders.push_back(it->second);
      it = ask_.erase(it);
    } else {
      ++it;
    }
  }
  return orders;
}

}
