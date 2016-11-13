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
	  if (result->getTheoreticalMaxScore() == -1)
	    {
	      _client->emit("new result", std::string("this is a test"));
	    }
	  else if (result->getTheoreticalMaxScore() == -2)
	    {
	      _client->emit("solution found", std::string("this is a test"));
	    }
	  else
	    {
	       _client->emit("theoretical max score", sio::int_message::create(400));
	    }
	  delete result;
	}
      std::this_thread::sleep_for(std::chrono::milliseconds(300));
    }
}
