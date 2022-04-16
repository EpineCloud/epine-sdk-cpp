#include "epine.h"

#include <string>
#include <functional>
#include <iostream>

// class connection_listener
// {
//   sio::client &handler;

// public:
//   connection_listener(sio::client &h) : handler(h)
//   {
//   }

//   void on_connected()
//   {
//     _lock.lock();
//     _cond.notify_all();
//     connect_finish = true;
//     _lock.unlock();
//   }
//   void on_close(client::close_reason const &reason)
//   {
//     std::cout << "sio closed " << std::endl;
//     exit(0);
//   }

//   void on_fail()
//   {
//     std::cout << "sio failed " << std::endl;
//     exit(0);
//   }
// };

namespace Epine {
  // class Wallet
  Auth::Wallet::Wallet() {}
  void Auth::Wallet::connect() {}

  // class Auth
  Auth::Auth() {}

  // class Client
  Client::Client() {}
  void Client::init(ReadynessListener callback) {
    std::string url = "http://localhost:3000";
    std::cout << "Connecting to " << url << std::endl;

    _sio_client.set_open_listener([&](){
      std::cout << "Connection opened" << std::endl;

      callback();
    });

    _sio_client.connect(url);
    _sio_socket = _sio_client.socket();
  }
}
