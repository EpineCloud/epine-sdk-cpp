#include "Config.h"

namespace Epine {
  Config::Config(std::string baseUrl_) {
    baseUrl = baseUrl_;
  }

  void Config::setSessionId(std::string sessionId_) {
    sessionId = sessionId_;
  }
}
