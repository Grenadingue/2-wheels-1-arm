#include <iostream>
#include <thread>
#include <chrono>
#include "WebServerBridge.hpp"
#include "Client.hpp"
#include "MainController.hpp"

//
// Simulate the node.js entry point
// Practicaly, only WebServerBridge::launchAlgorithm() will be called
// WebServerBridge::launchAlgorithm() must be bound to node.js engine
//
int main()
{
  WebServerBridge::launchAlgorithm();

  //
  // Act like a working thread
  // Simulate the main thread running node.js engine alongside
  while (42)
    std::this_thread::sleep_for(std::chrono::seconds(1));

  return 0;
}

WebServerBridge::WebServerBridge()
  : _client(new Client("http://localhost:3000"))
{
}

WebServerBridge::~WebServerBridge()
{
  std::cout << "BackupDataController::~BackupDataController" << std::endl;
}

//
// Replace with appropriate prototype for node.js binding
// void WebServerBridge::launchAlgorithm(v8::FunctionCallbackInfo<v8::Value> &)
//
void WebServerBridge::launchAlgorithm()
{
  MainController &main = *(new MainController);
  std::list<std::string> *parameters = new std::list<std::string>;

  //
  // Simulate parameters conversion from node.js to c++
  parameters->push_back("backup_file_name=./backup/super_backup.csv");
  parameters->push_back("population_size=200");
  parameters->push_back("mutation_rate=1%");
  parameters->push_back("foo=bar");
  parameters->push_back("beer=beer");

  main(parameters);
}

void WebServerBridge::_workLoop()
{
  const ResultModel *result = NULL;

  while (!_close)
    {
      result = NULL;
      if ((result = _getNextResult()))
	{
	  std::cout << "Web server bridge got new result !" << std::endl;
	  delete result;
	  _client->emit("event", std::string("this is a test"));
	}
      std::cout << "Web server bridge: Waiting" << std::endl;
      std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}
