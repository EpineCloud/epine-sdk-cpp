#include "Tokens.h"

#include <string>
#include <functional>
#include <iostream>

#include "HTTPRequest.hpp"

class EpineHTTPAPIv1 {
  public:
    static std::string getTokensAddressBalance(Epine::Config * config_, std::string address_, Epine::Constants::Chains::Type type_, Epine::Constants::Chains::ID id_) {
      try {
        std::string chainType = Epine::Constants::Chains::TypeUtils::toString(type_);
        int intChainId = static_cast<int>(id_);
        std::string chainId = std::to_string(intChainId);
        std::string url = config_->baseUrl + "/v1/tokens/address/" + address_ + "/balance?chainType=" + chainType + "&chainId=" + chainId;
        http::Request request{url};

        const http::Response response = request.send("GET", "", {
          {"x-session-id", config_->sessionId}
        });

        const auto responseBody = std::string{response.body.begin(), response.body.end()};

        LOG("Received JSON: " + responseBody); // print the result
        return responseBody;
      } catch (const std::exception& e) {
        std::cerr << "Request failed, error: " << e.what() << '\n';
      }
    }
};

namespace Epine {
  Tokens::Tokens(Config * config_) {
    _config = config_;
  }

  std::string Tokens::getAddressBalance(std::string address_, Constants::Chains::Type type_, Constants::Chains::ID id_) {
    return EpineHTTPAPIv1::getTokensAddressBalance(_config, address_, type_, id_);
  }
}
