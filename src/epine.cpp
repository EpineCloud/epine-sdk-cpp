#include "epine.h"

#include <string>
#include <functional>
#include <iostream>

namespace Epine {
  Client::Client(Environment environment) {
    std::string baseUrl;
    switch (environment)
    {
      case Environment::PRODUCTION:
        // baseUrl = "https://api-dev.epine.cloud";
        baseUrl = "http://34.91.134.2";
        break;
      default:
        baseUrl = "http://localhost:3000";
        break;
    }

    _config = new Config(baseUrl);
    
    auth = new Auth(_config);
    tokens = new Tokens(_config);

    _on_init_callback = []{};
  }

  void Client::init() {
    LOG("Epine Log: Connecting to " + _config->baseUrl);

    _sio_client.set_open_listener([&](){
      LOG("Epine Log: Connection opened");

      _sio_socket->on(
        Constants::Socket::TOPIC_SESSION,
        sio::socket::event_listener_aux([&](std::string const &name, sio::message::ptr const &data, bool isAck, sio::message::list &ack_resp){
          std::string sessionId = data->get_map()["sessionId"]->get_string();
          _config->setSessionId(sessionId);
          this->_on_init_callback();
        })
      );
      std::string sessionData = "{}";
      _sio_socket->emit(Constants::Socket::TOPIC_SUBSCRIBE, sessionData);
    });

    _sio_client.set_close_listener([&](sio::client::close_reason const &reason){
      LOG("Epine Log: Connection closed");
    });

    _sio_client.set_fail_listener([&](){
      LOG("Epine Error: connection failed");
    });

    _sio_client.connect(_config->baseUrl);
    _sio_socket = _sio_client.socket("/v1");

    // Trigger hierarchy init
    auth->init(_sio_socket);
  }

  void Client::set_on_init_callback(CallbackVoid on_init_callback) {
    _on_init_callback = on_init_callback;
  }
}
