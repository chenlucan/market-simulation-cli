#ifndef SERVER_SERVER_H
#define SERVER_SERVER_H

#include "boost/asio.hpp"

#include <string>

namespace server {
/// The top-level class of the HTTP server.
class Server {
public:
  Server(const Server&) = delete;
  Server& operator=(const Server&) = delete;

  /// Construct the server to listen on the specified TCP address and port, and
  /// serve up files from the given directory.
  Server(const std::string& address, int port, boost::asio::io_service& io_service);

  void Start();
  void Stop();

private:
  /// Perform an asynchronous accept operation.
  void do_accept();

private:
  /// The io_service used to perform asynchronous operations.
  boost::asio::io_service& io_service_;

  /// Acceptor used to listen for incoming connections.
  boost::asio::ip::tcp::acceptor acceptor_;

  /// The next socket to be accepted.
  boost::asio::ip::tcp::socket socket_;

  std::string ip_;
  std::string port_;

  int connection_id_;
};
}
#endif // SERVER_SERVER_H
