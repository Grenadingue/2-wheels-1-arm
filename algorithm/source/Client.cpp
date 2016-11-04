#include <iostream>
#include "Client.hpp"

WebServerBridge::Client::Client(const std::string &serverAddress)
  : _connectFinish(false)
{
  _handler.set_open_listener(std::bind(&WebServerBridge::Client::onConnection, this));
  _handler.set_close_listener(std::bind(&WebServerBridge::Client::onClose, this));
  _handler.set_fail_listener(std::bind(&WebServerBridge::Client::onFailure, this));
  _handler.connect(serverAddress);
}

WebServerBridge::Client::~Client()
{
  _handler.sync_close();
  _handler.clear_con_listeners();
}

void WebServerBridge::Client::onConnection()
{
  std::cout << "[SOCKET.IO_CLIENT] connected" << std::endl;
  _connectFinish = true;
  _socket = _handler.socket();
}

void WebServerBridge::Client::onClose()
{
  std::cout << "[SOCKET.IO_CLIENT] closed" << std::endl;
}

void WebServerBridge::Client::onFailure()
{
  std::cout << "[SOCKET.IO_CLIENT] failure" << std::endl;
}

bool WebServerBridge::Client::connected() const
{
  return _connectFinish;
}

void WebServerBridge::Client::emit(const std::string &eventName, const sio::message::list &data,
				   const std::function<void (const sio::message::list &)> &ack)
{
  if (_connectFinish)
    _socket->emit(eventName, data, ack);
  else
    std::cerr << "[SOCKET.IO_CLIENT] emit: client not connected, packet lost" << std::endl;
}
