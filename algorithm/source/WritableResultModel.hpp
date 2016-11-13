#ifndef		WRITABLERESULTMODEL_HPP_
# define	WRITABLERESULTMODEL_HPP_

# include "ResultModel.hpp"
# include <iostream>
# include <fstream>

class		WritableResultModel : public ResultModel
{
public:
  ~WritableResultModel();
};

std::ofstream &operator<<(std::ofstream &stream, const WritableResultModel &result);

#endif		/* !WRITABLERESULTMODEL_HPP_ */
