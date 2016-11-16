#include "_2w1a.hpp"
#include <iostream>

_2w1a::_2w1a(const Physics::Object &robot,
	     Physics::Object &wrist, Physics::Object &elbow, Physics::Object &shoulder)
  : Object(robot),
    _wrist(static_cast<Physics::Articulation &>(wrist)),
    _elbow(static_cast<Physics::Articulation &>(elbow)),
    _shoulder(static_cast<Physics::Articulation &>(shoulder))
{
}

_2w1a::~_2w1a()
{
}

bool	_2w1a::checkDifference(vrep::position_t &currentPosition) const
{
  float	totalOld = 0;
  float	totalCurrent = 0;
  float buffer = 0;
  
  totalOld = _lastPosition.x + _lastPosition.y + _lastPosition.z;
  totalCurrent = currentPosition.x + currentPosition.y + currentPosition.z;
  buffer = totalCurrent - totalOld;
  if (buffer < 0)
    buffer *= -1;
  if (buffer > 0.0015)
    return true;
  return false;
}

Physics::Articulation &_2w1a::wrist()
{
  return _wrist;
}

Physics::Articulation &_2w1a::elbow()
{
  return _elbow;
}

Physics::Articulation &_2w1a::shoulder()
{
  return _shoulder;
}

bool	_2w1a::isMoving()
{
  vrep::position_t	currentPosition;
  
  if (!getPositionOnMap(currentPosition))
    return false;
  if (_firstMove == true)
    {
      _lastPosition = currentPosition;
      _firstMove = false;
      return true;
    }
  if (checkDifference(currentPosition))
    {
      _lastPosition = currentPosition;
      return true;
    }
  return false;
}

void	_2w1a::waitWhileMoving()
{
  while (isMoving())
    std::this_thread::sleep_for(std::chrono::milliseconds(600));
}
