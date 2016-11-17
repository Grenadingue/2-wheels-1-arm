#include <iostream>
#include <iomanip>
#include <chrono>
#include <algorithm>
#include "GeneticAlgoController.hpp"
#include "MainController.hpp"

GeneticAlgoController::GeneticAlgoController(const IParameters *parameters,
					     MainController &mainController)
  : AThreadedDataHandler(parameters), _mainController(mainController),
    _parameters(static_cast<const AlgoParameters *>(parameters))
{
}

GeneticAlgoController::~GeneticAlgoController()
{
  std::cout << "GeneticAlgoController::~GeneticAlgoController()" << std::endl;
}

inline void GeneticAlgoController::handleNewResult(const ResultModel *result)
{
  _mainController.handleNewResult(result);
}

void GeneticAlgoController::handleNewResult()
{
}

void GeneticAlgoController::_emitTheoreticalMaxScore()
{
  // we define 100 as max score because we don't have fitness yet
  ResultModel *result = new ResultModel(100);

  handleNewResult(result);
}

void GeneticAlgoController::_emitNewResult(unsigned long long int i)
{
  int min = -1, max = 0;
  double average = 0;

  for (Individual *individual : _population)
    {
      int score = individual->fitness().score();

      min = (((min == -1) || (score < min)) ? score : min);
      average += score;
      max = ((score > max) ? score : max);
    }
  average = average / (float)_population.size();
  std::cout << "[ALGO] max = " << max << ", avg = " << average << ", min = " << min << std::endl;
  handleNewResult(new ResultModel(i, max, (int)average, min));
}

void GeneticAlgoController::_emitSolutionFound()
{
  // for now solution is not returned, we will display it in a speacial vrep instance
  ResultModel *result = new ResultModel(-2);

  _sortPopulationByScoreDesc();
  std::cout << "[MATRIX] Salution is:" << std::endl;
  std::cout << "[MATRIX] First movement wrist: " << _population[0]->genome()[0].wrist
	    << " ------- First movement elbow: " << _population[0]->genome()[0].elbow
	    << " ------- First movement shoulder: " << _population[0]->genome()[0].shoulder << std::endl;
  std::cout << "[MATRIX] Second movement wrist: " << _population[0]->genome()[1].wrist
	    << " ------- Second movement elbow: " << _population[0]->genome()[1].elbow
	    << " ------- Second movement shoulder: " << _population[0]->genome()[1].shoulder << std::endl;
  handleNewResult(result);
}

bool GeneticAlgoController::_instanciateVrepPool()
{
  std::cout << "[MATRIX] Instanciating vrep remote pool" << std::endl;
  for (const VrepParameters *instanceParams : _parameters->vrepParameters)
    {
      VrepThreadedController *vrepInstance = new VrepThreadedController(instanceParams, this);

      std::cout << "[MATRIX] Instanciating vrep remote api on port "
		<< instanceParams->serverPort << "..." << std::endl;
      _vrepPool.push_back(vrepInstance);
      (*vrepInstance)();
    }
  return true;
}

void GeneticAlgoController::_cleanVrepPool()
{
  for (VrepThreadedController *vrepInstance : _vrepPool)
    {
      vrepInstance->askForClose();
    }
  for (VrepThreadedController *vrepInstance : _vrepPool)
    {
      vrepInstance->waitForClose();
      delete vrepInstance;
    }
}

void GeneticAlgoController::_pushSimulationEvent(VrepSimulationEvent *event)
{
  static unsigned int vrepInstanceIndex = 0;

  if (vrepInstanceIndex >= _vrepPool.size())
    vrepInstanceIndex = 0;
  _vrepPool[vrepInstanceIndex]->handleNewResult(event);
  ++vrepInstanceIndex;
}

void GeneticAlgoController::_waitForSimulationsResults()
{
  std::cout << "[ALGO] Waiting for all simulations finished" << std::endl;
  while (_events.size() != _population.size())
    {
      std::this_thread::sleep_for(std::chrono::milliseconds(300));
    }

  std::cout << "[ALGO] All simulations finished!" << std::endl;

  _mutex.lock();
  while (!_events.empty())
    {
      _events.pop();
    }
  _mutex.unlock();
}

void GeneticAlgoController::_workLoop()
{
  std::cout << "[ALGO] Initializing genetic algorithm" << std::endl;
  if (_instanciateVrepPool())
    {
      std::cout << "[MATRIX] Matrix pool instanciated" << std::endl;
      std::cout << std::fixed << std::setprecision(8); // set float precision
      _geneticAlgorithm();
    }
  else
    std::cout << "[MATRIX] Unable to enter the matrix" << std::endl;
  std::cout << "[ALGO] Job finished: closing" << std::endl;
  std::this_thread::sleep_for(std::chrono::seconds(5));
  // wait to be sure that all emit events has been processed by other threads
  _mainController.handleFinishedJob();
}

void GeneticAlgoController::_geneticAlgorithm()
{
  unsigned long long int i = 0;

  if (!_initializePopulation())
    return;
  std::cout << "[ALGO] Population initialized" << std::endl
	    << "[ALGO] Genetic algorithm initialized" << std::endl;
  _emitTheoreticalMaxScore();
  while (!_solutionFound() && i != 8)
    {
      if (!_evaluateFitness())
	return;

      //
      // Update parameters and pass results to it
      _emitNewResult(i);
      ++i;
    }
  _emitSolutionFound();
  std::cout << "[ALGO] Solution found !" << std::endl;
  _cleanVrepPool();
  std::cout << "[MATRIX] We leaved the matrix" << std::endl;
}

bool GeneticAlgoController::_initializePopulation()
{
  Individual *individual = NULL;

  for (int i = 0; i != _parameters->populationSize; ++i)
    {
      individual = new Individual();
      individual->genome()[0].wrist = _random.realInRange<float>(0, 300);
      individual->genome()[0].shoulder = _random.realInRange<float>(0, 300);
      individual->genome()[0].elbow = _random.realInRange<float>(0, 300);
      individual->genome()[1].wrist = _random.realInRange<float>(0, 300);
      individual->genome()[1].shoulder = _random.realInRange<float>(0, 300);
      individual->genome()[1].elbow = _random.realInRange<float>(0, 300);
      _population.push_back(individual);
    }
  return true;
}

bool GeneticAlgoController::_solutionFound()
{
  return false;
}

bool GeneticAlgoController::_evaluateFitness()
{
  for (Individual *individual : _population)
    {
      VrepSimulationEvent *simulation =
	new VrepSimulationEvent(individual, _parameters->simulationCycles);

      std::cout << "[ALGO] Evaluating individual fitness" << std::endl;
      _pushSimulationEvent(simulation);
    }
  _waitForSimulationsResults();
  return true;
}

void GeneticAlgoController::_rateIndividual(Individual &individual)
{
  (void) individual;
}

bool GeneticAlgoController::sortIndividuals(Individual *first, Individual *seccond)
{
  return first->fitness().score() > seccond->fitness().score();
}

void GeneticAlgoController::_sortPopulationByScoreDesc()
{
  std::sort(_population.begin(), _population.end(), sortIndividuals);
}

Individual *GeneticAlgoController::_bestSolution()
{
  _sortPopulationByScoreDesc();
  return _population[0];
}

std::vector<Individual *> *GeneticAlgoController::_generateOffSpring()
{
  std::vector<Individual *>		*offSpring = new std::vector<Individual *>();
  int					offSpringCount = _parameters->populationRenewalRate * _parameters->populationSize;
  std::pair<Individual *, Individual *>	parents;
  int					i = 0;

  _sortPopulationByScoreDesc();
  while (i != offSpringCount)
    {
      parents = _selectParents();
      offSpring->push_back(_itsSexTime(parents));
      ++i;
    }
  _harshLife();
  _population.insert(_population.end(), offSpring->begin(), offSpring->end());
  return offSpring;
}


std::pair<Individual *, Individual *> GeneticAlgoController::_selectParents()
{
  std::pair<Individual *, Individual *> ret;

  ret.first = _population[_random.intInRange<int>(0, _parameters->populationSize - 1)];
  ret.second = _population[_random.intInRange<int>(0, _parameters->populationSize - 1)];
  return ret;
}

Individual *GeneticAlgoController::_itsSexTime(std::pair<Individual *, Individual *> &parents)
{
  Individual	*individual = new Individual();
  float		currentProbability;
  float		mutationProbability = _parameters->mutationRate * 100;
  
  // First movement wrist
  currentProbability = _random.realInRange<float>(0, 100);
  if (mutationProbability > currentProbability)
    individual->genome()[0].wrist = _mutateChildGenome();
  else
    individual->genome()[0].wrist = getRandomGene(parents);
  // First movement elbow
  currentProbability = _random.realInRange<float>(0, 100);
  if (mutationProbability > currentProbability)
    individual->genome()[0].elbow = _mutateChildGenome();
  else
    individual->genome()[0].elbow =  getRandomGene(parents);
  // First movement shoulder
  currentProbability = _random.realInRange<float>(0, 100);
  if (mutationProbability > currentProbability)
    individual->genome()[0].shoulder = _mutateChildGenome();
  else
    individual->genome()[0].shoulder =  getRandomGene(parents);
  // Second movement wrist
  currentProbability = _random.realInRange<float>(0, 100);
  if (mutationProbability > currentProbability)
    individual->genome()[1].wrist = _mutateChildGenome();
  else
    individual->genome()[1].wrist =  getRandomGene(parents);
  // Second movement elbow
  currentProbability = _random.realInRange<float>(0, 100);
  if (mutationProbability > currentProbability)
    individual->genome()[1].elbow = _mutateChildGenome();
  else
    individual->genome()[1].elbow =  getRandomGene(parents);
  // Second movement shoulder
  currentProbability = _random.realInRange<float>(0, 100);
  if (mutationProbability > currentProbability)
    individual->genome()[1].shoulder = _mutateChildGenome();
  else
    individual->genome()[1].shoulder =  getRandomGene(parents);
  return individual;
}

float GeneticAlgoController::getRandomGene(std::pair<Individual *, Individual *> &parents)
{
  int selected = _random.intInRange<int>(0, 5);
  int movement = _random.intInRange<int>(0, 1);
  
  if (selected == 0)
    return parents.first->genome()[movement].wrist;
  else if (selected == 1)
    return parents.first->genome()[movement].elbow;
  else if (selected == 2)
    return parents.first->genome()[movement].shoulder;
  else if (selected == 3)
    return parents.second->genome()[movement].wrist;
  else if (selected == 4)
    return parents.second->genome()[movement].elbow;
  else if (selected == 5)
    return parents.second->genome()[movement].shoulder;
  return 0;
}

float GeneticAlgoController::_mutateChildGenome()
{
  return _random.realInRange<float>(0, 300);
}

void GeneticAlgoController::_insertChildrenInPopulation(std::vector<Individual *> *individual)
{
  _population.insert(_population.end(), individual->begin(), individual->end());
}

void GeneticAlgoController::_harshLife()
{
  _population.erase(_population.end() - _parameters->populationRenewalRate * _parameters->populationSize, _population.end());
}
