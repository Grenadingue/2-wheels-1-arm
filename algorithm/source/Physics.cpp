#include "Physics.hpp"
#include "Object.hpp"

Physics::Physics()
  : _handle(vrep::eHandle::INVALID)
{
}

Physics::~Physics()
{
  for (auto objectKeyValue : _objects)
    delete objectKeyValue.second;
}

bool Physics::enterTheMatrix(unsigned short port)
{
  return vrep::start("127.0.0.1", port, _handle);
}

void Physics::getOffTheMatrix(bool force)
{
  if (_handle != vrep::eHandle::INVALID || force)
    vrep::finish(_handle);
}

bool Physics::startSimulation()
{
  return vrep::startSimulation(_handle) == vrep::eReturn::OK;
}

bool Physics::endSimulation()
{
  return vrep::stopSimulation(_handle) == vrep::eReturn::OK;
}

Physics::Object *Physics::getObject(const std::string &name)
{
  vrep::handle_t objectHandle = vrep::eHandle::INVALID;
  Object *object = NULL;

  if (_objects.find(name) != _objects.end())
    object = _objects[name];
  else
    {
      if (vrep::getObjectHandle(_handle, name, objectHandle) != vrep::eReturn::OK)
	return NULL;
      object = new Object(*this, objectHandle);
      _objects[name] = object;
    }
  return object;
}
