#include "server/util.h"

#include <algorithm>

#include "common/jsonxx.h"

namespace server {

std::string to_json(Order order) {
  jsonxx::Object obj;
  obj << "type"     << "order";
  obj << "id"       << order.id;
  obj << "account"  << order.account;
  obj << "price"    << std::to_string(order.price);
  obj << "quantity" << order.quantity;
  obj << "ticker"   << order.ticker;
  obj << "side"     << to_string(order.side);
  obj << "status"   << to_string(order.status);

  auto str = obj.json();
  str.erase(std::remove(str.begin(), str.end(), '\n'), str.end());
  return str;
}

std::string to_json(Trade trade) {
  jsonxx::Object obj;
  obj << "id"       << trade.id;
  obj << "orderid"  << trade.orderid;
  obj << "account"  << trade.account;
  obj << "price"    << std::to_string(trade.price);
  obj << "quantity" << trade.quantity;
  obj << "ticker"   << trade.ticker;

  auto str = obj.json();
  str.erase(std::remove(str.begin(), str.end(), '\n'), str.end());
  return str;
}

std::string to_string(OrderSide side) {
  switch (side) {
  case OrderSide::OS_Buy:
    return "buy";
    break;
  case OrderSide::OS_Sell:
    return "sell";
    break;
  }
  return "None";
}

std::string to_string(OrderStatus status) {
  switch (status) {
  case OrderStatus::OS_Working:
    return "Working";
    break;
  case OrderStatus::OS_Filled:
    return "Filled";
    break;
  }
  return "None";
}

}
