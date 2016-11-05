#include "Object.hpp"
#include "VrepAPI.hpp"

Physics::Object::Object(Physics &world, vrep::handle_t handle)
  : _world(world), _handle(handle)
{
}

Physics::Object::Object(const Object &other)
  : _world(other._world), _handle(other._handle)
{
}

Physics::Object::~Object()
{
}

Physics::Object &Physics::Object::operator=(const Object &other)
{
  _world = other._world;
  _handle = other._handle;
  return (*this);
}


bool Physics::Object::getPositionOnMap(vrep::position_t &position)
{
  return vrep::getObjectPosition(_world._handle, _handle, position) == vrep::eReturn::OK;
}

bool Physics::Object::getOrientationOnMap(vrep::orientation_t &orientation)
{
  return vrep::getObjectOrientation(_world._handle, _handle, orientation) == vrep::eReturn::OK;
}
