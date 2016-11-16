#ifndef		WORLD_HPP_
# define	WORLD_HPP_

# include <vector>

# include "MotherNature.hpp"
# include "Physics.hpp"
# include "Individual.hpp"

typedef std::vector<Individual *> individuals_t;

class		World
{
protected:
  individuals_t _population;
  MotherNature _random;

public:
  World();
  virtual ~World();
};

#endif		/* !WORLD_HPP_ */
