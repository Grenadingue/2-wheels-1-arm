#ifndef		MAINCONTROLLER_HPP_
# define	MAINCONTROLLER_HPP_

# include <list>
# include <string>
# include "IDataHandler.hpp"
# include "WebServerBridge.hpp"
# include "BackupDataController.hpp"
# include "GeneticAlgoController.hpp"
# include "AlgoParameters.hpp"

class		MainController : public IDataHandler
{
private:
  WebServerBridge *_webServerBridge;
  BackupDataController *_backupData;
  GeneticAlgoController *_geneticAlgorithm;

public:
  MainController();
  ~MainController();

  void operator()(const std::list<std::string> *);

  // Inherited from IDataHandler
  virtual void handleNewResult(const ResultModel *);

  void handleFinishedJob();

private:
  bool _parseParameters(const std::list<std::string> &, AlgoParameters &, std::string &);
  void _initControllers(const AlgoParameters *, const std::string *);
};

#endif		/* !MAINCONTROLLER_HPP_ */
