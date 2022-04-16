#ifndef EPINE_H
#define EPINE_H

#include <string>
#include <functional>

#include "../lib/sio/include/sio_client.h"

namespace Epine {
  class Auth {
    class Wallet {
      public:
        enum Event {
          CONNECT,
          DISCONNECT
        };

        typedef std::function<void(void)> EventListener;

        Wallet();
        void connect();
        void on(Event event, EventListener callback);
        void once(Event event, EventListener callback);
        void off(Event event);
    };

    public:
      Wallet wallet;
      Auth();
  };

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

#endif // __EPINE_H__
