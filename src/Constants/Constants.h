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

    namespace Chains {
      enum class Type {
        EVM,
        TVM
      };
      class TypeUtils {
        public:
          static std::string toString(Type type) {
            switch (type) {
              case Type::EVM:
                return "EVM";
              case Type::TVM:
                return "TVM";
              default:
                throw std::invalid_argument("Unknown chain type");
            }
          }
      };
    }
  }
}
#endif // EPINE_CONSTANTS_H
