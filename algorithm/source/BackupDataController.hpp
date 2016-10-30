#ifndef		BACKUPDATACONTROLLER_HPP_
# define	BACKUPDATACONTROLLER_HPP_

# include <string>
# include "AThreadedDataHandler.hpp"

class		BackupDataController : public AThreadedDataHandler
{

public:
  BackupDataController();
  ~BackupDataController();

  // Inherited from AThreadedDataHandler
  virtual void operator()();
  virtual void operator()(const std::string *);
  virtual void _workLoop();
};

#endif		/* !BACKUPDATACONTROLLER_HPP_ */
