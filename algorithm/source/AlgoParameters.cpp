#include "AlgoParameters.hpp"

AlgoParameters::AlgoParameters(int populationSize_, float populationRenewalRate_,
			       float mutationRate_, int simulationCycles_)
  : populationSize(populationSize_), populationRenewalRate(populationRenewalRate_),
    mutationRate(mutationRate_), simulationCycles(simulationCycles_)
{
}

AlgoParameters::~AlgoParameters()
{
}
