#include "World.hpp"

#include <iostream>

World::World()
  : _robot(NULL)
{
}

World::~World()
{
}

bool World::_enterVirtualWorld()
{
  return _physics.enterTheMatrix() && ((_robot = _retrieve2w1a()) != NULL);
}

void World::_leaveVirtualWorld()
{
  _physics.getOffTheMatrix();
}

bool World::_startSimulation()
{
  return _physics.startSimulation();
}

bool World::_stopSimulation()
{
  return _physics.endSimulation();
}

_2w1a *World::_retrieve2w1a()
{
  if (!_robot)
    {
      Physics::Object *robot = NULL,
	*wrist = NULL, *elbow = NULL, *shoulder = NULL;

      robot = _physics.getObject("2W1A");
      wrist = _physics.getObject("WristMotor");
      elbow = _physics.getObject("ElbowMotor");
      shoulder = _physics.getObject("ShoulderMotor");

      if (!robot || !wrist || !elbow || !shoulder)
	return NULL;

      _robot = new _2w1a(*robot, *wrist, *elbow, *shoulder);
    }
  return _robot;
}
