#ifndef		GENETICALGOCONTROLLER_HPP_
# define	GENETICALGOCONTROLLER_HPP_

# include "AThreadedDataHandler.hpp"
# include "VrepThreadedController.hpp"
# include "AlgoParameters.hpp"
# include "VrepSimulationEvent.hpp"
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

  // Used to sort the population
  static bool sortIndividuals(Individual *first, Individual *seccond);

  // Inherited from IDataHandler & AThreadedDataHandler
  virtual void handleNewResult(const ResultModel *);
  virtual void handleNewResult();

  // Inherited from AThreadedDataHandler
  virtual void _workLoop();

private:
  // Emit algorithm data
  void _emitTheoreticalMaxScore();
  void _emitNewResult(unsigned long long int);
  void _emitSolutionFound();

  // Vrep pool
  bool _instanciateVrepPool();
  void _cleanVrepPool();
  void _pushSimulationEvent(VrepSimulationEvent *);
  void _waitForSimulationsResults();

  // Genetic algorithm
  void _geneticAlgorithm();
  bool _solutionFound();
  bool _initializePopulation();
  bool _evaluateFitness();

  // Fitness
  void _rateIndividual(Individual &individual);
  void _sortPopulationByScoreDesc();

  // Offspring generation
  std::vector<Individual *> *_generateOffSpring();
  std::pair<Individual *, Individual *> _selectParents();
  Individual *_itsSexTime(std::pair<Individual *, Individual *> &parents);
  void _mutateChildGenome(Individual &child);
  void _insertChildrenInPopulation(std::vector<Individual *> *children);

  // Kill a part of the population
  void _harshLife();

  // Get best solution
  Individual *_bestSolution();
};

#endif		/* !GENETICALGOCONTROLLER_HPP_ */
