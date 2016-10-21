#include <iostream>
#include <iomanip>
#include <random>
#include <cmath>
#include <thread>
#include <chrono>
#include <cstring>

extern "C"
{
#include "vrep.h"
}

class Random
{
private:
  std::mt19937 _generator;

public:
  Random()
    : _generator(std::random_device()())
  {
  }

  template <typename int_t>
  inline int_t intInRange(int_t min, int_t max)
  {
    return (std::uniform_int_distribution<int_t>(min, max)(_generator));
  }

  template<typename real_t>
  inline real_t realInRange(real_t min, real_t max)
  {
    return (std::uniform_real_distribution<real_t>(min, max)(_generator));
  }
};

class Maths
{
public:
  static const float pi;

  class Degrees
  {
  public:

    template<typename number_t>
    static inline number_t toRadians(number_t degreeValue)
    {
      return degreeValue * pi / 180;
    }
  };

  class Radians
  {
  public:

    template<typename number_t>
    static inline number_t toDegrees(number_t radianValue)
    {
      return radianValue * 180 / pi;
    }
  };
};

const float Maths::pi = M_PI;

int main()
{
  Random random;
  simxInt clientId = -1;

  simxFinish(-1);
  clientId = simxStart((simxChar*)"127.0.0.1", 19997, true, true, 5000, 5);

  if (clientId != -1)
    {
      simxInt opMode = simx_opmode_oneshot_wait,
	wristHandle = 0, elbowHandle = 0, shoulderHandle = 0, robotHandle = 0;

      std::cout << "Connected to v-rep remote API server" << std::endl << std::endl;
      if (simxGetObjectHandle(clientId, "WristMotor", &wristHandle, opMode) == 0 &&
	  simxGetObjectHandle(clientId, "ElbowMotor", &elbowHandle, opMode) == 0 &&
	  simxGetObjectHandle(clientId, "ShoulderMotor", &shoulderHandle, opMode) == 0 &&
	  simxGetObjectHandle(clientId, "2W1A", &robotHandle, opMode) == 0)
      	{
	  simxFloat position[3], orientation[3];

	  std::cout << std::fixed << std::setprecision(8);
	  for (int i = 0; i != 3; ++i)
	    {
	      std::memset(position, 0, sizeof(position) / sizeof(simxFloat));
	      std::memset(orientation, 0, sizeof(orientation) / sizeof(simxFloat));

	      simxStartSimulation(clientId, opMode);
	      std::cout << "----- Simulation started -----" << std::endl;

	      simxGetObjectPosition(clientId, robotHandle, -1, position, simx_opmode_streaming);
	      std::cout << "2w1a position (x, y, z):\t"
			<< position[0] << ", " << position[1] << ", " << position[2] << std::endl;

	      simxGetObjectOrientation(clientId, robotHandle, -1, orientation, simx_opmode_streaming);
	      std::cout << "2w1a orientation (x, y, z):\t"
			<< orientation[0] << ", " << orientation[1] << ", "
			<< orientation[2] << std::endl << std::endl;

	      for (int j = 0; j != 5; ++j)
		{
		  simxFloat wristPos = 0, shoulderPos = 0, elbowPos = 0;

		  wristPos = random.realInRange<simxFloat>(0, 300);
		  elbowPos = random.realInRange<simxFloat>(0, 300);
		  shoulderPos = random.realInRange<simxFloat>(0, 300);

		  std::cout << "Motors target positions:\twrist: " << wristPos
			    << "°, elbow: " << elbowPos << "°, shoulder: " << shoulderPos
			    << "°" << std::endl;

		  wristPos = Maths::Degrees::toRadians(wristPos);
		  elbowPos = Maths::Degrees::toRadians(elbowPos);
		  shoulderPos = Maths::Degrees::toRadians(shoulderPos);

		  simxSetJointTargetPosition(clientId, wristHandle, wristPos, opMode);
		  simxSetJointTargetPosition(clientId, elbowHandle, elbowPos, opMode);
		  simxSetJointTargetPosition(clientId, shoulderHandle, shoulderPos, opMode);

		  std::this_thread::sleep_for(std::chrono::seconds(5));

		  simxGetJointPosition(clientId, wristHandle, &wristPos, opMode);
		  simxGetJointPosition(clientId, elbowHandle, &elbowPos, opMode);
		  simxGetJointPosition(clientId, shoulderHandle, &shoulderPos, opMode);

		  std::cout << "Motors reached positions:\twrist: "
			    << Maths::Radians::toDegrees(wristPos)<< "°, elbow: "
			    << Maths::Radians::toDegrees(elbowPos) << "°, shoulder: "
			    << Maths::Radians::toDegrees(shoulderPos) << "°" << std::endl << std::endl;

		  simxGetObjectPosition(clientId, robotHandle, -1, position, simx_opmode_streaming);
		  std::cout << "2w1a position (x, y, z):\t"
			    << position[0] << ", " << position[1] << ", " << position[2] << std::endl;

		  simxGetObjectOrientation(clientId, robotHandle, -1, orientation,
					   simx_opmode_streaming);
		  std::cout << "2w1a orientation (x, y, z):\t"
			    << orientation[0] << ", " << orientation[1] << ", "
			    << orientation[2] << std::endl << std::endl;
		}

	      std::cout << "----- Simulation ended -----" << std::endl << std::endl;
	      simxStopSimulation(clientId, opMode);
	      std::this_thread::sleep_for(std::chrono::seconds(1));
	    }
	}
      else
	std::cerr << "Error: cannot find 2w1a" << std::endl;
      simxFinish(clientId);
    }
  else
    std::cerr << "Error: cannot connect to v-rep remote API server" << std::endl;

  return 0;
}
