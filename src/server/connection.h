#ifndef SERVER_CONNECTION_H
#define SERVER_CONNECTION_H

#include "boost/asio.hpp"

#include <memory>

namespace server {

class ConnectionManager;

typedef std::function<void(std::string, std::string)> ConnMessageCB;
/// Represents a single connection from a client.
class Connection : public std::enable_shared_from_this<Connection>
{
public:
  Connection(const Connection&) = delete;
  Connection& operator=(const Connection&) = delete;

  Connection(std::string n, boost::asio::ip::tcp::socket socket, ConnectionManager* manager, ConnMessageCB msgcb);

  /// Start the first asynchronous operation for the connection.
  void Start() {
    async_read();
  }
  /// Stop all asynchronous operations associated with the connection.
  void Stop();

  void Send(std::string data);

public:
  const std::string& name() { return name_; }

private:
  /// Perform an asynchronous read operation.
  void async_read();

  /// Perform an asynchronous write operation.
  void async_write(std::string data);

  void handle_read(const boost::system::error_code& error);

private:
  std::string   name_;
  std::string   delimiter_;
  ConnMessageCB message_cb_;

  /// Socket for the connection.
  boost::asio::ip::tcp::socket socket_;
  boost::asio::streambuf       buffer_;

  /// The manager for this connection.
  ConnectionManager* connection_manager_;
};

typedef std::shared_ptr<Connection> connection_ptr;

}
#endif // SERVER_CONNECTION_H
