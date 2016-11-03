#include "VrepAPI.hpp"

namespace vrep
{
  bool start(const std::string &addr, uint16_t port, handle_t &clientId)
  {
    clientId = simxStart(addr.c_str(), port, true, true, 5000, 5);
    return clientId != eHandle::INVALID;
  }

  void finish(handle_t clientId)
  {
    simxFinish(clientId);
  }

  handle_t startSimulation(handle_t clientId)
  {
    return simxStartSimulation(clientId, eOpMode::BLOCKING);
  }

  handle_t stopSimulation(handle_t clientId)
  {
    return simxStopSimulation(clientId, eOpMode::BLOCKING);
  }

  handle_t getObjectHandle(handle_t clientId, const std::string &objectName, handle_t &objectHandle)
  {
    return simxGetObjectHandle(clientId, objectName.c_str(), &objectHandle, eOpMode::BLOCKING);
  }

  handle_t getObjectPosition(handle_t clientId, handle_t objectId, position_t &position)
  {
    handle_t ret = eReturn::LOCAL_ERROR;
    coordinates_u coordinates;

    ret = simxGetObjectPosition(clientId, objectId, -1, coordinates.t, eOpMode::BLOCKING);
    position = coordinates.s;
    return ret;
  }

  handle_t getObjectOrientation(handle_t clientId, handle_t objectId, orientation_t &orientation)
  {
    handle_t ret = eReturn::LOCAL_ERROR;
    coordinates_u coordinates;

    ret = simxGetObjectOrientation(clientId, objectId, -1, coordinates.t, eOpMode::BLOCKING);
    orientation = coordinates.s;
    return ret;
  }

  handle_t getJointPosition(handle_t clientId, handle_t jointId, float &position)
  {
    return simxGetJointPosition(clientId, jointId, &position, eOpMode::BLOCKING);
  }

  handle_t setJointTargetPosition(handle_t clientId, handle_t jointId, float position)
  {
    return simxSetJointTargetPosition(clientId, jointId, position, eOpMode::BLOCKING);
  }
};
