#ifndef		WEBSERVERBRIDGEPARAMETERS_HPP_
# define	WEBSERVERBRIDGEPARAMETERS_HPP_

# include <string>

# include "IParameters.hpp"

class		WebServerBridgeParameters : public IParameters
{
public:
  const std::string serverPort;

  WebServerBridgeParameters(const std::string &);
  virtual ~WebServerBridgeParameters();
};

#endif		/* !WEBSERVERBRIDGEPARAMETERS_HPP_ */
