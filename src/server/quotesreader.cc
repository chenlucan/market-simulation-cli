#include "server/quotesreader.h"

#include "boost/date_time/posix_time/posix_time.hpp"

#include "config/config.h"

#include "common/jsonxx.h"

namespace server {

QuotesReader::QuotesReader(boost::asio::io_service& io_service, bp::ptree config, QuotesListenerI *listener)
  : file_(config.get("quotes_file", "quotes.txt")),
    timer_(io_service),
    ticker_(config.get("ticker", "601398")),
    bid_price_(),
    ask_price_(),
    bid_qty_(),
    ask_qty_(),
    last_(),
    turnover_(),
    listener_(listener) {
}

QuotesReader::~QuotesReader() {
	file_.close();
}

void QuotesReader::Start() {
  std::string line;
  if (std::getline(file_, line)) {
      std::istringstream ss(line);
      double dt;
      if (!(ss >> dt >> bid_price_ >> ask_price_ >> bid_qty_ >> ask_qty_)) {
        std::cerr << "Wrong quote format, [" << line << "]" << std::endl;
        return;
      }
      timer_.expires_from_now(boost::posix_time::milliseconds(dt * 1000));
      timer_.async_wait([=] (const boost::system::error_code& e) { QuotesTimerHandler(e); });
  }
}

void QuotesReader::Stop() {
  timer_.cancel();
}

void QuotesReader::QuotesTimerHandler(const boost::system::error_code& error) {
  if (!error) {
    // publish data now!!!
    auto n = boost::posix_time::microsec_clock::local_time();
    auto dt = boost::posix_time::to_simple_string(n);
    listener_->OnQuote(dt, ticker_, bid_price_, ask_price_, bid_qty_, ask_qty_);

		std::string line;
		if (std::getline(file_, line)) {
				std::istringstream ss(line);
				double dt;
				if (!(ss >> dt >> bid_price_ >> ask_price_ >> bid_qty_ >> ask_qty_)) {
					std::cerr << "Wrong quote format, [" << line << "]" << std::endl;
					return;
				}
				timer_.expires_from_now(boost::posix_time::milliseconds(dt * 1000));
				timer_.async_wait([=] (const boost::system::error_code& e) { QuotesTimerHandler(e); });
		}
  } else {
    std::cerr << "Error in quote reader";
  }
}

}
