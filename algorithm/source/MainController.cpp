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

void MainController::operator()(const std::map<std::string, std::string> *rawParams)
{
  AlgoParameters *algoParams = new AlgoParameters(0, 0, 0, 0);
  std::string *dataBackupFileName = new std::string;

  if (!_parseParameters(*rawParams, *algoParams, *dataBackupFileName))
    {
      std::cerr << "Error: Parameters parsing failure" << std::endl <<
	"Aborting" << std::endl;
      return;
    }

  _initControllers(algoParams, dataBackupFileName);
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

bool MainController::_parseParameters(const std::map<std::string, std::string> &rawParams,
				      AlgoParameters &params, std::string &dataBackupFileName)
{
  (void)params;
  (void)dataBackupFileName;

  std::cout << "[C++_ADDON] Input parameters:" << std::endl;
  for (auto parameter : rawParams)
    {
      std::cout << "\t" << parameter.first << " = " << parameter.second << std::endl;
    }
  return true;
}

void MainController::_initControllers(const AlgoParameters *algoParams,
				      const std::string *dataBackupFileName)
{
  _webServerBridge = new WebServerBridge;
  _backupData = new BackupDataController;
  _geneticAlgorithm = new GeneticAlgoController(*this);

  (*_webServerBridge)();
  (*_backupData)(dataBackupFileName);
  (*_geneticAlgorithm)(algoParams);
}
