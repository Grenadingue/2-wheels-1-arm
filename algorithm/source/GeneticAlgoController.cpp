#include <iostream>
#include <iomanip>
#include <chrono>
#include <algorithm>
#include "GeneticAlgoController.hpp"
#include "MainController.hpp"

bool GeneticAlgoController::sortIndividuals(Individual *first, Individual *seccond)
{
  return first->fitness().score() > seccond->fitness().score();
}

GeneticAlgoController::GeneticAlgoController(MainController &mainController)
  : _mainController(mainController)
{
}

GeneticAlgoController::~GeneticAlgoController()
{
  std::cout << "GeneticAlgoController::~GeneticAlgoController()" << std::endl;
}

void GeneticAlgoController::_rateIndividual(Individual &individual)
{
  (void) individual;
}

void GeneticAlgoController::_sortPopulationByScoreDesc()
{
  std::sort(_population.begin(), _population.end(), sortIndividuals);
}

std::vector<Individual *> *GeneticAlgoController::_generateOffSpring()
{
  return new std::vector<Individual *>();
}

std::pair<Individual *, Individual *> GeneticAlgoController::_selectParents()
{
  std::pair<Individual *, Individual *> ret;
  return ret;
}

Individual *GeneticAlgoController::_itsSexTime(std::pair<Individual *, Individual *> &parents)
{
  (void) parents;
  return NULL;
}

void GeneticAlgoController::_mutateChildGenome(Individual &child)
{
  (void) child;
}

void GeneticAlgoController::_insertChildrenInPopulation(std::vector<Individual *> *individual)
{
  _population.insert(_population.end(), individual->begin(), individual->end());
}

void GeneticAlgoController::_harshLife()
{
}

Individual *GeneticAlgoController::_bestSolution()
{
  _sortPopulationByScoreDesc();
  return _population[0];
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


void GeneticAlgoController::operator()()
{
  std::cout << "Error: Cannot start GeneticAlgoController() without parameters" << std::endl;
}

void GeneticAlgoController::operator()(const AlgoParameters *parameters)
{
  (void)parameters;
  _thread = std::thread(&GeneticAlgoController::_workLoop, this);
}

void GeneticAlgoController::_workLoop()
{
  std::cout << "[ALGO] Initializing genetic algorithm" << std::endl;
  if (_enterVirtualWorld())
    {
      std::cout << "[MATRIX] We are in the matrix" << std::endl;
      if (_retrieve2w1a())
	{
	  std::cout << "[MATRIX] 2w1a retrieved" << std::endl;
	  std::cout << std::fixed << std::setprecision(8); // set float precision
	  _geneticAlgorithm();
	}
      else
	std::cout << "[MATRIX] Unable to retrieve 2w1a" << std::endl;
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
  _leaveVirtualWorld();
  std::cout << "[MATRIX] We leaved the matrix" << std::endl;
}

bool GeneticAlgoController::_solutionFound()
{
  return false;
}

bool GeneticAlgoController::_initializePopulation()
{
  Individual *individual = NULL;

  for (int i = 0; i != 5; ++i)
    {
      individual = new Individual(*_robot);
      _population.push_back(individual);
    }
  return true;
}

bool GeneticAlgoController::_evaluateFitness()
{
  for (Individual *individual : _population)
    {
      std::cout << "[ALGO] Evaluating individual fitness" << std::endl;
      if (_startSimulation())
	{
	  std::cout << "[MATRIX] Simulation started" << std::endl;
	  for (int i = 0; i != 1; ++i)
	    {
	      vrep::position_t pos;
	      vrep::orientation_t ori;

	      if (!individual->getPositionOnMap(pos) || !individual->getOrientationOnMap(ori))
		{
		  std::cout << "[MATRIX] Unable to retrieve 2w1a coordinates on map" << std::endl;
		  break;
		}
	      std::cout << "[MATRIX] Position:\tx: " << (pos.x >= 0 ? " " : "") << pos.x
			<< ", y: " << (pos.y >= 0 ? " " : "") << pos.y
			<< ", z: " << (pos.z >= 0 ? " " : "") << pos.z << std::endl
			<< "[MATRIX] Orientation:\tx: " << (ori.x >= 0 ? " " : "") << ori.x
			<< ", y: " << (ori.y >= 0 ? " " : "") << ori.y
			<< ", z: " << (ori.z >= 0 ? " " : "") << ori.z << std::endl << std::endl;

	      float wristPos = _random.realInRange<float>(0, 300),
		elbowPos = _random.realInRange<float>(0, 300),
		shoulderPos = _random.realInRange<float>(0, 300);

	      std::cout << "[MATRIX] Wrist motor target position:\t\t" << wristPos
			<< " degrees" << std::endl
			<< "[MATRIX] Elbow motor target position:\t\t" << elbowPos
			<< " degrees" << std::endl
			<< "[MATRIX] Shoulder motor target position:\t" << shoulderPos
			<< " degrees" << std::endl << std::endl;

	      if (!individual->wrist().setTargetPosition(wristPos) ||
		  !individual->elbow().setTargetPosition(elbowPos) ||
		  !individual->shoulder().setTargetPosition(shoulderPos))
		{
		  std::cout << "[MATRIX] Unable to set 2w1a articulations target postions" << std::endl;
		  break;
		}

	      std::this_thread::sleep_for(std::chrono::seconds(3));

	      if (!individual->wrist().getPosition(wristPos) ||
		  !individual->elbow().getPosition(elbowPos) ||
		  !individual->shoulder().getPosition(shoulderPos))
		{
		  std::cout << "[MATRIX] Unable to set 2w1a articulations target postions" << std::endl;
		  break;
		}

	      std::cout << "[MATRIX] Wrist motor reached position:\t\t" << wristPos
			<< " degrees" << std::endl
			<< "[MATRIX] Elbow motor reached position:\t\t" << elbowPos
			<< " degrees" << std::endl
			<< "[MATRIX] Shoulder motor reached position:\t" << shoulderPos
			<< " degrees" << std::endl << std::endl;

	      if (!individual->getPositionOnMap(pos) || !individual->getOrientationOnMap(ori))
		{
		  std::cout << "[MATRIX] Unable to retrieve 2w1a coordinates on map" << std::endl;
		  break;
		}
	      std::cout << "[MATRIX] Position:\tx: " << (pos.x >= 0 ? " " : "") << pos.x
			<< ", y: " << (pos.y >= 0 ? " " : "") << pos.y
			<< ", z: " << (pos.z >= 0 ? " " : "") << pos.z << std::endl
			<< "[MATRIX] Orientation:\tx: " << (ori.x >= 0 ? " " : "") << ori.x
			<< ", y: " << (ori.y >= 0 ? " " : "") << ori.y
			<< ", z: " << (ori.z >= 0 ? " " : "") << ori.z << std::endl << std::endl;
	    }
	  if (!_stopSimulation())
	    {
	      std::cout << "[MATRIX] Unable to stop simulation" << std::endl;
	      return false;
	    }
	  std::this_thread::sleep_for(std::chrono::seconds(1));
	  std::cout << "[MATRIX] Simulation ended" << std::endl;
	}
      std::cout << std::endl;
    }
  return true;
}
