#include "Genome.hpp"

Individual::Genome::Genome()
{
}

Individual::Genome::Genome(const Genome &other)
{
  (void)other;
}

Individual::Genome::~Genome()
{
}

Individual::Genome::gene_t& Individual::Genome::operator[](const int pos)
{
  return _genes[pos];
}

Individual::Genome::gene_t& Individual::Genome::operator[](const unsigned int pos)
{
  return _genes[pos];
}

Individual::Genome& Individual::Genome::operator=(const Genome &other)
{
  (void)other;
  return (*this);
}
