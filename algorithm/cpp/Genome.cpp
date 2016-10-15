#include "Genome.hpp"

Genome::Genome()
{
}

Genome::Genome(const Genome &other)
{
  (void)other;
}

Genome::~Genome()
{
}

Genome &Genome::operator=(const Genome &other)
{
  (void)other;
  return (*this);
}
