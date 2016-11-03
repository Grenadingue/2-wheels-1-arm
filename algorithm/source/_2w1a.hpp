#ifndef		_2W1A_HPP_
# define	_2W1A_HPP_

# include "Object.hpp"
# include "Articulation.hpp"

class		_2w1a : public Physics::Object
{
private:
  Articulation *_wrist;
  Articulation *_elbow;
  Articulation *_shoulder;

public:
  _2w1a(const Physics::Object &);
  virtual ~_2w1a();
};

#endif		/* !_2W1A_HPP_ */
