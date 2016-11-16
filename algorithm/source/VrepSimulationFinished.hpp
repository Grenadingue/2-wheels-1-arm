#ifndef		VREPSIMULATIONFINISHED_HPP_
# define	VREPSIMULATIONFINISHED_HPP_

# include "IEvent.hpp"
# include "Individual.hpp"

class		VrepSimulationFinished : public IEvent
{
public:
  enum eStatus : int
    {
      SUCCESS,
      FAILURE,
    };

private:
  Individual *_individual;

public:
  const eStatus status;

public:
  VrepSimulationFinished(Individual *, eStatus);
  virtual ~VrepSimulationFinished();

  Individual *individual();
};

#endif		/* !VREPSIMULATIONFINISHED_HPP_ */
