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
	  delete result;
	}
      std::this_thread::sleep_for(std::chrono::milliseconds(300));
    }
}
