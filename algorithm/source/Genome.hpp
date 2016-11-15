#ifndef		GENOME_HPP_
# define	GENOME_HPP_

# include <list>
# include <vector>

# include "Individual.hpp"

class	       Individual::Genome
{
  struct gene_t {
    float wrist;
    float elbow;
    float shoulder;
  };
private:
  std::vector<gene_t> _genes;

public:
  Genome();
  Genome(const Genome&);
  ~Genome();
  Genome& operator=(const Genome&);
  gene_t& operator[](const int pos);
  gene_t& operator[](const unsigned int pos);
};

#endif		/* !GENOME_HPP_ */
