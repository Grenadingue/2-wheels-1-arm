#ifndef		DEGREES_HPP_
# define	DEGREES_HPP_

class Maths;

template<typename number_t>
class		Maths::Degrees
{
public:
  static inline number_t toRadians(number_t degreeValue)
  {
    return degreeValue * pi / 180;
  }
};

#endif		/* !DEGREES_HPP_ */
