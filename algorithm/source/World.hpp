#ifndef		WORLD_HPP_
# define	WORLD_HPP_

# include <list>

# include "MotherNature.hpp"
# include "Physics.hpp"
# include "Individual.hpp"

typedef std::list<Individual *> individuals_t;

class		World
{
protected:
  individuals_t _population;
  MotherNature _motherNature;
  Physics _physics;

public:
  World();
  virtual ~World();
};

#endif		/* !WORLD_HPP_ */
