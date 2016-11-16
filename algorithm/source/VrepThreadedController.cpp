#include <iostream>
#include "VrepThreadedController.hpp"
#include "VrepSimulationFinished.hpp"
#include "Individual.hpp"

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
  const IEvent *event = NULL;

  while (!_close)
    {
      event = NULL;
      if ((event = _getNextResult()))
	{
	  std::cout << "[MATRIX] New simulation request received" << std::endl;

	  VrepSimulationEvent *simEvent = (VrepSimulationEvent *)event;

	  VrepSimulationFinished::eStatus status =  VrepSimulationFinished::SUCCESS;
	  if (!_simulate(simEvent))
	    status = VrepSimulationFinished::FAILURE;

	  VrepSimulationFinished *retEvent = new VrepSimulationFinished(simEvent->individual(), status);

	  _parentController->handleNewResult(retEvent);

	  std::cout << "[MATRIX] Simulation event processed" << std::endl;
	  delete event;
	}
      std::this_thread::sleep_for(std::chrono::milliseconds(300));
    }
  return true;
}

bool VrepThreadedController::_simulate(VrepSimulationEvent *event)
{
  Individual *individual = event->individual();

  std::cout << "[MATRIX] Starting simulation..." << std::endl;
  individual->useBody(_robot);
  if (_startSimulation())
    {
      std::cout << "[MATRIX] Simulation started" << std::endl;
      float wristPos = 250,
	elbowPos = 120,
	shoulderPos = 150;

      std::cout << "[MATRIX] Wrist motor target position:\t\t" << wristPos
		<< " degrees" << std::endl
		<< "[MATRIX] Elbow motor target position:\t\t" << elbowPos
		<< " degrees" << std::endl
		<< "[MATRIX] Shoulder motor target position:\t" << shoulderPos
		<< " degrees" << std::endl << std::endl;

      if (!individual->body()->wrist().setTargetPosition(wristPos) ||
	  !individual->body()->elbow().setTargetPosition(elbowPos) ||
	  !individual->body()->shoulder().setTargetPosition(shoulderPos))
	{
	  std::cout << "[MATRIX] Unable to set 2w1a articulations target postions" << std::endl;
	}
      for (int i = 0; i != event->simulationCycles; ++i)
	{
	  vrep::position_t pos;
	  vrep::orientation_t ori;

	  if (!individual->body()->getPositionOnMap(pos) || !individual->body()->getOrientationOnMap(ori))
	    {
	      std::cout << "[MATRIX] Unable to retrieve 2w1a coordinates on map" << std::endl;
	      break;
	    }
	  std::cout << "[MATRIX] Position:\tx: " << (pos.x >= 0 ? " " : "") << pos.x
		    << ", y: " << (pos.y >= 0 ? " " : "") << pos.y
		    << ", z: " << (pos.z >= 0 ? " " : "") << pos.z << std::endl
		    << "[MATRIX] Orientation:\tx: " << (ori.x >= 0 ? " " : "") << ori.x
		    << ", y: " << (ori.y >= 0 ? " " : "") << ori.y
		    << ", z: " << (ori.z >= 0 ? " " : "") << ori.z << std::endl << std::endl;

	  wristPos = _random.realInRange<float>(0, 300);
	  elbowPos = _random.realInRange<float>(0, 300);
	  shoulderPos = _random.realInRange<float>(0, 300);

	  std::cout << "[MATRIX] Wrist motor target position:\t\t" << wristPos
		    << " degrees" << std::endl
		    << "[MATRIX] Elbow motor target position:\t\t" << elbowPos
		    << " degrees" << std::endl
		    << "[MATRIX] Shoulder motor target position:\t" << shoulderPos
		    << " degrees" << std::endl << std::endl;

	  if (!individual->body()->wrist().setTargetPosition(wristPos) ||
	      !individual->body()->elbow().setTargetPosition(elbowPos) ||
	      !individual->body()->shoulder().setTargetPosition(shoulderPos))
	    {
	      std::cout << "[MATRIX] Unable to set 2w1a articulations target postions" << std::endl;
	      break;
	    }

	  individual->body()->waitWhileMoving(10);

	  if (!individual->body()->wrist().getPosition(wristPos) ||
	      !individual->body()->elbow().getPosition(elbowPos) ||
	      !individual->body()->shoulder().getPosition(shoulderPos))
	    {
	      std::cout << "[MATRIX] Unable to set 2w1a articulations target postions" << std::endl;
	      break;
	    }

	  std::cout << "[MATRIX] Wrist motor reached position:\t\t" << wristPos
		    << " degrees" << std::endl
		    << "[MATRIX] Elbow motor reached position:\t\t" << elbowPos
		    << " degrees" << std::endl
		    << "[MATRIX] Shoulder motor reached position:\t" << shoulderPos
		    << " degrees" << std::endl << std::endl;

	  if (!individual->body()->getPositionOnMap(pos) || !individual->body()->getOrientationOnMap(ori))
	    {
	      std::cout << "[MATRIX] Unable to retrieve 2w1a coordinates on map" << std::endl;
	      break;
	    }
	  std::cout << "[MATRIX] Position:\tx: " << (pos.x >= 0 ? " " : "") << pos.x
		    << ", y: " << (pos.y >= 0 ? " " : "") << pos.y
		    << ", z: " << (pos.z >= 0 ? " " : "") << pos.z << std::endl
		    << "[MATRIX] Orientation:\tx: " << (ori.x >= 0 ? " " : "") << ori.x
		    << ", y: " << (ori.y >= 0 ? " " : "") << ori.y
		    << ", z: " << (ori.z >= 0 ? " " : "") << ori.z << std::endl << std::endl;
	}
      if (!_stopSimulation())
	{
	  std::cout << "[MATRIX] Unable to stop simulation" << std::endl;
	  return false;
	}
      std::this_thread::sleep_for(std::chrono::seconds(1));
      std::cout << "[MATRIX] Simulation ended" << std::endl;
    }
  else
    std::cout << "[MATRIX] Unable to start simulation" << std::endl;
  individual->useBody(NULL);
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

int VrepThreadedController::nbProcessedEvents()
{
  int nb = 0;

  _mutex.lock();
  nb = _events.size();
  _mutex.unlock();
  return nb;
}
