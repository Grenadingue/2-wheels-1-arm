#ifndef		ARTICULATION_HPP_
# define	ARTICULATION_HPP_

# include "Object.hpp"

class		Physics::Articulation : Physics::Object
{
public:
  virtual ~Articulation();

  // position in degrees
  bool getPosition(float &);
  bool setTargetPosition(float);
};

#endif		/* !ARTICULATION_HPP_ */
