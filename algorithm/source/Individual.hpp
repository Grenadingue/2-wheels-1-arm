#ifndef		INDIVIDUAL_HPP_
# define	INDIVIDUAL_HPP_

# include "_2w1a.hpp"

class		Individual
{
public:
  template<typename gene_t> class Genome;
  typedef Genome<int> genome_t;

private:
  genome_t *_genome;
  _2w1a *_body;

public:
  Individual();
  virtual ~Individual();

  void useBody(_2w1a *);
  _2w1a *body();
};

#endif		/* !INDIVIDUAL_HPP_ */
