#ifndef		GENETICALGOCONTROLLER_HPP_
# define	GENETICALGOCONTROLLER_HPP_

# include "AThreadedDataHandler.hpp"
# include "VrepThreadedController.hpp"
# include "AlgoParameters.hpp"
# include "World.hpp"

class MainController;

class		GeneticAlgoController : public AThreadedDataHandler, public World
{
private:
  MainController &_mainController;
  const AlgoParameters *_parameters;
  std::vector<VrepThreadedController *> _vrepPool;

public:
  GeneticAlgoController(const IParameters *, MainController &);
  virtual ~GeneticAlgoController();

  // Inherited from IDataHandler & AThreadedDataHandler
  virtual void handleNewResult(const ResultModel *);
  virtual void handleNewResult();

  // Inherited from AThreadedDataHandler
  virtual void _workLoop();

  // emit algorithm data
  void _emitTheoreticalMaxScore();
  void _emitNewResult(unsigned long long int);
  void _emitSolutionFound();

  // vrep pool
  bool _instanciateVrepPool();
  void _cleanVrepPool();

  // Genetic algorithm
  void _geneticAlgorithm();
  bool _solutionFound();
  bool _initializePopulation();
  bool _evaluateFitness();
};

#endif		/* !GENETICALGOCONTROLLER_HPP_ */
