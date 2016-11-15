#ifndef		VECTOR_HPP_
# define	VECTOR_HPP_

#include <utility>

class Vector
{

public:
  Vector(std::pair <float, float> first_coordinate_, std::pair <float, float> second_coordinate_);
  ~Vector();
  float getLength();
  float getCoordinates();
  float getAngle(Vector);

  const std::pair <float, float> first_coordinate;
  const std::pair <float, float> second_coordinate;
};

#endif		/* !VECTOR_HPP_ */
