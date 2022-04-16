#include "Auth.h"

#include <string>
#include <functional>
#include <iostream>

#include "Wallet.h"

namespace Epine {
  Auth::Auth() {
    // Create instance of Wallet
    wallet = new Wallet();
  }

  void Auth::init(sio::socket::ptr sio_socket) {
    wallet->init(sio_socket);
  }
}
