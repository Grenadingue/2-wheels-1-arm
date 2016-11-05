#ifndef		OBJECT_HPP_
# define	OBJECT_HPP_

# include "Physics.hpp"

class		Physics::Object
{
protected:
  Physics &_world;
  vrep::handle_t _handle;

public:
  Object(Physics &, vrep::handle_t);
  Object(const Object &);
  virtual ~Object();

  Object &operator=(const Object &);

  bool getPositionOnMap(vrep::position_t &);
  bool getOrientationOnMap(vrep::orientation_t &);
};

#endif		/* !OBJECT_HPP_ */
