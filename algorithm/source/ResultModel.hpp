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
  ResultModel();
  ResultModel(int iteration, int maxScore, double averageScore, int worstScore);
  ResultModel(int theoreticalMaxScore);
  ResultModel(const ResultModel &);
  ResultModel(const ResultModel *);
  ~ResultModel();
  ResultModel &operator=(const ResultModel &);
};

#endif		/* !RESULTMODEL_HPP_ */
