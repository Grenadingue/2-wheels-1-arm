#ifndef		VREPTHREADEDCONTROLLER_HPP_
# define	VREPTHREADEDCONTROLLER_HPP_

# include "AThreadedDataHandler.hpp"
# include "VrepParameters.hpp"
# include "Physics.hpp"
# include "_2w1a.hpp"
# include "VrepSimulationEvent.hpp"
# include "MotherNature.hpp"

class		VrepThreadedController : public AThreadedDataHandler
{
private:
  const VrepParameters *_parameters;
  AThreadedDataHandler *_parentController;
  _2w1a *_robot;
  Physics _physics;
  MotherNature _random;

public:
  VrepThreadedController(const IParameters *, AThreadedDataHandler *);
  ~VrepThreadedController();

  // Inherited from AThreadedDataHandler
  virtual void _workLoop();

private:
  bool _handleIncommingEvents();
  bool _simulate(VrepSimulationEvent *);

  // vrep
  bool _enterVirtualWorld();
  void _leaveVirtualWorld();
  bool _startSimulation();
  bool _stopSimulation();
  _2w1a *_retrieve2w1a();

public:
  int nbProcessedEvents();
};

#endif		/* !VREPTHREADEDCONTROLLER_HPP_ */
