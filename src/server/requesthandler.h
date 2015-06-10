#ifndef SERVER_REQUESTHANDLER_H
#define SERVER_REQUESTHANDLER_H

#include "common/jsonxx.h"

#include "server/message.h"

namespace server {
class RequestListenerI {
public:
  RequestListenerI() {};
  virtual ~RequestListenerI() {}

  virtual void OnRequest(ReqMarkets  req) {};
  virtual void OnRequest(ReqOrders   req) {};
  virtual void OnRequest(ReqTrades   req) {};
  virtual void OnRequest(ReqOms      req) {};
  virtual void OnRequest(ReqNewOrder req) {};
};

class RequestHandler {
public:
  RequestHandler(RequestListenerI *listener);
  virtual ~RequestHandler();

public:
  void ParseRequest(std::string connection_name, std::string data);

private:
  RequestListenerI *listener_;
};
}
#endif  // SERVER_REQUESTHANDLER_H
