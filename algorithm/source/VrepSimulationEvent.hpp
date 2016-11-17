#ifndef		VREPSIMULATIONEVENT_HPP_
# define	VREPSIMULATIONEVENT_HPP_

# include "IEvent.hpp"
# include "Individual.hpp"

class		VrepSimulationEvent : public IEvent
{
private:
  Individual *_individual;

public:
  const int simulationCycles; // number of cycles for a simulation

public:
  VrepSimulationEvent(Individual *, int);
  virtual ~VrepSimulationEvent();

  Individual *individual();
};

#endif		/* !VREPSIMULATIONEVENT_HPP_ */
