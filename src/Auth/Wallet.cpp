#include "Wallet.h"

#include <string>
#include <functional>
#include <iostream>

#include "HTTPRequest.hpp"
#include "rapidjson/document.h"

class EpineHTTPAPIv1 {
  public:
    static std::string getAuthWalletConnect() {
      try {
        http::Request request{"http://localhost:3000/auth/wallet/connect"};

        const http::Response response = request.send("GET", "", {
          {"X-Session-Id", "1337"}
        });

        const auto responseBody = std::string{response.body.begin(), response.body.end()};

        rapidjson::Document d;
        d.Parse(&responseBody[0]);

        std::cout << "Received URI: " << d["uri"].GetString() << '\n'; // print the result
        return d["uri"].GetString();
      } catch (const std::exception& e) {
        std::cerr << "Request failed, error: " << e.what() << '\n';
      }
    }
};

namespace Epine {
  Auth::Wallet::Wallet() {
    _on_connected_listener = []{};
  }

  void Auth::Wallet::init(sio::socket::ptr sio_socket) {
    sio_socket->on(
      "auth.wallet.connected",
      sio::socket::event_listener_aux([&](std::string const &name, sio::message::ptr const &data, bool isAck, sio::message::list &ack_resp){
        _on_connected_listener();
      })
    );
  }

  std::string Auth::Wallet::connect() {
    return EpineHTTPAPIv1::getAuthWalletConnect();
  }

  void Auth::Wallet::on(Event event, EventListener callback) {
    if (event == Event::CONNECTED) {
      _on_connected_listener = callback;
    }
  }
}
