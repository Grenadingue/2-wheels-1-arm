#ifndef		OBJECT_HPP_
# define	OBJECT_HPP_

class		Object
{

public:
  Object();
  Object(const Object&);
  ~Object();
  Object &operator=(const Object&);
};

#endif		/* !OBJECT_HPP_ */
