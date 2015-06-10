#include "client.h"

#include "boost/bind.hpp"
#include "boost/system/error_code.hpp"

#include <iostream>
#include <istream>
#include <string>

namespace common {

Client::Client(boost::asio::io_service& io_service, std::string ip, size_t port, MessageCB msg_cb)
  : io_service_(io_service),
    socket_(io_service_),
    ip_(std::move(ip)),
    port_(port),
    connected_(false),
    closing_(false),
	message_cb_(std::move(msg_cb)) {}

Client::~Client() { disconnect(); }

bool Client::connect() {
  try {
//    std::cout << "Connecting to host[" << ip_ << "], port[" << port_ << "]" << std::endl;
    boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::address::from_string(ip_), port_);

    return connect(endpoint);
  } catch(const std::exception &e) {
    std::cerr << "Error in connecting" << std::endl;
  }
  return false;
}

void Client::disconnect() {
  close();

  connected_ = false;
  closing_   = false;
}

void Client::update() {
  io_service_.poll();
}

void Client::write(std::string msg) {
  if(!connected_) return;
  if(closing_) return;

  io_service_.post(boost::bind(&Client::do_write, this, msg));
}

bool Client::connect(boost::asio::ip::tcp::endpoint& endpoint) {
  if(connected_) return true;
  if(closing_) return false;

  ep_ = endpoint;

  try {
    socket_.connect(ep_);
    connected_ = true;
    async_read();
  } catch(const std::exception &e) {
    std::cerr << "Error in connecting: exception[" << e.what() << "]" << std::endl;
  }
  return connected_;
}

void Client::close() {
  if(!connected_) return;

  io_service_.post(boost::bind(&Client::do_close, this));
}

void Client::async_read() {
  if(!connected_) return;
  if(closing_) return;

  boost::asio::async_read_until(socket_, buffer_, delimiter_,
      boost::bind(&Client::handle_read, this, boost::asio::placeholders::error));
}

void Client::handle_read(const boost::system::error_code& error) {
  if (!error) {
    std::string msg;
    std::istream is(&buffer_);
    std::getline(is, msg);
    if(!msg.empty()) {
      message_cb_(msg);
    }

    async_read();
  } else {
    connected_ = false;
    do_close();
  }
}

void Client::do_write(std::string msg) {
  if(!connected_) return;

  bool write_in_progress = !messages_.empty();
  messages_.push_back(msg);

  if (!write_in_progress && !closing_) {
    boost::asio::async_write(socket_,
      boost::asio::buffer(messages_.front()),
      boost::bind(&Client::handle_write, this, boost::asio::placeholders::error));
  }
}

void Client::do_close() {
  if(closing_) return;

  closing_ = true;

  socket_.close();
}

void Client::handle_write(const boost::system::error_code& error) {
  if(!error && !closing_) {
    messages_.pop_front();
    if (!messages_.empty()) {
      boost::asio::async_write(socket_,
        boost::asio::buffer(messages_.front()),
        boost::bind(&Client::handle_write, this, boost::asio::placeholders::error));
    }
  }
}

}
