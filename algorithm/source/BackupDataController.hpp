#ifndef		BACKUPDATACONTROLLER_HPP_
# define	BACKUPDATACONTROLLER_HPP_

# include <string>
# include "AThreadedDataHandler.hpp"
# include "BackupDataParameters.hpp"

class		BackupDataController : public AThreadedDataHandler
{
private:
  const BackupDataParameters *_parameters;

public:
  BackupDataController(const IParameters *);
  ~BackupDataController();

  // Inherited from AThreadedDataHandler
  virtual void _workLoop();
};

#endif		/* !BACKUPDATACONTROLLER_HPP_ */
