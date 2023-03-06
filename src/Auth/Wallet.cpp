#include "Wallet.h"

#include <string>
#include <functional>
#include <iostream>

#include "HTTPRequest.hpp"
#include "rapidjson/document.h"

class EpineHTTPAPIv1 {
  public:
    static std::string getAuthRequest(Epine::Config * config_, Epine::Constants::Chains::Type type_) {
      try {
        std::string chainType = Epine::Constants::Chains::TypeUtils::toString(type_);
        std::string url = config_->baseUrl + "/v1/auth/request?chainType=" + chainType;
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

    _on_connected_listener = [](std::vector<std::string>){};
  }

  void Auth::Wallet::init(sio::socket::ptr sio_socket) {
    sio_socket->on(
      Constants::Socket::TOPIC_AUTH_CONNECTED,
      sio::socket::event_listener_aux([&](std::string const &name, sio::message::ptr const &data, bool isAck, sio::message::list &ack_resp){
        std::vector<sio::message::ptr> addressesVector = data->get_map()["addresses"]->get_vector();

        std::vector<std::string> addressesArray;
        std::transform(
          addressesVector.begin(),
          addressesVector.end(),
          std::back_inserter(addressesArray),
          [](const sio::message::ptr elem) { return elem->get_string(); }
        );

        _on_connected_listener(addressesArray);
      })
    );
  }

  std::string Auth::Wallet::connect(Constants::Chains::Type type_) {
    return EpineHTTPAPIv1::getAuthRequest(_config, type_);
  }

  void Auth::Wallet::on(Event event, EventListenerStringArray callback) {
    switch (event) {
      case Event::CONNECTED:
        _on_connected_listener = callback;
        break;
      default:
        throw std::runtime_error("Event type and listener mismatch");
    }
  }
}
