#include <iostream>
#include <map>
#include "WebServerBridge.hpp"
#include "Client.hpp"
#include "MainController.hpp"

WebServerBridge::WebServerBridge(const IParameters *parameters)
  : AThreadedDataHandler(parameters), _client(new Client("http://localhost:8081"))
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
	      sio::message::ptr resultObj(sio::object_message::create());
	      std::map<std::string, sio::message::ptr> &obj = resultObj->get_map();

	      obj.insert(std::make_pair("iteration",
					sio::int_message::create(result->getIteration())));
	      obj.insert(std::make_pair("maxScore",
					sio::int_message::create(result->getMaxScore())));
	      obj.insert(std::make_pair("averageScore",
					sio::int_message::create(result->getAverageScore())));
	      obj.insert(std::make_pair("worstScore",
					sio::int_message::create(result->getWorstScore())));

	      _client->emit("new result", resultObj);
	    }
	  else if (result->getTheoreticalMaxScore() == -2)
	    {
	      _client->emit("solution found", std::string("this is the end signal"));
	    }
	  else
	    {
	       _client->emit("theoretical max score",
			     sio::int_message::create(result->getTheoreticalMaxScore()));
	    }
	  delete result;
	}
      std::this_thread::sleep_for(std::chrono::milliseconds(300));
    }
}
