#include "AThreadedDataHandler.hpp"

AThreadedDataHandler::AThreadedDataHandler(const IParameters *parameters)
  : _close(false), _parameters(parameters)
{
}

AThreadedDataHandler::~AThreadedDataHandler()
{
}

void AThreadedDataHandler::operator()()
{
  _thread = std::thread(&AThreadedDataHandler::_workLoop, this);
}

inline void AThreadedDataHandler::askForClose()
{
  _close = true;
}

inline void AThreadedDataHandler::waitForClose()
{
  _thread.join();
}

inline void AThreadedDataHandler::askAndWaitForClose()
{
  askForClose();
  waitForClose();
}

void AThreadedDataHandler::handleNewResult(const ResultModel *result)
{
  _mutex.lock();
  _results.push(result);
  _mutex.unlock();
}

const ResultModel *AThreadedDataHandler::_getNextResult()
{
  const ResultModel *result = NULL;

  _mutex.lock();
  if (!_results.empty())
    {
      result = _results.front();
      _results.pop();
    }
  _mutex.unlock();
  return result;
}
