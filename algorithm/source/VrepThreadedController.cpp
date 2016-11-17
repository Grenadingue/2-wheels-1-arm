#include <iostream>
#include <list>
#include "VrepThreadedController.hpp"
#include "VrepSimulationFinished.hpp"
#include "Individual.hpp"
#include "Genome.hpp"
#include "Vector.hpp"

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
      std::cout << "[MATRIX " << _parameters->serverPort << "] We are in the matrix" << std::endl;
      if (_retrieve2w1a())
  	{
  	  std::cout << "[MATRIX " << _parameters->serverPort << "] 2w1a retrieved from port "
		    << std::endl;
	  if (!_handleIncommingEvents())
	    {
	      std::cout << "[MATRIX " << _parameters->serverPort
			<< "] Fatal remote api error on port " << std::endl;
	    }
  	}
      else
  	std::cout << "[MATRIX " << _parameters->serverPort
		  << "] Unable to retrieve 2w1a from port " << std::endl;
    }
  else
    {
      std::cout << "[MATRIX " << _parameters->serverPort
		<< "] Unable to enter the matrix from port " << std::endl;
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
	  std::cout << "[MATRIX " << _parameters->serverPort
		    << "] New simulation request received" << std::endl;

	  VrepSimulationEvent *simEvent = (VrepSimulationEvent *)event;

	  VrepSimulationFinished::eStatus status =  VrepSimulationFinished::SUCCESS;
	  if (!_simulate(simEvent))
	    status = VrepSimulationFinished::FAILURE;

	  VrepSimulationFinished *retEvent = new VrepSimulationFinished(simEvent->individual(), status);

	  _parentController->handleNewResult(retEvent);

	  std::cout << "[MATRIX " << _parameters->serverPort
		    << "] Simulation event processed" << std::endl;
	  delete event;
	}
      std::this_thread::sleep_for(std::chrono::milliseconds(300));
    }
  return true;
}

bool VrepThreadedController::_simulate(VrepSimulationEvent *event)
{
  Individual *individual = event->individual();

  std::cout << "[MATRIX " << _parameters->serverPort << "] Starting simulation..." << std::endl;
  individual->useBody(_robot);
  if (_startSimulation())
    {
      std::list<Vector> vectors;
      float wristPos = 250, elbowPos = 120, shoulderPos = 150;

      std::cout << "[MATRIX " << _parameters->serverPort << "] Simulation started" << std::endl;

      // forcing initial position
      if (!individual->body()->wrist().setTargetPosition(wristPos) ||
	  !individual->body()->elbow().setTargetPosition(elbowPos) ||
	  !individual->body()->shoulder().setTargetPosition(shoulderPos))
	{
	  std::cout << "[MATRIX " << _parameters->serverPort
		    << "] Unable to set 2w1a articulations target postions" << std::endl;
	}

      for (int i = 0; i != event->simulationCycles; ++i)
	{
	  vrep::position_t pos1, pos2;

	  // start cycle position
	  if (!individual->body()->getPositionOnMap(pos1))
	    {
	      std::cout << "[MATRIX " << _parameters->serverPort
			<< "] Unable to retrieve 2w1a coordinates on map" << std::endl;
	      break;
	    }
	  std::cout << "[MATRIX " << _parameters->serverPort << "] Position:\tx: "
		    << (pos1.x >= 0 ? " " : "") << pos1.x
		    << ", y: " << (pos1.y >= 0 ? " " : "") << pos1.y
		    << ", z: " << (pos1.z >= 0 ? " " : "") << pos1.z << std::endl << std::endl;

	  wristPos = individual->genome()[0].wrist;
	  elbowPos = individual->genome()[0].elbow;
	  shoulderPos = individual->genome()[0].shoulder;

	  // std::cout << "[MATRIX " << _parameters->serverPort << "] Wrist motor target position:\t\t"
	  // 	    << wristPos << " degrees" << std::endl
	  // 	    << "[MATRIX " << _parameters->serverPort << "] Elbow motor target position:\t\t"
	  // 	    << elbowPos << " degrees" << std::endl
	  // 	    << "[MATRIX " << _parameters->serverPort << "] Shoulder motor target position:\t"
	  // 	    << shoulderPos << " degrees" << std::endl << std::endl;

	  if (!individual->body()->wrist().setTargetPosition(wristPos) ||
	      !individual->body()->elbow().setTargetPosition(elbowPos) ||
	      !individual->body()->shoulder().setTargetPosition(shoulderPos))
	    {
	      std::cout << "[MATRIX " << _parameters->serverPort
			<< "] Unable to set 2w1a articulations target postions" << std::endl;
	      break;
	    }

	  individual->body()->waitWhileMoving(5); // timeout 5sec

	  // if (!individual->body()->wrist().getPosition(wristPos) ||
	  //     !individual->body()->elbow().getPosition(elbowPos) ||
	  //     !individual->body()->shoulder().getPosition(shoulderPos))
	  //   {
	  //     std::cout << "[MATRIX " << _parameters->serverPort
	  // 		<< "] Unable to set 2w1a articulations target postions" << std::endl;
	  //     break;
	  //   }

	  // std::cout << "[MATRIX " << _parameters->serverPort << "] Wrist motor reached position:\t\t"
	  // 	    << wristPos << " degrees" << std::endl
	  // 	    << "[MATRIX " << _parameters->serverPort << "] Elbow motor reached position:\t\t"
	  // 	    << elbowPos << " degrees" << std::endl
	  // 	    << "[MATRIX " << _parameters->serverPort << "] Shoulder motor reached position:\t"
	  // 	    << shoulderPos << " degrees" << std::endl << std::endl;

	  // half cycle vector
	  // if (!individual->body()->getPositionOnMap(pos2))
	  //   {
	  //     std::cout << "[MATRIX " << _parameters->serverPort
	  // 		<< "] Unable to retrieve 2w1a coordinates on map" << std::endl;
	  //     break;
	  //   }
	  // std::cout << "[MATRIX " << _parameters->serverPort << "] Position:\tx: "
	  // 	    << (pos2.x >= 0 ? " " : "") << pos2.x
	  // 	    << ", y: " << (pos2.y >= 0 ? " " : "") << pos2.y
	  // 	    << ", z: " << (pos2.z >= 0 ? " " : "") << pos2.z << std::endl << std::endl;

	  wristPos = individual->genome()[1].wrist;
	  elbowPos = individual->genome()[1].elbow;
	  shoulderPos = individual->genome()[1].shoulder;

	  if (!individual->body()->wrist().setTargetPosition(wristPos) ||
	      !individual->body()->elbow().setTargetPosition(elbowPos) ||
	      !individual->body()->shoulder().setTargetPosition(shoulderPos))
	    {
	      std::cout << "[MATRIX " << _parameters->serverPort
			<< "] Unable to set 2w1a articulations target postions" << std::endl;
	      break;
	    }

	  individual->body()->waitWhileMoving(5); // timeout 5sec

	  if (!individual->body()->wrist().getPosition(wristPos) ||
	      !individual->body()->elbow().getPosition(elbowPos) ||
	      !individual->body()->shoulder().getPosition(shoulderPos))
	    {
	      std::cout << "[MATRIX " << _parameters->serverPort
			<< "] Unable to set 2w1a articulations target postions" << std::endl;
	      break;
	    }

	  // end cycle position
	  if (!individual->body()->getPositionOnMap(pos2))
	    {
	      std::cout << "[MATRIX " << _parameters->serverPort
	  		<< "] Unable to retrieve 2w1a coordinates on map" << std::endl;
	      break;
	    }
	  std::cout << "[MATRIX " << _parameters->serverPort << "] Position:\tx: "
	  	    << (pos2.x >= 0 ? " " : "") << pos2.x
	  	    << ", y: " << (pos2.y >= 0 ? " " : "") << pos2.y
	  	    << ", z: " << (pos2.z >= 0 ? " " : "") << pos2.z << std::endl << std::endl;

	  float x1 = pos1.x, x2 = pos2.x, y1 = pos1.y, y2 = pos2.y;
	  std::pair<float, float> pos1_ = std::make_pair(x1, y1), pos2_ = std::make_pair(x2, y2);
	  Vector cycleVector(pos1_, pos2_);
	  vectors.push_back(cycleVector);
	}
      if (!_stopSimulation())
	{
	  std::cout << "[MATRIX " << _parameters->serverPort << "] Unable to stop simulation"
		    << std::endl;
	  return false;
	}
      std::this_thread::sleep_for(std::chrono::seconds(1));
      std::cout << "[MATRIX " << _parameters->serverPort << "] Simulation ended" << std::endl;

      Vector initialVector(vectors.front());
      Vector totalVector(initialVector.firstCoordinate, vectors.back().secondCoordinate);
      float directionDiff = initialVector.getDiretionDiff(totalVector);
      bool hasMoved = initialVector.getMagnitude() > 1 && totalVector.getMagnitude() > vectors.size();

      float directionPercentage = 100.0 - ((directionDiff / 180.0) * 100);
      float score = hasMoved ? 50.0 : 0.0;
      score += directionPercentage;
      individual->fitness().setScore((int)score);
    }
  else
    std::cout << "[MATRIX " << _parameters->serverPort << "] Unable to start simulation" << std::endl;
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
