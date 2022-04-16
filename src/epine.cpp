#include "epine.h"

#include <string>
#include <functional>
#include <iostream>

namespace Epine {
  Client::Client() {}
  void Client::init(ReadynessListener callback) {
    std::string url = "http://localhost:3000";
    std::cout << "Connecting to " << url << std::endl;

    _sio_client.set_open_listener([&](){
      std::cout << "Connection opened" << std::endl;

      callback();

      // Emit session
      std::string sessionData = "{\"sessionId\":\"1337\"}";
      _sio_socket->emit("session", sessionData);
    });

    _sio_client.connect(url);
    _sio_socket = _sio_client.socket();

    // Trigger hierarchy init
    auth.init(_sio_socket);
  }
}
