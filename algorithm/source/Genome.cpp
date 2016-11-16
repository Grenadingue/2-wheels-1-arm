#include "Genome.hpp"

Individual::Genome::Genome()
{
  Individual::Genome::gene_t gene;
  
  _genes.push_back(gene);
  _genes.push_back(gene);
}

Individual::Genome::Genome(const Genome &other)
{
  (void)other;
}

Individual::Genome::~Genome()
{
}

Individual::Genome::gene_t& Individual::Genome::at(int pos)
{
  return _genes[pos];
}

Individual::Genome::gene_t& Individual::Genome::operator[](int pos)
{
  return _genes[pos];
}

Individual::Genome::gene_t& Individual::Genome::operator[](unsigned int pos)
{
  return _genes[pos];
}

Individual::Genome& Individual::Genome::operator=(const Genome &other)
{
  (void)other;
  return (*this);
}
