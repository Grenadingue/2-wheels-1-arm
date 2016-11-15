#include "Individual.hpp"
#include "Fitness.hpp"

Individual::Individual(const _2w1a &robot)
  : _2w1a(robot), _fitness(new Fitness)
{
}

Individual::~Individual()
{
}

Fitness& Individual::fitness()
{
  return *_fitness;
}
