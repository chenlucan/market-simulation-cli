#ifndef SERVER_EXCHANGE_H
#define SERVER_EXCHANGE_H

#include "config/fwd.h"

#include "server/connectionmanager.h"
#include "server/quotesreader.h"
#include "server/requesthandler.h"
#include "server/server.h"

namespace server {

class Exchange : public QuotesListenerI, public RequestListenerI {
public:
	Exchange(boost::asio::io_service& io_service, bp::ptree config);
	virtual ~Exchange();

	void Start();
	void Stop();

public:
	// QuotesListenerI interface
	void OnQuote(std::string datetime, std::string ticker, double bid_price, double ask_price, int bid_qty, int ask_qty) override;

public:
  // RequestListenerI interface
  void OnRequest(ReqMarkets  req) override;
  void OnRequest(ReqOrders   req) override;
  void OnRequest(ReqTrades   req) override;
  void OnRequest(ReqOms      req) override;
  void OnRequest(ReqNewOrder req) override;

private:
	void UpdateStats(double fill_price, int fill_qty);

private:
	// read quotes
	QuotesReader      quotes_reader_;

  // manage tcp connections
  ConnectionManager connection_manager_;
  Server            server_;

  std::string ticker_;
  double      bid_price_;
  double      ask_price_;
  int         bid_qty_;
  int         ask_qty_;
  double      last_;
  double      turnover_;
};

}
#endif // SERVER_EXCHANGE_H
