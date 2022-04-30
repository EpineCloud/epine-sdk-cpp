#ifndef EPINE_H
#define EPINE_H

#include <string>
#include <functional>

#include "Auth/Auth.h"
#include "Auth/Wallet.h"
#include "Constants/Constants.h"
#include "Config/Config.h"

namespace Epine {
  class Client {
    public:
      enum class Environment {
        PRODUCTION,
        LOCAL
      };

      typedef std::function<void(void)> ReadynessListener;

      Auth * auth;
      Client(Environment environment = Environment::PRODUCTION);
      void init(ReadynessListener callback);
    private:
      Config * _config;
      sio::client _sio_client;
      sio::socket::ptr _sio_socket;
  };
}

#endif // EPINE_H
