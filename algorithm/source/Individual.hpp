#ifndef		INDIVIDUAL_HPP_
# define	INDIVIDUAL_HPP_

# include "_2w1a.hpp"
# include "Fitness.hpp"

class		Individual
{
public:
  class Genome;

private:
  Fitness *_fitness;
  Genome *_genome;
  _2w1a *_body;

public:
  Individual();
  virtual ~Individual();

  Fitness& fitness();
  void useBody(_2w1a *);
  _2w1a *body();
  Genome &genome();
};

#endif		/* !INDIVIDUAL_HPP_ */
