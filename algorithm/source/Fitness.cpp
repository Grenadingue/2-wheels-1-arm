#include "Fitness.hpp"

Fitness::Fitness()
  : _score(0)
{
}

Fitness::~Fitness()
{
}

int Fitness::score() const
{
  return _score;
}

void Fitness::setScore(int score)
{
  _score = score;
}
