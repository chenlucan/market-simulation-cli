#include "server/requesthandler.h"

#include "server/util.h"

namespace server {

RequestHandler::RequestHandler(RequestListenerI *listener) : listener_(listener) {}

RequestHandler::~RequestHandler() {}

void RequestHandler::ParseRequest(std::string connection_name, std::string data) {
  jsonxx::Object obj;
  if (!obj.parse(data)) {
    std::cout << "wrong json format order received"<< std::endl;
    return;
  }

  auto req = obj.get<jsonxx::String>("type", "");
  if (req == "markets") {
    auto ticker = obj.get<jsonxx::String>("ticker", "");
    ReqMarkets req{};
    req.login_account     = connection_name;
    req.instrested_ticker = ticker;
    listener_->OnRequest(req);
  } else if (req == "orders") {
    auto account = obj.get<jsonxx::String>("account", "server");
    ReqOrders req{};
    req.login_account      = connection_name;
    req.instrested_account = account;
    listener_->OnRequest(req);
  } else if (req == "trades") {
    auto account = obj.get<jsonxx::String>("account", "server");
    ReqTrades req{};
    req.login_account      = connection_name;
    req.instrested_account = account;
    listener_->OnRequest(req);
  } else if (req == "oms") {
    auto account = obj.get<jsonxx::String>("account", "");
    ReqOms req{};
    req.login_account      = connection_name;
    listener_->OnRequest(req);
  } else if (req == "new_order") {
    auto account  = obj.get<jsonxx::String>("account");
    auto ticker   = obj.get<jsonxx::String>("ticker", "");
    auto side_str = obj.get<jsonxx::String>("side", "");
    auto price    = std::atof(obj.get<jsonxx::String>("price", "0").c_str());
    auto qty      = obj.get<jsonxx::Number>("quantity", 0);
    auto side     = (side_str == "buy") ? OrderSide::OS_Buy : (side_str == "sell" ? OrderSide::OS_Sell : OrderSide::OS_None);
    ReqNewOrder req{};
    req.login_account = account;
    req.price = price;
    req.quantity = qty;
    req.ticker = ticker;
    req.side = side;
    listener_->OnRequest(req);
  }
}

}
