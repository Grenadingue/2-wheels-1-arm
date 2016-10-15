#include <iostream>
#include <thread>
#include <chrono>
#include "BackupDataController.hpp"
#include "WritableResultModel.hpp"

BackupDataController::BackupDataController()
{
}

BackupDataController::~BackupDataController()
{
  std::cout << "BackupDataController::~BackupDataController" << std::endl;
}

void BackupDataController::operator()()
{
  std::cout << "Error: Cannot start BackupDataController() without parameters" << std::endl;
}

void BackupDataController::operator()(const std::string *fileName)
{
  (void)fileName;
  _thread = std::thread(&BackupDataController::_workLoop, this);
}

void BackupDataController::_workLoop()
{
  const WritableResultModel *result = NULL;

  while (!_close)
    {
      result = NULL;
      if ((result = static_cast<const WritableResultModel *>(_getNextResult())))
	{
	  std::cout << "Backup data controller got new result !" << std::endl;
	  delete result;
	}
      std::cout << "Backup data controller: Waiting" << std::endl;
      std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}
