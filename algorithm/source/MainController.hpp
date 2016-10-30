#ifndef		MAINCONTROLLER_HPP_
# define	MAINCONTROLLER_HPP_

# include <map>
# include <string>
# include "IDataHandler.hpp"
# include "AlgoParameters.hpp"

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

  void operator()(const std::map<std::string, std::string> *);

  // Inherited from IDataHandler
  virtual void handleNewResult(const ResultModel *);

  void handleFinishedJob();

private:
  bool _parseParameters(const std::map<std::string, std::string> &, AlgoParameters &, std::string &);
  void _initControllers(const AlgoParameters *, const std::string *);
};

#endif		/* !MAINCONTROLLER_HPP_ */
