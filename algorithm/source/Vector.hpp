#ifndef		VECTOR_HPP_
# define	VECTOR_HPP_

#include <utility>
#include <cmath>

class Vector
{

public:
  Vector(std::pair <float, float> firstCoordinate_, std::pair <float, float> secondCoordinate_);
  ~Vector();
  float getMagnitude();
  std::pair <float, float> getCoordinates() const;
  float getDiretionDiff(const Vector &v) const;

  const std::pair <float, float> firstCoordinate;
  const std::pair <float, float> secondCoordinate;
};

#endif		/* !VECTOR_HPP_ */
