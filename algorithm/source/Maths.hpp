#ifndef		MATHS_HPP_
# define	MATHS_HPP_

# include "cmath"

class		Maths
{
public:
  template<typename number_t> class Degrees;
  template<typename number_t> class Radians;

  static const float pi;
};

# include "Degrees.hpp"
# include "Radians.hpp"

#endif		/* !MATHS_HPP_ */
