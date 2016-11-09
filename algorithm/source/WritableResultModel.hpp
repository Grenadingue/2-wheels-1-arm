#ifndef		WRITABLERESULTMODEL_HPP_
# define	WRITABLERESULTMODEL_HPP_

# include "ResultModel.hpp"

class		WritableResultModel : public ResultModel
{

public:
  WritableResultModel();
  ~WritableResultModel();
  std::ofstream &WritableResultModel::operator<<(std::ofstream &file,
						 const WritableResultModel &result);
};


#endif		/* !WRITABLERESULTMODEL_HPP_ */
