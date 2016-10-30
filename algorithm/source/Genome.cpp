#include "Genome.hpp"

template<typename gene_t>
Individual::Genome<gene_t>::Genome()
{
}

template<typename gene_t>
Individual::Genome<gene_t>::Genome(const Genome &other)
{
  (void)other;
}

template<typename gene_t>
Individual::Genome<gene_t>::~Genome()
{
}

template<typename gene_t>
Individual::Genome<gene_t> &Individual::Genome<gene_t>::operator=(const Genome &other)
{
  (void)other;
  return (*this);
}
