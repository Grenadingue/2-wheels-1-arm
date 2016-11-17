#include "AlgoParameters.hpp"

AlgoParameters::AlgoParameters(int populationSize_, float populationRenewalRate_,
			       float mutationRate_, int simulationCycles_,
			       const std::vector<const VrepParameters *> &vrepParameters_)
  : populationSize(populationSize_), populationRenewalRate(populationRenewalRate_),
    mutationRate(mutationRate_), simulationCycles(simulationCycles_),
    vrepParameters(vrepParameters_)
{
}

AlgoParameters::~AlgoParameters()
{
}
