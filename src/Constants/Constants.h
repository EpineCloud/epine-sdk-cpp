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
      // ID
      enum class ID {
        // No ChainId
        NO = 0,
        // EVM
        EVM_ETHEREUM = 1,
        EVM_POLYGON = 137,
        EVM_TESTNET_ZK_SYNC = 280
      };
      class IDUtils {
        public:
          static std::string toName(ID id) {
            switch (id) {
              case ID::EVM_ETHEREUM:
                return "Ethereum";
              case ID::EVM_POLYGON:
                return "Polygon";
              case ID::EVM_TESTNET_ZK_SYNC:
                return "Testnet: zkSync";
              default:
                throw std::invalid_argument("Unknown chain id");
            }
          }
      };

      // Type
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
