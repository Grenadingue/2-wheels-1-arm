#include "WritableResultModel.hpp"

WritableResultModel::WritableResultModel()
{
}

WritableResultModel::~WritableResultModel()
{
}

std::ofstream &WritableResultModel::operator<<(std::ofstream &file,
					       const WritableResultModel &result)
{
  if (file.is_open == false)
    {
      std::cout << "!!! LOG FILE NOT OPENED. LOG WONT BE WRITTEN !!!" << std::endl;
      //      file = std::cout;
      return file;
    }
  if (result._theoreticalMaxScore == -1)
    {
      file << "{ \"theoreticalMaxScore\": " << result._theoreticalMaxScore <<
	", \"results\": [";
    }
  file << "{ "
       << "\"iteration\": " << result._iteration << ","
       << "\"maxScore\": " << result._maxScore << ","
       << "\"averageScore\": " << result._averageScore << ","
       << "\"worstScore\": " << result._worstScore;
 if (result._theoreticalMaxScore == -2)
   file << "}]}";
 else
   file << "},";
 return file;
}
