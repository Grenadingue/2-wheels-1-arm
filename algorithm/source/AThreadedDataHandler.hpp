#ifndef		ATHREADEDDATAHANDLER_HPP_
# define	ATHREADEDDATAHANDLER_HPP_

# include <thread>
# include <mutex>
# include <queue>

# include "IParameters.hpp"
# include "IDataHandler.hpp"

class		AThreadedDataHandler : public IDataHandler
{
protected:
  std::thread _thread;
  std::mutex _mutex;
  std::queue<const IEvent *> _events;
  bool _close;
  const IParameters *_parameters;

public:
  AThreadedDataHandler(const IParameters *);
  virtual ~AThreadedDataHandler();

  virtual void operator()();
  virtual void _workLoop() = 0;

  virtual void askForClose();
  virtual void waitForClose();
  virtual void askAndWaitForClose();

  // Inherited from IDataHandler
  virtual void handleNewResult(const IEvent *);

protected:
  const IEvent *_getNextResult();
};

#endif		/* !ATHREADEDDATAHANDLER_HPP_ */
