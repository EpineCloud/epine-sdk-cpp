#ifndef EPINE_AUTH_H
#define EPINE_AUTH_H

#include <string>
#include <functional>

#include "../../lib/sio/include/sio_client.h"

namespace Epine {
  class Auth {

    public:
      class Wallet;

      Wallet * wallet;
      Auth();
      void init(sio::socket::ptr sio_socket);
  };
}
#endif // EPINE_AUTH_H
