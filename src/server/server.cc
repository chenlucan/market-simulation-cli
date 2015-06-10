#include "server.h"

#include <iostream>
#include <signal.h>
#include <utility>

namespace server {

Server::Server(const std::string& address, int port, boost::asio::io_service& io_service, ConnectionManager* connection_manager, ConnMessageCB msgcb)
  : io_service_(io_service),
    acceptor_(io_service_),
    socket_(io_service_),
    ip_(address),
    port_(std::to_string(port)),
    message_cb_(msgcb),
    connection_manager_(connection_manager),
    connection_id_(0) {}

void Server::Start() {
  // Open the acceptor with the option to reuse the address (i.e. SO_REUSEADDR).
  boost::asio::ip::tcp::resolver resolver(io_service_);
  boost::asio::ip::tcp::endpoint endpoint = *resolver.resolve({ip_, port_});
  acceptor_.open(endpoint.protocol());
  acceptor_.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
  acceptor_.bind(endpoint);
  acceptor_.listen();

  do_accept();
}

void Server::Stop() {
  acceptor_.close();
}

void Server::do_accept() {
  acceptor_.async_accept(socket_,
    [this](boost::system::error_code ec) {
      // Check whether the server was stopped by a signal before this
      // completion handler had a chance to run.
      if (!acceptor_.is_open()) {
        return;
      }
      if (!ec) {
        connection_manager_->Start(std::make_shared<Connection>(std::to_string(connection_id_++), std::move(socket_), connection_manager_,
          [=] (std::string connection_name, std::string data) {
            message_cb_(connection_name, data);
        }));
      }

      do_accept();
    });
}

}
