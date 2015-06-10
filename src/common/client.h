#ifndef SERVER_CLIENT_H
#define SERVER_CLIENT_H

#include "boost/asio.hpp"

#include <deque>
#include <functional>
#include <string>

namespace common {

typedef std::function<void(std::string)> MessageCB;

class Client {
public:
  Client(boost::asio::io_service& io_service, std::string ip, size_t port, MessageCB msg_cb);
  virtual ~Client();

  bool connect();
  void disconnect();

  void update();
  void write(std::string msg);

private:
  bool connect(boost::asio::ip::tcp::endpoint& endpoint);
  void close();

  void async_read();

  void do_write(std::string msg);
  void do_close();

  void handle_read(const boost::system::error_code& error);
  void handle_write(const boost::system::error_code& error);

private:
  boost::asio::ip::tcp::endpoint  ep_;
  boost::asio::io_service&        io_service_;
  boost::asio::ip::tcp::socket    socket_;
  boost::asio::streambuf          buffer_;

  bool                            connected_;
  bool                            closing_;
  std::deque<std::string>         messages_;
  std::string                     delimiter_;
  std::string                     ip_;
  size_t                          port_;

  MessageCB                       message_cb_;
};

}
#endif // SERVER_CLIENT_H

