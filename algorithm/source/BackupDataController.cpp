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
  std::ofstream stream;

  stream.open("test_algo.json", std::ofstream::out);
  while (!_close)
    {
      result = NULL;
      if ((result = static_cast<const WritableResultModel *>(_getNextResult())))
	{
	  stream << result;
	  delete result;
	}
      std::this_thread::sleep_for(std::chrono::milliseconds(300));
    }
}
