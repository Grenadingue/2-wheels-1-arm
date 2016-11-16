#ifndef		VECTOR_HPP_
# define	VECTOR_HPP_

#include <utility>

class Vector
{

public:
  Vector(std::pair <float, float> firstCoordinate_, std::pair <float, float> secondCoordinate_);
  ~Vector();
  float getMagnitude();
  float getCoordinates();
  float getDiretionDiff(const Vector v);

  const std::pair <float, float> firstCoordinate;
  const std::pair <float, float> secondCoordinate;
};

#endif		/* !VECTOR_HPP_ */
