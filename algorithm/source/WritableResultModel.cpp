#include "WritableResultModel.hpp"

WritableResultModel::~WritableResultModel()
{
}

int WritableResultModel::getTheoreticalMaxScore() const
{
  return this->_theoreticalMaxScore;
}

int WritableResultModel::getMaxScore() const
{
  return this->_maxScore;
}

double WritableResultModel::getAverageScore() const
{
  return this->_averageScore;
}

int WritableResultModel::getWorstScore() const
{
  return this->_worstScore;
}

int WritableResultModel::getIteration() const
{
  return this->_iteration;
}

void WritableResultModel::setTheoreticalMaxScore(const int maxScore)
{
  this->_theoreticalMaxScore = maxScore;
}

std::ofstream &operator<<(std::ofstream &file, WritableResultModel &result)
{
  if (file.is_open() == false)
    {
      std::cout << "!!! LOG FILE NOT OPENED. LOG WONT BE WRITTEN !!!" << std::endl;
      //      file = std::cout;
      return file;
    }
  if (result.getTheoreticalMaxScore() != -1 && result.getTheoreticalMaxScore() != -2)
    {
      file << "{ \"theoreticalMaxScore\": " << result.getTheoreticalMaxScore() <<
	", \"results\": [";
      return file;
    }
  file << "{ "
       << "\"iteration\": " << result.getIteration() << ","
       << "\"maxScore\": " << result.getMaxScore() << ","
       << "\"averageScore\": " << result.getAverageScore() << ","
       << "\"worstScore\": " << result.getWorstScore();
  if (result.getTheoreticalMaxScore() == -2)
    file << "}]}";
  else
    file << "},";
  return file;
}
