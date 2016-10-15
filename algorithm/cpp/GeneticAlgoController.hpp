#ifndef		GENETICALGOCONTROLLER_HPP_
# define	GENETICALGOCONTROLLER_HPP_

# include "AThreadedDataHandler.hpp"
# include "AlgoParameters.hpp"

class MainController;

class		GeneticAlgoController : public AThreadedDataHandler
{
private:
  MainController &_mainController;

public:
  GeneticAlgoController(MainController &);
  ~GeneticAlgoController();

  // Inherited from IDataHandler & AThreadedDataHandler
  virtual void handleNewResult(const ResultModel *);
  virtual void handleNewResult();

  // Inherited from AThreadedDataHandler
  virtual void operator()();
  virtual void operator()(const AlgoParameters *);
  virtual void _workLoop();
};

#endif		/* !GENETICALGOCONTROLLER_HPP_ */
