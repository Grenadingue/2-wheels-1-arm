#ifndef		BACKUPDATAPARAMETERS_HPP_
# define	BACKUPDATAPARAMETERS_HPP_

# include <string>

# include "IParameters.hpp"

class		BackupDataParameters : public IParameters
{
public:
  const std::string filePath;

  BackupDataParameters(const std::string &);
  virtual ~BackupDataParameters();
};

#endif		/* !BACKUPDATAPARAMETERS_HPP_ */
