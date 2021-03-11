#ifndef TF_REDIS_CLIENT_H
#define TF_REDIS_CLIENT_H

#include <memory>
#include <string>

namespace acl {
  class redis_client_cluster;
  class redis_string;
  class redis_zset;
  class redis_set;
  class redis_key;
}

namespace tensorflow {
namespace redis {

template <typename T>
class TSingleton {
 public:
  static T& Instance();
  static void Destroy();

 private:
  static T* m_pInstance;
};

template <typename T>
T* TSingleton<T>::m_pInstance = NULL;

template <typename T>
inline T& TSingleton<T>::Instance() {
  if (m_pInstance == NULL) {
    m_pInstance = new T();
  }
  return *m_pInstance;
}

template <typename T>
inline void TSingleton<T>::Destroy() {
  if (m_pInstance) {
    delete m_pInstance;
    m_pInstance = nullptr;
  }
}

class RedisClientObj {
 public:
  RedisClientObj() {}
  ~RedisClientObj() {}

  // redis_addr, max_conns, conn_timeout, rw_timeout
  bool Initialize(const std::string& addr, int maxConns, int connTimeout, int rwTimeout);

  std::string Get(const std::string& key);

  bool ZAdd(const std::string& key, const std::string& member, double score);

  bool SAdd(const std::string& key, const std::string& value);

 private:
  RedisClientObj(const RedisClientObj&) = delete;
  RedisClientObj(RedisClientObj&&) = delete;

  std::shared_ptr<acl::redis_client_cluster> cluster_;
  std::shared_ptr<acl::redis_set> cmdSet_;
  std::shared_ptr<acl::redis_zset> cmdZSet_;
	std::shared_ptr<acl::redis_key> cmdKey_;
};

class RedisClient : public RedisClientObj, public TSingleton<RedisClient> {};

class RedisClientVre : public RedisClientObj, public TSingleton<RedisClientVre> {};

}  // namespace redis
}  // namespace tensorflow

#endif  // TF_REDIS_CLIENT_H