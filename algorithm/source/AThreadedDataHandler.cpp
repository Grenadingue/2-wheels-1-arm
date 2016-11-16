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

void AThreadedDataHandler::handleNewResult(const IEvent *event)
{
  _mutex.lock();
  _events.push(event);
  _mutex.unlock();
}

const IEvent *AThreadedDataHandler::_getNextResult()
{
  const IEvent *event = NULL;

  _mutex.lock();
  if (!_events.empty())
    {
      event = _events.front();
      _events.pop();
    }
  _mutex.unlock();
  return event;
}
