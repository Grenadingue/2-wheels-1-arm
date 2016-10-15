#include <iostream>
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
  unsigned long int i = 0;

  while (!_close && i != 5)
    {
      std::cout << "Genetic algorithm controller: Waiting" << std::endl;
      std::this_thread::sleep_for(std::chrono::seconds(1));
      //
      // Update parameters and pass results to it
      handleNewResult();
      ++i;
    }
  std::cout << "Genetic algorithm job finished: Closing" << std::endl;
  _mainController.handleFinishedJob();
}
