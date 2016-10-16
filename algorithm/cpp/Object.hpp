#ifndef		OBJECT_HPP_
# define	OBJECT_HPP_

# include "Physics.hpp"

class		Physics::Object
{
public:
  Object();
  Object(const Object&);
  ~Object();

  Object &operator=(const Object&);
};

#endif		/* !OBJECT_HPP_ */
