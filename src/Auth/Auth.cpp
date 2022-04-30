#include "Auth.h"

#include <string>
#include <functional>
#include <iostream>

#include "Wallet.h"

namespace Epine {
  Auth::Auth(Config * config_) {
    _config = config_;
    // Create instance of Wallet
    wallet = new Wallet(config_);
  }

  void Auth::init(sio::socket::ptr sio_socket) {
    wallet->init(sio_socket);
  }
}
