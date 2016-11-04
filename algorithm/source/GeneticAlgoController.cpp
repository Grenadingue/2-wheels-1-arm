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
      individual = new Individual(*_robot);
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
	  for (int i = 0; i != 2; ++i)
	    {
	      vrep::position_t pos;
	      vrep::orientation_t ori;

	      if (!individual->getPositionOnMap(pos))
		{
		  std::cout << "unable to retrieve 2w1a position on map" << std::endl;
		  break;
		}
	      std::cout << "position:\tx: "
			<< pos.x << ", y: " << pos.y << ", z: " << pos.z << std::endl;
	      if (!individual->getOrientationOnMap(ori))
		{
		  std::cout << "unable to retrieve 2w1a orientation on map" << std::endl;
		  break;
		}
	      std::cout << "orient.:\tx: "
			<< ori.x << ", y: " << ori.y << ", z: " << ori.z << std::endl;

	      if (!individual->wrist().setTargetPosition(_random.realInRange<float>(0, 300)) ||
		  !individual->elbow().setTargetPosition(_random.realInRange<float>(0, 300)) ||
		  !individual->shoulder().setTargetPosition(_random.realInRange<float>(0, 300)))
		{
		  std::cout << "unable to set 2w1a articulations target postions" << std::endl;
		  break;
		}

	      std::this_thread::sleep_for(std::chrono::seconds(2));

	      float wristPos = 0, elbowPos = 0, shoulderPos = 0;

	      if (!individual->wrist().getPosition(wristPos) ||
		  !individual->elbow().getPosition(elbowPos) ||
		  !individual->shoulder().getPosition(shoulderPos))
		{
		  std::cout << "unable to set 2w1a articulations target postions" << std::endl;
		  break;
		}
	    }
	  if (!_stopSimulation())
	    {
	      std::cout << "[MATRIX] Unable to stop simulation" << std::endl;
	      return false;
	    }
	  std::this_thread::sleep_for(std::chrono::seconds(1));
	  std::cout << "[MATRIX] Simulation ended" << std::endl;
	}
    }
  return true;
}
