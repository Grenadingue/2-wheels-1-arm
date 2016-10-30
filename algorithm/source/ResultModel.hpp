#ifndef		RESULTMODEL_HPP_
# define	RESULTMODEL_HPP_

class		ResultModel
{

public:
  ResultModel();
  ResultModel(const ResultModel &);
  ResultModel(const ResultModel *);
  ~ResultModel();
  ResultModel &operator=(const ResultModel &);
};

#endif		/* !RESULTMODEL_HPP_ */
