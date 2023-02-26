#ifndef EPINE_TOKENS_H
#define EPINE_TOKENS_H

#include <string>
#include <functional>

#include "HTTPRequest.hpp"
#include "rapidjson/document.h"

#include "../Constants/Constants.h"
#include "../Config/Config.h"

namespace Epine {
  class Tokens {
    public:
      class Token {
        public:
          std::string address;
          std::string symbol;
          double balance;
          bool native;
      };


      Tokens(Config * config_);

      std::vector<Token> parseTokensJSON(const std::string& tokensJSON);
      std::vector<Token> getAddressBalance(std::string address, Constants::Chains::Type type, Constants::Chains::ID id);
    private:
      Config * _config;
  };
}
#endif // EPINE_TOKENS_H
