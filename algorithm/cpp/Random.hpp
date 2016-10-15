#ifndef		RANDOM_HPP_
# define	RANDOM_HPP_

# include <random>

class		Random
{
private:
  std::mt19937_64 _generator;

public:
  Random();
  ~Random();

  template <typename int_t>
  inline int_t intInRange(int_t min, int_t max)
  {
    return std::uniform_int_distribution<int_t>(min, max)(_generator);
  }

  template<typename real_t>
  inline real_t realInRange(real_t min, real_t max)
  {
    return std::uniform_real_distribution<real_t>(min, max)(_generator);
  }
};

#endif		/* !RANDOM_HPP_ */
