#ifndef		MAINCONTROLLER_HPP_
# define	MAINCONTROLLER_HPP_

# include <map>
# include <string>
# include "IDataHandler.hpp"

class WebServerBridgeParameters;
class BackupDataParameters;
class AlgoParameters;

class WebServerBridge;
class BackupDataController;
class GeneticAlgoController;

class		MainController : public IDataHandler
{
private:
  WebServerBridge *_webServerBridge;
  BackupDataController *_backupData;
  GeneticAlgoController *_geneticAlgorithm;

public:
  MainController();
  ~MainController();

  void operator()(std::map<std::string, std::string> *);

  // Inherited from IDataHandler
  virtual void handleNewResult(const IEvent *);

  void handleFinishedJob();

private:
  bool _parseParameters(std::map<std::string, std::string> &,
			AlgoParameters *&,
			WebServerBridgeParameters *&,
			BackupDataParameters *&);
  void _initControllers(const AlgoParameters *,
			const WebServerBridgeParameters *,
			const BackupDataParameters *);
};

#endif		/* !MAINCONTROLLER_HPP_ */
