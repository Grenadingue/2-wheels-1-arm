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

void MainController::handleNewResult(const ResultModel *result)
{
  _webServerBridge->handleNewResult(new ResultModel(result));
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

bool MainController::_parseParameters(std::map<std::string, std::string> &rawParams,
				      AlgoParameters *&algoParams,
				      WebServerBridgeParameters *&webServerParams,
				      BackupDataParameters *&backupDataParams)
{
  if (rawParams.find("populationSize") != rawParams.end() ||
      rawParams.find("populationRenewalRate") != rawParams.end() ||
      rawParams.find("mutationRate") != rawParams.end() ||
      rawParams.find("simulationCycles") != rawParams.end())
    {
      int populationSize = std::stoi(rawParams["populationSize"]);
      float populationRenewalRate = std::stof(rawParams["populationRenewalRate"]);
      float mutationRate = std::stof(rawParams["mutationRate"]);
      int simulationCycles = std::stoi(rawParams["simulationCycles"]);
      algoParams = new AlgoParameters(populationSize, populationRenewalRate,
				      mutationRate, simulationCycles);
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

  algoParams = new AlgoParameters(0, 0, 0, 0);
  webServerParams = new WebServerBridgeParameters(8081);
  backupDataParams = new BackupDataParameters("test_algo.json");

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
