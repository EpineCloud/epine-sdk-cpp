#ifndef EPINE_CONFIG_H
#define EPINE_CONFIG_H

#define LOG(__O__) std::cout << "\e[1;30;1m" << __O__ << "\e[0m" << std::endl

#include <string>

namespace Epine {
  class Config {
    public:
      Config(std::string baseUrl_);
      void setSessionId(std::string sessionId_);
      // API
      std::string baseUrl;
      std::string sessionId = "";
  };
}
#endif // EPINE_CONFIG_H
