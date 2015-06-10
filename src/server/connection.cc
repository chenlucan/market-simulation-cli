#include "connection.h"

#include "boost/bind.hpp"

#include <iostream>

#include "connectionmanager.h"

namespace server {

Connection::Connection(std::string n, boost::asio::ip::tcp::socket socket, ConnectionManager* manager, ConnMessageCB msgcb)
  : name_(n),
    socket_(std::move(socket)),
    connection_manager_(manager),
    message_cb_(std::move(msgcb)),
    delimiter_("\0") {}

void Connection::Stop() {
  socket_.close();
}

void Connection::Send(std::string data) {
  async_write(data);
}

void Connection::async_read() {
  auto self(shared_from_this());

  boost::asio::async_read_until(socket_, buffer_, delimiter_,
      boost::bind(&Connection::handle_read, this, boost::asio::placeholders::error));
}

void Connection::async_write(std::string data) {
  auto self(shared_from_this());
  boost::asio::async_write(socket_, boost::asio::buffer(data.c_str(), data.size()),
      [this, self](boost::system::error_code ec, std::size_t) {});
}

void Connection::handle_read(const boost::system::error_code& error) {
  if (!error) {
    std::string msg;
    std::istream is(&buffer_);
    std::getline(is, msg);
    if(!msg.empty()) {
      message_cb_(name(), msg);
    }
    async_read();
  } else if (error == boost::asio::error::connection_reset ||
      error == boost::asio::error::network_reset    ||
      error == boost::asio::error::eof) {
    connection_manager_->Stop(shared_from_this());
  }
}

}
