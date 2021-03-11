#include <cstring>
#include <iostream>

#include "redis_client.h"

using namespace tfra::redis;

int main(int argc, char** argv) {
  if (argc != 4) {
    std::cout << "args: redis_data [addr] [cmd] [key]" << std::endl;
    std::cout << "supported cmds [get]" << std::endl;
    return 0;
  }

  const char* redisAddr = argv[1];
  const char* cmd = argv[2];
  const char* key = argv[3];

  if (!RedisClient::Instance().Initialize(redisAddr, 1, 1, 1)) {
    std::cout << "redis [" << redisAddr << "] init failed" << std::endl;
  }

  if (strcmp(cmd, "get") == 0) {
    std::string res = RedisClient::Instance().Get(key);
    std::cout << "get [key:" << key << " value:" << res << "]" << std::endl;
  }

  return 0;
}