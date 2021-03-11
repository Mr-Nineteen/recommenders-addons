#include "redis_client.h"

#include <map>
#include <cstring>
#include <iostream>
#include "tensorflow_recommenders_addons/dynamic_embedding/core/lib/redis/include/acl_cpp/lib_acl.hpp"

using namespace std;

namespace tfra {
namespace redis {

bool RedisClientObj::Initialize(const std::string& addr, int maxConns, int connTimeout,
                                int rwTimeout) {
  cluster_ = std::make_shared<acl::redis_client_cluster>();
  cmdSet_ = std::make_shared<acl::redis_set>();
  cmdZSet_ = std::make_shared<acl::redis_zset>();
  cmdKey_ = std::make_shared<acl::redis_key>();

  cluster_->set(addr.c_str(), maxConns, connTimeout, rwTimeout);
  cmdSet_->set_cluster(cluster_.get());
  cmdZSet_->set_cluster(cluster_.get());
  cmdKey_->set_cluster(cluster_.get());

  acl::redis_command cmd(cluster_.get());
  const acl::redis_result* pRes = cmd.request({"ping"});

  if (pRes == nullptr) {
    cout << "redis[" << addr.c_str() << "] init failed, pRes is nullptr" << endl;
    return false;
  }

  cout << "redis[" << addr.c_str() << "] init res " << pRes->get_type() << ", status: " << pRes->get_status() << endl;
  if (pRes->get_type() != acl::REDIS_RESULT_STATUS ||
      std::string("PONG").compare(pRes->get_status())) {
    return false;
  }

  cout << "redis[" << addr.c_str() << "] init success..." << endl;
  return true;
}

std::string RedisClientObj::Get(const std::string& key) {
  acl::string val;
  acl::redis_string redis;
  redis.set_cluster(cluster_.get());
  bool bSuccess = redis.get(key.c_str(), val);
  return bSuccess ? std::string(val.c_str(), val.length()) : "";
}

bool RedisClientObj::ZAdd(const std::string& key, const std::string& member, double score) {
  if(member.empty()) {
    return false;
  }
  std::map<acl::string, double> kvs_;
  kvs_.emplace(member.c_str(), score);
  cmdZSet_->zadd(key.c_str(), kvs_);
  cmdZSet_->clear();
  return true;
}

bool RedisClientObj::SAdd(const std::string& key, const std::string& value) {
  if(value.empty()) {
    return false;
  }
  std::vector<acl::string> members;
  members.push_back(acl::string(value.c_str()));
  cmdSet_->sadd(key.c_str(), members);
  cmdSet_->clear();
  return true;
}

}  // namespace foundation
}  // namespace tesseract