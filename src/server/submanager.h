#ifndef SERVER_SUBMANAGER_H
#define SERVER_SUBMANAGER_H

#include "boost/multi_index_container.hpp"
#include "boost/multi_index/composite_key.hpp"
#include "boost/multi_index/member.hpp"
#include "boost/multi_index/ordered_index.hpp"

#include <map>

#include "server/fwd.h"

namespace bm = boost::multi_index;

namespace server {

struct SubStruct {
  SubStruct(std::string k, std::string n) : key(k), name(n) {};

  std::string key;
  std::string name;
};

struct by_key{};
struct by_name{};
struct by_pair{};

typedef boost::multi_index_container<
    SubStruct,
    bm::indexed_by<
      bm::ordered_unique<bm::tag<by_pair>, bm::composite_key<SubStruct,
                                                             bm::member<SubStruct, std::string, &SubStruct::key>,
                                                             bm::member<SubStruct, std::string, &SubStruct::name>>>

    >
> Subscriptions;


class SubManager {
public:
  SubManager(ConnectionManagerI* conn_manager);
  virtual ~SubManager();

public:
  void SubscribeAll(std::string name);
  void Subscribe(std::string key,   std::string name);
  void UnSubscribe(std::string key, std::string name);

  void Publish(std::string key, std::string data);

private:
  ConnectionManagerI *manager_;
  Subscriptions      subs_;

  std::map<std::string, int> white_list_;
};

}
#endif  // SERVER_SUBMANAGER_H
