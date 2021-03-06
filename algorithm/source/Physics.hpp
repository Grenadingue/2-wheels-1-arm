#ifndef		PHYSICS_HPP_
# define	PHYSICS_HPP_

# include <map>
# include <string>
# include "VrepAPI.hpp"

class		Physics
{
public:
  class Object;
  class Articulation;

private:
  vrep::handle_t _handle;
  std::map<std::string, Object *> _objects;

public:
  Physics();
  ~Physics();

  bool enterTheMatrix(unsigned short);
  void getOffTheMatrix(bool = false);
  bool startSimulation();
  bool endSimulation();
  Object *getObject(const std::string &);
};

#endif		/* !PHYSICS_HPP_ */
