#include <thread>
#include <chrono>
#include "MainController.hpp"

//
// Simulate the node.js entry point
// Practicaly, only WebServerBridge::launchAlgorithm() will be called
// WebServerBridge::launchAlgorithm() must be bound to node.js engine
//
int main()
{
  MainController &main = *(new MainController);
  std::map<std::string, std::string> *parameters = new std::map<std::string, std::string>;

  //
  // Simulate parameters conversion from node.js to c++
  parameters->insert(std::pair<std::string, std::string>("backup_file_name", "./backup/super_backup.csv"));
  parameters->insert(std::pair<std::string, std::string>("population_size", "200"));
  parameters->insert(std::pair<std::string, std::string>("mutation_rate", "0.01"));
  parameters->insert(std::pair<std::string, std::string>("foo", "bar"));
  parameters->insert(std::pair<std::string, std::string>("beer", "beer"));

  main(parameters);

  //
  // Act like a working thread
  // Simulate the main thread running node.js engine alongside
  while (42)
    std::this_thread::sleep_for(std::chrono::seconds(1));

  return 0;
}
