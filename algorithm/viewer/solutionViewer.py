# File created by Thibaut Royer, Epitech school
# thibaut1.royer@epitech.eu
# It intends to be an example program for the "Two wheels, one arm" educative project.

import vrep
import math
import random
import time
import sys

print ('Start')

# Close eventual old connections
vrep.simxFinish(-1)
portNumber = sys.argv[1];
print "Port is " + portNumber
# Connect to V-REP remote server
clientID = vrep.simxStart('127.0.0.1', int(portNumber), True, True, 5000, 5)

if clientID != -1:
    print ('Connected to remote API server')

    # Communication operating mode with the remote API : wait for its answer before continuing (blocking mode)
    # http://www.coppeliarobotics.com/helpFiles/en/remoteApiConstants.htm
    opmode = vrep.simx_opmode_oneshot_wait

    # Try to retrieve motors and robot handlers
    # http://www.coppeliarobotics.com/helpFiles/en/remoteApiFunctionsPython.htm#simxGetObjectHandle
    ret1, wristHandle = vrep.simxGetObjectHandle(clientID, "WristMotor", opmode)
    ret2, elbowHandle = vrep.simxGetObjectHandle(clientID, "ElbowMotor", opmode)
    ret3, shoulderHandle = vrep.simxGetObjectHandle(clientID, "ShoulderMotor", opmode)
    ret4, robotHandle = vrep.simxGetObjectHandle(clientID, "2W1A", opmode)

    # If handlers are OK, execute two simulations
    if ret1 == 0 and ret2 == 0 and ret3 == 0:
        for i in range(0, 2):
            # Start the simulation
            # http://www.coppeliarobotics.com/helpFiles/en/remoteApiFunctionsPython.htm#simxStartSimulation
            vrep.simxStartSimulation(clientID, opmode)
            print ("----- Simulation started -----")

            # Start getting the robot position
            # Unlike other commands, we will use a streaming operating mode
            # http://www.coppeliarobotics.com/helpFiles/en/remoteApiFunctionsPython.htm#simxGetObjectPosition
            pret, robotPos = vrep.simxGetObjectPosition(clientID, robotHandle, -1, vrep.simx_opmode_streaming)
            print "2w1a position: (x = " + str(robotPos[0]) +\
                  ", y = " + str(robotPos[1]) + ")"

            # Start getting the robot orientation
            # Unlike other commands, we will use a streaming operating mode
            # http://www.coppeliarobotics.com/helpFiles/en/remoteApiFunctionsPython.htm#simxGetObjectOrientation
            oret, robotOrient = vrep.simxGetObjectOrientation(clientID, robotHandle, -1, vrep.simx_opmode_streaming)
            print "2w1a orientation: (x = " + str(robotOrient[0]) + \
                  ", y = " + str(robotOrient[1]) +\
                  ", z = " + str(robotOrient[2]) + ")"

            # Make the robot move
            for j in range(0, 2):
                # Generating random positions for the motors
                if j == 1:
                    awrist = float(sys.argv[2])
                    aelbow = float(sys.argv[3])
                    ashoulder = float(sys.argv[4])
                else:
                    awrist = float(sys.argv[5])
                    aelbow = float(sys.argv[6])
                    ashoulder =  float(sys.argv[7])
                # The control functions use Radians to determine the target position.
                # Here, we use maths.radians to convert degrees into radians.
                # http://www.coppeliarobotics.com/helpFiles/en/remoteApiFunctionsPython.htm#simxSetJointTargetPosition
                print "Motors target positions: " + str(ashoulder) + " " + str(aelbow) + " " + str(awrist)
                vrep.simxSetJointTargetPosition(clientID, wristHandle, math.radians(awrist), opmode)
                vrep.simxSetJointTargetPosition(clientID, elbowHandle, math.radians(aelbow), opmode)
                vrep.simxSetJointTargetPosition(clientID, shoulderHandle, math.radians(ashoulder), opmode)

                # Wait in order to let the motors finish their movements
                # Tip: there must be a more efficient way to do it...
                time.sleep(3)

                # Get the motors effective positions after the movement sequence
                # http://www.coppeliarobotics.com/helpFiles/en/remoteApiFunctionsPython.htm#simxGetJointPosition
                pwrist = vrep.simxGetJointPosition(clientID, wristHandle, opmode)
                pelbow = vrep.simxGetJointPosition(clientID, elbowHandle, opmode)
                pshoulder = vrep.simxGetJointPosition(clientID, shoulderHandle, opmode)
                print "Motors reached positions: " + str(ashoulder) + " " + str(aelbow) + " " + str(awrist)

                # Get the robot position after the movement sequence
                pret, robotPos = vrep.simxGetObjectPosition(clientID, robotHandle, -1, vrep.simx_opmode_buffer)
                print "2w1a position: (x = " + str(robotPos[0]) +\
                      ", y = " + str(robotPos[1]) + ")"

                # Get the robot orientation after the movement sequence
                oret, robotOrient = vrep.simxGetObjectOrientation(clientID, robotHandle, -1, vrep.simx_opmode_buffer)
                print "2w1a orientation: (x = " + str(robotOrient[0]) +\
                      ", y = " + str(robotOrient[1]) +\
                      ", z = " + str(robotOrient[2]) + ")"

            # End the simulation, wait to be sure V-REP had the time to stop it entirely
            # http://www.coppeliarobotics.com/helpFiles/en/remoteApiFunctionsPython.htm#simxStopSimulation
            vrep.simxStopSimulation(clientID, opmode)
            time.sleep(1)
            print "----- Simulation ended -----"

    # Close the connection to V-REP remote server
    # http://www.coppeliarobotics.com/helpFiles/en/remoteApiFunctionsPython.htm#simxFinish
    vrep.simxFinish(clientID)
else:
    print ('Failed connecting to remote API server')
print ('End')
