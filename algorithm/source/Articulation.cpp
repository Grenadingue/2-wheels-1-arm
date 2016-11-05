#include "Articulation.hpp"
#include "Maths.hpp"

Physics::Articulation::~Articulation()
{
}

bool Physics::Articulation::getPosition(float &position)
{
  if (vrep::getJointPosition(_world._handle, _handle, position) != vrep::eReturn::OK)
    return false;
  position = Maths::Radians<float>::toDegrees(position);
  return true;
}

bool Physics::Articulation::setTargetPosition(float position)
{
  position = Maths::Degrees<float>::toRadians(position);
  return vrep::setJointTargetPosition(_world._handle, _handle, position) == vrep::eReturn::OK;
}
