#ifndef		VREPAPI_HPP_
# define	VREPAPI_HPP_

extern "C"
{
# include "extApi.h"
}

# include <string>
# include "struct_packed.h"

namespace vrep
{
  STRUCT_PACKED(coordinates_t,
    float x;
    float y;
    float z;
  );

  union coordinates_u
  {
    coordinates_t s;
    float t[3];
  };

  typedef coordinates_t position_t;
  typedef coordinates_t orientation_t;

  typedef simxInt handle_t;

  enum eOpMode : simxInt
    {
      ONESHOT = simx_opmode_oneshot,
      ONESHOT_WAIT = simx_opmode_oneshot_wait, // same as blocking
      BLOCKING = simx_opmode_blocking,
      DISCONTINUE = simx_opmode_discontinue,
      BUFFER = simx_opmode_buffer,
      REMOVE = simx_opmode_remove
    };

  enum eReturn : handle_t
    {
      OK = simx_return_ok,
      NO_VALUE = simx_return_novalue_flag,
      TIMEOUT = simx_return_timeout_flag,
      ILLEGAL_OPMODE = simx_return_illegal_opmode_flag,
      REMOTE_ERROR = simx_return_remote_error_flag,
      SPLIT_PROGRESS = simx_return_split_progress_flag,
      LOCAL_ERROR = simx_return_local_error_flag,
      INITIALIZE = simx_return_initialize_error_flag
    };

  handle_t start(const std::string &addr, uint16_t port);
  handle_t startSimulation(handle_t clientId);

  handle_t getObjectHandle(handle_t clientId, const std::string &objectName, handle_t objectHandle);
  handle_t getObjectPosition(handle_t clientId, handle_t objectId, position_t &position);
  handle_t getObjectOrientation(handle_t clientId, handle_t objectId, orientation_t &orientation);

  handle_t getJointPosition(handle_t clientId, handle_t jointId, float &position);
  handle_t setJointTargetPosition(handle_t clientId, handle_t jointId, float position);
};

#endif		/* !VREPAPI_HPP_ */
