#include "Vector.hpp"
#include "Maths.hpp"

Vector::Vector(std::pair <float, float> firstCoordinate_, std::pair <float, float> secondCoordinate_)
: firstCoordinate(firstCoordinate_), secondCoordinate(secondCoordinate_)
{
}

Vector::~Vector()
{
}

float Vector::getMagnitude()
{
  static const float powCarreX = pow((this->secondCoordinate.first - this->firstCoordinate.first), 2);
  static const float powCarreY = pow((this->secondCoordinate.second - this->firstCoordinate.second), 2);

  static const float magnitude = sqrt(powCarreX + powCarreY);

  return(magnitude);
}

std::pair <float, float> Vector::getCoordinates() const
{
  float xVector = this->secondCoordinate.first - this->firstCoordinate.first;
  float yVector = this->secondCoordinate.second - this->firstCoordinate.second;

  std::pair <float, float> vectorCoordinates (xVector, yVector);

  return(vectorCoordinates);
}

float Vector::getDiretionDiff(const Vector &v) const
{
  const std::pair <float, float> firstVector = this->getCoordinates();
  const std::pair <float, float> secondVector = v.getCoordinates();

  float Na = sqrt(pow(firstVector.first, 2) + pow(firstVector.second, 2));
  float Nb = sqrt(pow(secondVector.first, 2) + pow(secondVector.second, 2));
  float N = Na * Nb;

  float DirectionDiff;

  if (N == 0) {
    DirectionDiff = 0;
  } else {
    float C = (firstVector.first * secondVector.first + firstVector.second * secondVector.second) / (Na * Nb);
    DirectionDiff = Maths::Radians<float>::toDegrees(acos(C));
  }

  return(DirectionDiff);
}
