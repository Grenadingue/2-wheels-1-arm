#include "Individual.hpp"
#include "Fitness.hpp"

Individual::Individual()
  :  _fitness(new Fitness), _body(NULL)
{
}


// <<<<<<< HEAD
// Individual::Individual(const _2w1a &robot)
//   : _2w1a(robot), _fitness(new Fitness)
// =======
// Individual::Individual()
//   : _body(NULL)
// >>>>>>> master
// {
// }

Individual::~Individual()
{
}

// <<<<<<< HEAD
Fitness& Individual::fitness()
{
  return *_fitness;
}
// =======
void Individual::useBody(_2w1a *body)
{
  _body = body;
}

_2w1a *Individual::body()
{
  return _body;
// >>>>>>> master
}
