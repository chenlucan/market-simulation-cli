#ifndef SERVER_QUOTESREADER_H
#define SERVER_QUOTESREADER_H

#include "boost/asio/deadline_timer.hpp"

#include <fstream>

#include "config/fwd.h"

namespace server {

class QuotesListenerI {
public:
  QuotesListenerI() {}
  virtual ~QuotesListenerI() {}

  virtual void OnQuote(std::string datetime, std::string ticker, double bid_price, double ask_price, int bid_qty, int ask_qty) {};
};

class QuotesReader {
public:
  QuotesReader(boost::asio::io_service& io_service, bp::ptree config, QuotesListenerI* listener);
	virtual ~QuotesReader();

	void Start();
	void Stop();

private:
	void QuotesTimerHandler(const boost::system::error_code& error);

private:
	std::fstream file_;
	boost::asio::deadline_timer timer_;

	std::string ticker_;
	double      bid_price_;
	double      ask_price_;
	int         bid_qty_;
	int         ask_qty_;
	double      last_;
	double      turnover_;

	QuotesListenerI *listener_;
};
}

#endif // SERVER_QUOTESREADER_H
