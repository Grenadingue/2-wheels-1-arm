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
  Physics _physics;
  _2w1a *_robot;

public:
  World();
  virtual ~World();

protected:
  bool _enterVirtualWorld();
  void _leaveVirtualWorld();
  bool _startSimulation();
  bool _stopSimulation();
  _2w1a *_retrieve2w1a();
};

#endif		/* !WORLD_HPP_ */
