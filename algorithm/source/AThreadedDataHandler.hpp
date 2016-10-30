#ifndef		ATHREADEDDATAHANDLER_HPP_
# define	ATHREADEDDATAHANDLER_HPP_

# include <thread>
# include <mutex>
# include <queue>

# include "IDataHandler.hpp"

class		AThreadedDataHandler : public IDataHandler
{
protected:
  std::thread _thread;
  std::mutex _mutex;
  std::queue<const ResultModel *> _results;
  bool _close;

public:
  AThreadedDataHandler();
  virtual ~AThreadedDataHandler();

  virtual void operator()();
  virtual void _workLoop() = 0;

  virtual void askForClose();
  virtual void waitForClose();
  virtual void askAndWaitForClose();

  // Inherited from IDataHandler
  virtual void handleNewResult(const ResultModel *);

protected:
  const ResultModel *_getNextResult();
};

#endif		/* !ATHREADEDDATAHANDLER_HPP_ */