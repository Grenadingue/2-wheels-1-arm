#include "Random.hpp"

Random::Random()
  : _generator(std::random_device()())
{
}

Random::~Random()
{
}
