#ifndef FITNESS_HPP_
# define FITNESS_HPP_

class Fitness
{
protected:
  int _score;

public:
  int score() const;
  void setScore(int score);
  Fitness();
  ~Fitness();

};

#endif // !FITNESS_HPP_
