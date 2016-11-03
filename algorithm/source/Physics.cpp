#include "Physics.hpp"

Physics::Physics()
  : _worldHandle(-1)
{
}

Physics::~Physics()
{
}

bool Physics::enterTheMatrix()
{
  return vrep::start("localhost", 19997) != -1;
}

void Physics::getOffTheMatrix()
{
  vrep::finish(_worldHandle);
}

bool Physics::startSimulation()
{
  return vrep::startSimulation(_worldHandle) == 0;
}

bool Physics::endSimulation()
{
  return vrep::stopSimulation(_worldHandle) == 0;
}

Physics::Object *Physics::getObject(const std::string &name)
{
  (void)name;
  return NULL;
}
