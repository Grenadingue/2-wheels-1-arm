#include "_2w1a.hpp"

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
