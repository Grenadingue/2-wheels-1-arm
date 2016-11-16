#include <iostream>
#include <iomanip>
#include <chrono>
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

// not used
void GeneticAlgoController::handleNewResult()
{
}

void GeneticAlgoController::_emitTheoreticalMaxScore()
{
  ResultModel *result = new ResultModel(100);

  handleNewResult(result);
}

void GeneticAlgoController::_emitNewResult(unsigned long long int i)
{
  ResultModel *result = new ResultModel(i, i * 8, i * 4, i * 2);

  handleNewResult(result);
}

void GeneticAlgoController::_emitSolutionFound()
{
  ResultModel *result = new ResultModel(-2);

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

bool GeneticAlgoController::_solutionFound()
{
  return false;
}

bool GeneticAlgoController::_initializePopulation()
{
  Individual *individual = NULL;

  for (int i = 0; i != _parameters->populationSize; ++i)
    {
      individual = new Individual();
      _population.push_back(individual);
    }
  return true;
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
