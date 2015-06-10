#ifndef SERVER_TRADEMANAGER_H
#define SERVER_TRADEMANAGER_H

#include <map>

#include "server/util.h"

namespace server {

class TradeManager {
public:
  TradeManager();
  virtual ~TradeManager();

  Trade AddTrade(std::string account, int orderid, double price, int quantity, std::string ticker);

private:
  int id_;
  std::map<int, Trade> trades_;
};

}
#endif  // SERVER_TRADEMANAGER_H
