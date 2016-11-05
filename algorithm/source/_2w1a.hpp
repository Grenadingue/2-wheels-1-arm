#ifndef		_2W1A_HPP_
# define	_2W1A_HPP_

# include "Object.hpp"
# include "Articulation.hpp"

class		_2w1a : public Physics::Object
{
private:
  Physics::Articulation &_wrist;
  Physics::Articulation &_elbow;
  Physics::Articulation &_shoulder;

public:
  _2w1a(const Physics::Object &, Physics::Object &, Physics::Object &, Physics::Object &);
  virtual ~_2w1a();

  Physics::Articulation &wrist();
  Physics::Articulation &elbow();
  Physics::Articulation &shoulder();
};

#endif		/* !_2W1A_HPP_ */
