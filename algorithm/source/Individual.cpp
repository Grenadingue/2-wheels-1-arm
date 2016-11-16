#include "Individual.hpp"

Individual::Individual()
  : _body(NULL)
{
}

Individual::~Individual()
{
}

void Individual::useBody(_2w1a *body)
{
  _body = body;
}

_2w1a *Individual::body()
{
  return _body;
}
