#ifndef		PHYSICS_HPP_
# define	PHYSICS_HPP_

# include <map>
# include <string>
# include "VrepAPI.hpp"

class		Physics
{
public:
  class Object;

private:
  vrep::handle_t _worldHandle;
  std::map<std::string, Object *> _objects;

public:
  Physics();
  ~Physics();

  bool enterTheMatrix();
  void getOffTheMatrix();
  bool startSimulation();
  bool endSimulation();
  Object *getObject(const std::string &);
};

#endif		/* !PHYSICS_HPP_ */
