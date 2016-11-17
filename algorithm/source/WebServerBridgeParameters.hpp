#ifndef		WEBSERVERBRIDGEPARAMETERS_HPP_
# define	WEBSERVERBRIDGEPARAMETERS_HPP_

# include <string>

# include "IParameters.hpp"

class		WebServerBridgeParameters : public IParameters
{
public:
  const unsigned short serverPort;

  WebServerBridgeParameters(unsigned short);
  virtual ~WebServerBridgeParameters();
};

#endif		/* !WEBSERVERBRIDGEPARAMETERS_HPP_ */
