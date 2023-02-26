#ifndef EPINE_TOKENS_H
#define EPINE_TOKENS_H

#include <string>
#include <functional>

#include "../Constants/Constants.h"
#include "../Config/Config.h"

namespace Epine {
  class Tokens {

    public:
      Tokens(Config * config_);

      std::string getAddressBalance(std::string address, Constants::Chains::Type type, Constants::Chains::ID id);
    private:
      Config * _config;
  };
}
#endif // EPINE_TOKENS_H
