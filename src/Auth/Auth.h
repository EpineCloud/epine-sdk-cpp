#ifndef EPINE_AUTH_H
#define EPINE_AUTH_H

#include <string>
#include <functional>

#include "../../lib/sio/src/sio_client.h"

#include "../Constants/Constants.h"
#include "../Config/Config.h"

namespace Epine {
  class Auth {

    public:
      class Wallet;

      Wallet * wallet;
      Auth(Config * config_);
      void init(sio::socket::ptr sio_socket);
    private:
      Config * _config;
  };
}
#endif // EPINE_AUTH_H
