#ifndef SERVER_MESSAGE_H
#define SERVER_MESSAGE_H

#include <string>

namespace server {

enum class OrderSide {
   OS_None = 0,
   OS_Buy  = 1,
   OS_Sell = 2
};

enum class OrderStatus {
   OS_None     = 0,
   OS_Working  = 1,
   OS_Filled   = 2
};

struct Order {
  Order(int oid, std::string account_name)
  : id(oid),
    account(account_name),
    price(0),
    quantity(0),
    ticker{},
    side(OrderSide::OS_None),
    status(OrderStatus::OS_None) {};

  int         id;
  std::string account;

  double      price;
  int         quantity;
  std::string ticker;
  OrderSide   side;

  OrderStatus status;
};

struct Trade {
  Trade(int id, int oid, std::string account_name)
  : id(id),
    orderid(oid),
    account(account_name),
    price(0),
    quantity(0),
    ticker{} {};

  int         id;
  int         orderid;
  std::string account;

  double      price;
  int         quantity;
  std::string ticker;
};


struct ReqMarkets {
  std::string login_account;
  std::string instrested_ticker;
};

struct ReqOrders {
  std::string login_account;
  std::string instrested_account;
};

struct ReqTrades {
  std::string login_account;
  std::string instrested_account;
};

struct ReqOms {
  std::string login_account;
};

struct ReqNewOrder {
  std::string login_account;

  OrderSide   side;
  std::string ticker;
  double      price;
  int         quantity;
};
}
#endif // SERVER_UTIL_H
