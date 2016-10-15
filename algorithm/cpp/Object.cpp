#include "Object.hpp"

Object::Object()
{
}

Object::Object(const Object &other)
{
  (void)other;
}

Object::~Object()
{
}

Object &Object::operator=(const Object &other)
{
  (void)other;
  return (*this);
}
