#ifndef		_2W1A_HPP_
# define	_2W1A_HPP_

# include <chrono>
# include <thread>
# include "Object.hpp"
# include "Articulation.hpp"

class		_2w1a : public Physics::Object
{
private:
  Physics::Articulation &_wrist;
  Physics::Articulation &_elbow;
  Physics::Articulation &_shoulder;
  vrep::position_t	_lastPosition;
  bool			_firstMove;
  
public:
  _2w1a(const Physics::Object &, Physics::Object &, Physics::Object &, Physics::Object &);
  virtual ~_2w1a();

protected:
  bool	checkDifference(vrep::position_t &) const;

public:  
  Physics::Articulation &wrist();
  Physics::Articulation &elbow();
  Physics::Articulation &shoulder();

  bool isMoving();
  void waitWhileMoving();
};

#endif		/* !_2W1A_HPP_ */
