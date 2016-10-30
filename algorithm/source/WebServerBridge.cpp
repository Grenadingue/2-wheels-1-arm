#include <iostream>
#include <map>
#include "WebServerBridge.hpp"
#include "Client.hpp"
#include "MainController.hpp"

WebServerBridge::WebServerBridge()
  : _client(new Client("http://localhost:8081"))
{
  std::cout << "WebServerBridge::WebServerBridge" << std::endl;
}

WebServerBridge::~WebServerBridge()
{
  std::cout << "WebServerBridge::~WebServerBridge" << std::endl;
}

void WebServerBridge::_workLoop()
{
  const ResultModel *result = NULL;

  while (!_close)
    {
      result = NULL;
      if ((result = _getNextResult()))
	{
	  std::cout << "[C++] Web server bridge got new result !" << std::endl;
	  delete result;
	  _client->emit("new result", std::string("this is a test"));
	}
      std::cout << "Web server bridge: Waiting" << std::endl;
      std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}
