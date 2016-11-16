#include "VrepSimulationEvent.hpp"

VrepSimulationEvent::VrepSimulationEvent(Individual *individual, int simulationCycles_)
  : _individual(individual), simulationCycles(simulationCycles_)
{
}

VrepSimulationEvent::~VrepSimulationEvent()
{
}

Individual *VrepSimulationEvent::individual()
{
  return _individual;
}
