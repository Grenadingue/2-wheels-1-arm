#ifndef		WEBSERVERBRIDGE_HPP_
# define	WEBSERVERBRIDGE_HPP_

# include <map>
# include "AThreadedDataHandler.hpp"
# include "WebServerBridgeParameters.hpp"

class		WebServerBridge : public AThreadedDataHandler
{
private:
  class Client;

  Client *_client;

public:
  WebServerBridge(const IParameters *);
  ~WebServerBridge();

  // Inherited from AThreadedDataHandler
  virtual void _workLoop();
};

#endif		/* !WEBSERVERBRIDGE_HPP_ */
