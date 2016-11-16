#include "VrepSimulationFinished.hpp"

VrepSimulationFinished::VrepSimulationFinished(Individual *individual, eStatus status_)
  : _individual(individual), status(status_)
{
}

VrepSimulationFinished::~VrepSimulationFinished()
{
}

Individual *VrepSimulationFinished::individual()
{
  return _individual;
}
