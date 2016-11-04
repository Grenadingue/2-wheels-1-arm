#ifndef		INDIVIDUAL_HPP_
# define	INDIVIDUAL_HPP_

# include "_2w1a.hpp"

class		Individual : public _2w1a
{
public:
  template<typename gene_t> class Genome;
  typedef Genome<int> genome_t;

private:
  genome_t *_genome;

public:
  Individual(const _2w1a &);
  virtual ~Individual();
};

#endif		/* !INDIVIDUAL_HPP_ */
