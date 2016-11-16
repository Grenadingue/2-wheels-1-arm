#ifndef		ALGOPARAMETERS_HPP_
# define	ALGOPARAMETERS_HPP_

# include <string>
# include <vector>

# include "IParameters.hpp"
# include "VrepParameters.hpp"

class		AlgoParameters : public IParameters
{
public:
  const int populationSize;
  const float populationRenewalRate; // part of the population killed and renewed
  const float mutationRate; // mutation probability
  const int simulationCycles; // number of cycles for a simulation
  const std::vector<const VrepParameters *> vrepParameters;

  AlgoParameters(int, float, float, int, const std::vector<const VrepParameters *> &);
  AlgoParameters();
  virtual ~AlgoParameters();
};

#endif		/* !ALGOPARAMETERS_HPP_ */
