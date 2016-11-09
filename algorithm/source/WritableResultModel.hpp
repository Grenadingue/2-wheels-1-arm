#ifndef		WRITABLERESULTMODEL_HPP_
# define	WRITABLERESULTMODEL_HPP_

# include "ResultModel.hpp"
# include <iostream>
# include <fstream>

class		WritableResultModel : public ResultModel
{

public:
  WritableResultModel();
  ~WritableResultModel();
  std::ofstream &operator<<(std::ofstream &file);
};


#endif		/* !WRITABLERESULTMODEL_HPP_ */
