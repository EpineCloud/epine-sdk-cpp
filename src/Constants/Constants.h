#ifndef EPINE_CONSTANTS_H
#define EPINE_CONSTANTS_H

#include <string>

namespace Epine {
  namespace Constants {
    namespace Socket {
      std::string const TOPIC_SUBSCRIBE = "subscribe";
      std::string const TOPIC_SESSION = "session";

      std::string const TOPIC_AUTH_CONNECTED = "auth:connected";
    }
  }
}
#endif // EPINE_CONSTANTS_H
