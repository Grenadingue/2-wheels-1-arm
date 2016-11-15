#ifndef		GENETICALGOCONTROLLER_HPP_
# define	GENETICALGOCONTROLLER_HPP_

# include "AThreadedDataHandler.hpp"
# include "AlgoParameters.hpp"
# include "World.hpp"

class MainController;

class		GeneticAlgoController : public AThreadedDataHandler, public World
{
private:
  MainController &_mainController;

public:
  GeneticAlgoController(const IParameters *, MainController &);
  virtual ~GeneticAlgoController();

  // Inherited from IDataHandler & AThreadedDataHandler
  virtual void handleNewResult(const ResultModel *);
  virtual void handleNewResult();

  // Inherited from AThreadedDataHandler
  virtual void operator()();
  virtual void operator()(const AlgoParameters *);
  virtual void _workLoop();

  // emit algorithm data
  void _emitTheoreticalMaxScore();
  void _emitNewResult(unsigned long long int);
  void _emitSolutionFound();

  // Genetic algorithm
  void _geneticAlgorithm();
  bool _solutionFound();
  bool _initializePopulation();
  bool _evaluateFitness();
};

#endif		/* !GENETICALGOCONTROLLER_HPP_ */
