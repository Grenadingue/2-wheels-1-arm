#ifndef		INDIVIDUAL_HPP_
# define	INDIVIDUAL_HPP_

# include "_2w1a.hpp"
# include "Fitness.hpp"

class		Individual : public _2w1a
{
public:
  class Genome;

private:
  Fitness* _fitness;
  Genome* _genome;

public:
  Fitness& fitness();
  Individual(const _2w1a &);
  virtual ~Individual();
};

#endif		/* !INDIVIDUAL_HPP_ */
