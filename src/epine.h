#ifndef EPINE_H
#define EPINE_H

#include <string>
#include <functional>

#include "Auth/Auth.h"
#include "Auth/Wallet.h"

namespace Epine {
  class Client {
    public:
      typedef std::function<void(void)> ReadynessListener;

      Auth auth;
      Client();
      void init(ReadynessListener callback);
    private:
      sio::client _sio_client;
      sio::socket::ptr _sio_socket;
  };
}

#endif // EPINE_H
