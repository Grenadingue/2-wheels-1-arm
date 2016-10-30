#ifndef		RADIANS_HPP_
# define	RADIANS_HPP_

class Maths;

template<typename number_t>
class		Maths::Radians
{
public:
  static inline number_t toDegrees(number_t radianValue)
  {
    return radianValue * 180 / pi;
  }
};

#endif		/* !RADIANS_HPP_ */
