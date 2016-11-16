#ifndef		IDATAHANDLER_HPP_
# define	IDATAHANDLER_HPP_

# include "ResultModel.hpp"

class		IDataHandler
{

public:
  virtual ~IDataHandler() {}

  virtual void handleNewResult(const IEvent *) = 0;
};

#endif		/* !IDATAHANDLER_HPP_ */
