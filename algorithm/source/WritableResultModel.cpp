#include "WritableResultModel.hpp"

WritableResultModel::WritableResultModel()
{
}

WritableResultModel::~WritableResultModel()
{
}

std::ofstream &WritableResultModel::operator<<(std::ofstream &file)
{
  if (file.is_open() == false)
    {
      std::cout << "!!! LOG FILE NOT OPENED. LOG WONT BE WRITTEN !!!" << std::endl;
      //      file = std::cout;
      return file;
    }
  if (this->_theoreticalMaxScore == -1)
    {
      file << "{ \"theoreticalMaxScore\": " << this->_theoreticalMaxScore <<
	", \"results\": [";
    }
  file << "{ "
       << "\"iteration\": " << this->_iteration << ","
       << "\"maxScore\": " << this->_maxScore << ","
       << "\"averageScore\": " << this->_averageScore << ","
       << "\"worstScore\": " << this->_worstScore;
 if (this->_theoreticalMaxScore == -2)
   file << "}]}";
 else
   file << "},";
 return file;
}
