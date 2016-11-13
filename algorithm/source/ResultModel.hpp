#ifndef		RESULTMODEL_HPP_
# define	RESULTMODEL_HPP_

class		ResultModel
{
protected:
  int _iteration;
  int _theoreticalMaxScore;
  int _maxScore;
  int _worstScore;
  double _averageScore;

public:
  ResultModel(int iteration, int maxScore, double averageScore, int worstScore);
  ResultModel(int theoreticalMaxScore);
  ResultModel(const ResultModel &);
  ResultModel(const ResultModel *);
  ~ResultModel();
  ResultModel &operator=(const ResultModel &);

  int getTheoreticalMaxScore() const;
  int getIteration() const;
  int getMaxScore() const;
  double getAverageScore() const;
  int getWorstScore() const;

  void setTheoreticalMaxScore(const int maxScore);
};

#endif		/* !RESULTMODEL_HPP_ */
