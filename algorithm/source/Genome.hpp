#ifndef		GENOME_HPP_
# define	GENOME_HPP_

# include <list>

# include "Individual.hpp"

template<typename gene_t>
class		Individual::Genome
{
public:
  typedef std::list<gene_t> genes_t;

private:
  genes_t _genes;

public:
  Genome();
  Genome(const Genome&);
  ~Genome();
  Genome& operator=(const Genome&);
};

#endif		/* !GENOME_HPP_ */
