#include <iostream>
#include <iomanip>
#include <chrono>
#include "GeneticAlgoController.hpp"
#include "MainController.hpp"

GeneticAlgoController::GeneticAlgoController(MainController &mainController)
  : _mainController(mainController)
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
  ResultModel *result = new ResultModel;

  //
  // ResultModel should be filled here

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
  std::cout << "Genetic algorithm job finished: Closing" << std::endl;
  _mainController.handleFinishedJob();
}

void GeneticAlgoController::_geneticAlgorithm()
{
  unsigned long long int i = 0;

  if (!_initializePopulation())
    return;
  std::cout << "[MATRIX] population initialized" << std::endl;
  while (!_solutionFound() && i != 1)
    {
      if (!_evaluateFitness())
	return;
      //
      // Update parameters and pass results to it
      handleNewResult();
      ++i;
    }
  _leaveVirtualWorld();
  std::cout << "[MATRIX] We are outside the matrix" << std::endl;
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
      if (!(individual = new Individual(*_robot)))
	{
	  std::cout << "[MATRIX] cannot create individual" << std::endl;
	  return false;
	}
      _population.push_back(individual);
    }
  return true;
}

bool GeneticAlgoController::_evaluateFitness()
{
  for (Individual *individual : _population)
    {
      if (_startSimulation())
	{
	  std::cout << "[MATRIX] Simulation started" << std::endl;
	  for (int i = 0; i != 3; ++i)
	    {
	      vrep::position_t pos;
	      vrep::orientation_t ori;

	      if (!individual->getPositionOnMap(pos))
		{
		  std::cout << "unable to retrieve 2w1a position on map" << std::endl;
		  return false;
		}
	      std::cout << "position:\tx: "
			<< pos.x << ", y: " << pos.y << ", z: " << pos.z << std::endl;
	      if (!individual->getOrientationOnMap(ori))
		{
		  std::cout << "unable to retrieve 2w1a orientation on map" << std::endl;
		  return false;
		}
	      std::cout << "orient.:\tx: "
			<< ori.x << ", y: " << ori.y << ", z: " << ori.z << std::endl;
	    }
	  if (_stopSimulation())
	    std::cout << "[MATRIX] Simulation ended" << std::endl;
	  else
	    {
	      std::cout << "[MATRIX] Unable to stop simulation" << std::endl;
	      return false;
	    }
	}
    }
  return true;
}
