#include <iostream>
#include <thread>
#include <chrono>
#include "BackupDataController.hpp"
#include "WritableResultModel.hpp"

BackupDataController::BackupDataController(const IParameters *parameters)
  : AThreadedDataHandler(parameters),
    _parameters(static_cast<const BackupDataParameters *>(parameters))
{
}

BackupDataController::~BackupDataController()
{
  std::cout << "BackupDataController::~BackupDataController" << std::endl;
}

void BackupDataController::_workLoop()
{
  const ResultModel *result = NULL;
  std::ofstream stream;

  stream.open(_parameters->filePath, std::ofstream::out);
  while (!_close)
    {
      result = NULL;
      if ((result = static_cast<const ResultModel *>(_getNextResult())))
	{
	  const WritableResultModel & wResult = *static_cast<const WritableResultModel *>(result);

	  stream << wResult;
	  delete result;
	}
      std::this_thread::sleep_for(std::chrono::milliseconds(300));
    }
}
