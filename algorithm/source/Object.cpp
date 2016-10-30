#include "Object.hpp"
#include "VrepAPI.hpp"

Physics::Object::Object()
{
}

Physics::Object::Object(const Object &other)
{
  (void)other;
}

Physics::Object::~Object()
{
}

Physics::Object &Physics::Object::operator=(const Object &other)
{
  (void)other;
  return (*this);
}
