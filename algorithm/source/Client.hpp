#ifndef		CLIENT_HPP_
# define	CLIENT_HPP_

# include <string>
# include "WebServerBridge.hpp"
# include "sio_client.h"

class WebServerBridge::Client
{
private:
  sio::client _handler;
  sio::socket::ptr _socket;
  bool _connectFinish;

public:
  Client(const std::string &);
  ~Client();

  void onConnection();
  void onClose();
  void onFailure();
  bool connected() const;
  void emit(const std::string &, const sio::message::list & = nullptr,
	    const std::function<void (const sio::message::list &)> & = nullptr);
};

#endif		/* !CLIENT_HPP_ */
