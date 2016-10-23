#ifndef		WEBSERVERBRIDGE_HPP_
# define	WEBSERVERBRIDGE_HPP_

# include "AThreadedDataHandler.hpp"

class		WebServerBridge : public AThreadedDataHandler
{
private:
  class Client;

  Client *_client;

public:
  WebServerBridge();
  ~WebServerBridge();

  static void launchAlgorithm();

  // Inherited from AThreadedDataHandler
  virtual void _workLoop();
};

#endif		/* !WEBSERVERBRIDGE_HPP_ */
