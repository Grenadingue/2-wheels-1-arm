#include <iostream>
#include <map>
#include "WebServerBridge.hpp"
#include "Client.hpp"
#include "MainController.hpp"

WebServerBridge::WebServerBridge()
  : _client(new Client("http://localhost:8081"))
{
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
	  delete result;
	  _client->emit("new result", std::string("this is a test"));
	}
      std::this_thread::sleep_for(std::chrono::milliseconds(300));
    }
}
