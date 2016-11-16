#include "Individual.hpp"
#include "Fitness.hpp"

Individual::Individual()
  :  _fitness(new Fitness), _body(NULL)
{
}

Individual::~Individual()
{
}

Fitness& Individual::fitness()
{
  return *_fitness;
}

void Individual::useBody(_2w1a *body)
{
  _body = body;
}

_2w1a *Individual::body()
{
  return _body;
}

Individual::Genome	&Individual::genome()
{
  return *_genome;
}
