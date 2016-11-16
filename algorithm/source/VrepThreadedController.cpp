#include <iostream>
#include "VrepThreadedController.hpp"

VrepThreadedController::VrepThreadedController(const IParameters *parameters,
					       AThreadedDataHandler *parentController)
  : AThreadedDataHandler(parameters),
    _parameters(static_cast<const VrepParameters *>(parameters)),
    _parentController(parentController),
    _robot(NULL)
{
}

VrepThreadedController::~VrepThreadedController()
{
}

void VrepThreadedController::_workLoop()
{
  if (_enterVirtualWorld())
    {
      std::cout << "[MATRIX] We are in the matrix from port "
		<< _parameters->serverPort << std::endl;
      if (_retrieve2w1a())
  	{
  	  std::cout << "[MATRIX] 2w1a retrieved from port "
		    << _parameters->serverPort << std::endl;
	  if (!_handleIncommingEvents())
	    {
	      std::cout << "[MATRIX] Fatal remote api error on port "
			<< _parameters->serverPort << std::endl;
	    }
  	}
      else
  	std::cout << "[MATRIX] Unable to retrieve 2w1a from port "
		  << _parameters->serverPort << std::endl;
    }
  else
    {
      std::cout << "[MATRIX] Unable to enter the matrix from port "
		<< _parameters->serverPort << std::endl;
      return;
    }
  _leaveVirtualWorld();
}

bool VrepThreadedController::_handleIncommingEvents()
{
  const ResultModel *result = NULL;

  while (!_close)
    {
      result = NULL;
      if ((result = _getNextResult()))
	{
	  _simulate();
	  delete result;
	}
      std::this_thread::sleep_for(std::chrono::milliseconds(300));
    }
  return true;
}

bool VrepThreadedController::_simulate()
{
  // if (_startSimulation())
  // 	{
  // 	  std::cout << "[MATRIX] Simulation started" << std::endl;
  // 	  for (int i = 0; i != 1; ++i)
  // 	    {
  // 	      vrep::position_t pos;
  // 	      vrep::orientation_t ori;

  // 	      if (!individual->getPositionOnMap(pos) || !individual->getOrientationOnMap(ori))
  // 		{
  // 		  std::cout << "[MATRIX] Unable to retrieve 2w1a coordinates on map" << std::endl;
  // 		  break;
  // 		}
  // 	      std::cout << "[MATRIX] Position:\tx: " << (pos.x >= 0 ? " " : "") << pos.x
  // 			<< ", y: " << (pos.y >= 0 ? " " : "") << pos.y
  // 			<< ", z: " << (pos.z >= 0 ? " " : "") << pos.z << std::endl
  // 			<< "[MATRIX] Orientation:\tx: " << (ori.x >= 0 ? " " : "") << ori.x
  // 			<< ", y: " << (ori.y >= 0 ? " " : "") << ori.y
  // 			<< ", z: " << (ori.z >= 0 ? " " : "") << ori.z << std::endl << std::endl;

  // 	      float wristPos = _random.realInRange<float>(0, 300),
  // 		elbowPos = _random.realInRange<float>(0, 300),
  // 		shoulderPos = _random.realInRange<float>(0, 300);

  // 	      std::cout << "[MATRIX] Wrist motor target position:\t\t" << wristPos
  // 			<< " degrees" << std::endl
  // 			<< "[MATRIX] Elbow motor target position:\t\t" << elbowPos
  // 			<< " degrees" << std::endl
  // 			<< "[MATRIX] Shoulder motor target position:\t" << shoulderPos
  // 			<< " degrees" << std::endl << std::endl;

  // 	      if (!individual->wrist().setTargetPosition(wristPos) ||
  // 		  !individual->elbow().setTargetPosition(elbowPos) ||
  // 		  !individual->shoulder().setTargetPosition(shoulderPos))
  // 		{
  // 		  std::cout << "[MATRIX] Unable to set 2w1a articulations target postions" << std::endl;
  // 		  break;
  // 		}

  // 	      std::this_thread::sleep_for(std::chrono::seconds(3));

  // 	      if (!individual->wrist().getPosition(wristPos) ||
  // 		  !individual->elbow().getPosition(elbowPos) ||
  // 		  !individual->shoulder().getPosition(shoulderPos))
  // 		{
  // 		  std::cout << "[MATRIX] Unable to set 2w1a articulations target postions" << std::endl;
  // 		  break;
  // 		}

  // 	      std::cout << "[MATRIX] Wrist motor reached position:\t\t" << wristPos
  // 			<< " degrees" << std::endl
  // 			<< "[MATRIX] Elbow motor reached position:\t\t" << elbowPos
  // 			<< " degrees" << std::endl
  // 			<< "[MATRIX] Shoulder motor reached position:\t" << shoulderPos
  // 			<< " degrees" << std::endl << std::endl;

  // 	      if (!individual->getPositionOnMap(pos) || !individual->getOrientationOnMap(ori))
  // 		{
  // 		  std::cout << "[MATRIX] Unable to retrieve 2w1a coordinates on map" << std::endl;
  // 		  break;
  // 		}
  // 	      std::cout << "[MATRIX] Position:\tx: " << (pos.x >= 0 ? " " : "") << pos.x
  // 			<< ", y: " << (pos.y >= 0 ? " " : "") << pos.y
  // 			<< ", z: " << (pos.z >= 0 ? " " : "") << pos.z << std::endl
  // 			<< "[MATRIX] Orientation:\tx: " << (ori.x >= 0 ? " " : "") << ori.x
  // 			<< ", y: " << (ori.y >= 0 ? " " : "") << ori.y
  // 			<< ", z: " << (ori.z >= 0 ? " " : "") << ori.z << std::endl << std::endl;
  // 	    }
  // 	  if (!_stopSimulation())
  // 	    {
  // 	      std::cout << "[MATRIX] Unable to stop simulation" << std::endl;
  // 	      return false;
  // 	    }
  // 	  std::this_thread::sleep_for(std::chrono::seconds(1));
  // 	  std::cout << "[MATRIX] Simulation ended" << std::endl;
  // 	}
  return true;
}

bool VrepThreadedController::_enterVirtualWorld()
{
  return _physics.enterTheMatrix(_parameters->serverPort) && ((_robot = _retrieve2w1a()) != NULL);
}

void VrepThreadedController::_leaveVirtualWorld()
{
  _physics.getOffTheMatrix();
}

bool VrepThreadedController::_startSimulation()
{
  return _physics.startSimulation();
}

bool VrepThreadedController::_stopSimulation()
{
  return _physics.endSimulation();
}

_2w1a *VrepThreadedController::_retrieve2w1a()
{
  if (!_robot)
    {
      Physics::Object *robot = NULL,
	*wrist = NULL, *elbow = NULL, *shoulder = NULL;

      robot = _physics.getObject("2W1A");
      wrist = _physics.getObject("WristMotor");
      elbow = _physics.getObject("ElbowMotor");
      shoulder = _physics.getObject("ShoulderMotor");

      if (!robot || !wrist || !elbow || !shoulder)
	return NULL;

      _robot = new _2w1a(*robot, *wrist, *elbow, *shoulder);
    }
  return _robot;
}
