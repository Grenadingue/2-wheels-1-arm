#include <sstream>
#include <iostream>
#include "MainController.hpp"
#include "WebServerBridge.hpp"
#include "BackupDataController.hpp"
#include "GeneticAlgoController.hpp"

MainController::MainController()
{
}

MainController::~MainController()
{
}

void MainController::operator()(std::map<std::string, std::string> *rawParams)
{
  AlgoParameters *algoParams = NULL;
  WebServerBridgeParameters *webServerParams = NULL;
  BackupDataParameters *backupDataParams = NULL;

  if (!_parseParameters(*rawParams, algoParams, webServerParams, backupDataParams))
    {
      std::cerr << "Error: Parameters parsing failure" << std::endl
		<< "Aborting" << std::endl;
      return;
    }

  _initControllers(algoParams, webServerParams, backupDataParams);
}

void MainController::handleNewResult(const IEvent *result)
{
  _webServerBridge->handleNewResult(new ResultModel(static_cast<const ResultModel *>(result)));
  _backupData->handleNewResult(result);
}

void MainController::handleFinishedJob()
{
  _webServerBridge->askForClose();
  _backupData->askForClose();

  _webServerBridge->waitForClose();
  _backupData->waitForClose();

  delete _webServerBridge;
  delete _backupData;

  _webServerBridge = NULL;
  _backupData = NULL;

  delete this;
}

void split(const std::string &s, char delim, std::vector<std::string> &elems)
{
  std::stringstream ss;
  ss.str(s);
  std::string item;
  while (std::getline(ss, item, delim))
    {
      elems.push_back(item);
    }
}

std::vector<std::string> split(const std::string &s, char delim)
{
  std::vector<std::string> elems;
  split(s, delim, elems);
  return elems;
}

bool MainController::_parseParameters(std::map<std::string, std::string> &rawParams,
				      AlgoParameters *&algoParams,
				      WebServerBridgeParameters *&webServerParams,
				      BackupDataParameters *&backupDataParams)
{
  if (rawParams.find("populationSize") != rawParams.end() ||
      rawParams.find("populationRenewalRate") != rawParams.end() ||
      rawParams.find("mutationRate") != rawParams.end() ||
      rawParams.find("simulationCycles") != rawParams.end() ||
      rawParams.find("vrepPool") != rawParams.end())
    {
      int populationSize = std::stoi(rawParams["populationSize"]);
      float populationRenewalRate = std::stof(rawParams["populationRenewalRate"]);
      float mutationRate = std::stof(rawParams["mutationRate"]);
      int simulationCycles = std::stoi(rawParams["simulationCycles"]);

      std::vector<std::string> vrepPoolPorts = split(rawParams["vrepPool"], ',');
      std::vector<const VrepParameters *> vrepPool;

      for (std::string vrepPort : vrepPoolPorts)
	{
	  vrepPool.push_back(new VrepParameters(std::stoi(vrepPort)));
	}

      algoParams = new AlgoParameters(populationSize, populationRenewalRate,
      				      mutationRate, simulationCycles, vrepPool);
    }
  else
    return false;

  if (rawParams.find("serverPort") != rawParams.end())
    webServerParams = new WebServerBridgeParameters(std::stoi(rawParams["serverPort"]));
  else
    return false;

  if (rawParams.find("backupFile") != rawParams.end())
    backupDataParams = new BackupDataParameters(rawParams["backupFile"]);
  else
    return false;

  std::cout << "[C++_ADDON] Input parameters:" << std::endl;
  for (auto parameter : rawParams)
    {
      std::cout << "\t" << parameter.first << " = " << parameter.second << std::endl;
    }
  return true;
}

void MainController::_initControllers(const AlgoParameters *algoParams,
				      const WebServerBridgeParameters *webServerParams,
				      const BackupDataParameters *backupDataParams)
{
  _webServerBridge = new WebServerBridge(webServerParams);
  _backupData = new BackupDataController(backupDataParams);
  _geneticAlgorithm = new GeneticAlgoController(algoParams, *this);

  (*_webServerBridge)();
  (*_backupData)();
  (*_geneticAlgorithm)();
}
