#ifndef		WRITABLERESULTMODEL_HPP_
# define	WRITABLERESULTMODEL_HPP_

# include "ResultModel.hpp"
# include <iostream>
# include <fstream>

class		WritableResultModel : public ResultModel
{

public:
  int getTheoreticalMaxScore() const;
  int getIteration() const;
  int getMaxScore() const;
  double getAverageScore() const;
  int getWorstScore() const;
  void setTheoreticalMaxScore(const int maxScore);
  ~WritableResultModel();
};

std::ofstream &operator<<(std::ofstream &stream, WritableResultModel *result);

#endif		/* !WRITABLERESULTMODEL_HPP_ */
