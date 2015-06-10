#include "server/trademanager.h"

namespace server {
TradeManager::TradeManager() : id_(), trades_{} {}

TradeManager::~TradeManager() {}

Trade TradeManager::AddTrade(std::string account, int orderid, double price, int quantity, std::string ticker) {
  Trade trade(id_++, orderid, account);
  trade.price    = price;
  trade.quantity = quantity;
  trade.ticker   = ticker;

  trades_.insert(std::pair<int, Trade>(trade.id, trade));

  return trade;
}

}
