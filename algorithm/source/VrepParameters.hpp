#ifndef		VREPPARAMETERS_HPP_
# define	VREPPARAMETERS_HPP_

# include <string>

# include "IParameters.hpp"

class		VrepParameters : public IParameters
{
public:
  const unsigned short serverPort;

  VrepParameters(unsigned short);
  virtual ~VrepParameters();
};

#endif		/* !VREPPARAMETERS_HPP_ */
