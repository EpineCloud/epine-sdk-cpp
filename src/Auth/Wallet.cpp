#include "Wallet.h"

#include <string>
#include <functional>
#include <iostream>

#include "HTTPRequest.hpp"
#include "rapidjson/document.h"

class EpineHTTPAPIv1 {
  public:
    static std::string getAuthWalletConnect(Epine::Config * config_) {
      try {
        std::string url = config_->baseUrl + "/v1/auth/request";
        http::Request request{url};

        const http::Response response = request.send("GET", "", {
          {"x-session-id", config_->sessionId}
        });

        const auto responseBody = std::string{response.body.begin(), response.body.end()};

        rapidjson::Document d;
        d.Parse(&responseBody[0]);

        std::string uri = d["uri"].GetString();
        LOG("Received URI: " + uri); // print the result
        return uri;
      } catch (const std::exception& e) {
        std::cerr << "Request failed, error: " << e.what() << '\n';
      }
    }
};

namespace Epine {
  Auth::Wallet::Wallet(Config * config_) {
    _config = config_;

    _on_connected_listener = []{};
  }

  void Auth::Wallet::init(sio::socket::ptr sio_socket) {
    sio_socket->on(
      Constants::Socket::TOPIC_AUTH_CONNECTED,
      sio::socket::event_listener_aux([&](std::string const &name, sio::message::ptr const &data, bool isAck, sio::message::list &ack_resp){
        _on_connected_listener();
      })
    );
  }

  std::string Auth::Wallet::connect() {
    return EpineHTTPAPIv1::getAuthWalletConnect(_config);
  }

  void Auth::Wallet::on(Event event, EventListener callback) {
    if (event == Event::CONNECTED) {
      _on_connected_listener = callback;
    }
  }
}
