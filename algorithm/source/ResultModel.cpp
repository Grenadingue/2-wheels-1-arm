#include "ResultModel.hpp"

ResultModel::ResultModel(int iteration, int maxScore, double averageScore,
			 int worstScore)
{
  _iteration = iteration;
  _maxScore = maxScore;
  _averageScore = averageScore;
  _worstScore = worstScore;
  _theoreticalMaxScore = -1;
}

ResultModel::ResultModel(int theoreticalMaxScore)
{
  _theoreticalMaxScore = theoreticalMaxScore;
}

ResultModel::ResultModel(const ResultModel &other)
{
  _iteration = other._iteration;
  _theoreticalMaxScore = other._theoreticalMaxScore;
  _maxScore = other._maxScore;
  _worstScore = other._worstScore;
  _averageScore = other._averageScore;
}

ResultModel::ResultModel(const ResultModel *other)
{
  _iteration = other->_iteration;
  _theoreticalMaxScore = other->_theoreticalMaxScore;
  _maxScore = other->_maxScore;
  _worstScore = other->_worstScore;
  _averageScore = other->_averageScore;
}

ResultModel::~ResultModel()
{
}

ResultModel &ResultModel::operator=(const ResultModel &other)
{ 
  _iteration = other._iteration;
  _theoreticalMaxScore = other._theoreticalMaxScore;
  _maxScore = other._maxScore;
  _worstScore = other._worstScore;
  _averageScore = other._averageScore;
  return (*this);
}
