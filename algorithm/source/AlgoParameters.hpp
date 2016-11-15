#ifndef		ALGOPARAMETERS_HPP_
# define	ALGOPARAMETERS_HPP_

# include <string>

# include "IParameters.hpp"

class		AlgoParameters : public IParameters
{
public:
  const int populationSize;
  const float populationRenewalRate; // part of the population killed and renewed
  const float mutationRate; // mutation probability
  const int simulationCycles; // number of cycles for a simulation

  AlgoParameters(int, float, float, int);
  AlgoParameters();
  virtual ~AlgoParameters();
};

#endif		/* !ALGOPARAMETERS_HPP_ */
