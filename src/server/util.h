#ifndef SERVER_UTIL_H
#define SERVER_UTIL_H

#include "server/message.h"

namespace server {

std::string to_json(Order order);

std::string to_json(Trade trade);

std::string to_string(OrderSide side);

std::string to_string(OrderStatus status);

}
#endif // SERVER_UTIL_H
