#ifndef EPINE_AUTH_WALLET_H
#define EPINE_AUTH_WALLET_H

#include <string>
#include <functional>

#include "Auth.h"

namespace Epine {
  class Auth::Wallet {
    public:
      enum class Event {
        CONNECTED,
        DISCONNECTED
      };

      typedef std::function<void(void)> EventListener;

      Wallet(Config * config_);
      void init(sio::socket::ptr sio_socket);
      std::string connect(Constants::Chains::Type type);
      void on(Event event, EventListener callback);
      void once(Event event, EventListener callback);
      void off(Event event);

    private:
      Config * _config;
      EventListener _on_connected_listener;
  };
}
#endif // EPINE_AUTH_WALLET_H
