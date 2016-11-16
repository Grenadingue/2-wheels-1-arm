cmake_minimum_required(VERSION 3.1.0 FATAL_ERROR)

# Find system boost package
find_package(Boost ${BOOST_VER} REQUIRED COMPONENTS system date_time random)

# Set project directories
set(PROJECT_F ${CMAKE_CURRENT_SOURCE_DIR}/source)
set(LIB_F ${CMAKE_CURRENT_SOURCE_DIR}/lib)
set(VREP_F ${LIB_F}/vrep)
set(SIO_F ${LIB_F}/socket.io-client/socket.io-client-cpp)
set(SIO_BUILD_F ${LIB_F}/socket.io-client/build)

add_executable(
	# Target executable
	2w1a_dev

	# Vrep remote API source files
	${VREP_F}/extApi.c
	${VREP_F}/extApiPlatform.c

	# Project source files
	${PROJECT_F}/main.cpp
	${PROJECT_F}/MainController.cpp
	${PROJECT_F}/AThreadedDataHandler.cpp
	${PROJECT_F}/WebServerBridge.cpp
	${PROJECT_F}/BackupDataController.cpp
	${PROJECT_F}/GeneticAlgoController.cpp
	${PROJECT_F}/VrepThreadedController.cpp
	${PROJECT_F}/AlgoParameters.cpp
	${PROJECT_F}/WebServerBridgeParameters.cpp
	${PROJECT_F}/BackupDataParameters.cpp
	${PROJECT_F}/VrepParameters.cpp
	${PROJECT_F}/Client.cpp
	${PROJECT_F}/VrepSimulationEvent.cpp
	${PROJECT_F}/VrepSimulationFinished.cpp
	${PROJECT_F}/ResultModel.cpp
	${PROJECT_F}/WritableResultModel.cpp
	${PROJECT_F}/World.cpp
	${PROJECT_F}/MotherNature.cpp
	${PROJECT_F}/Random.cpp
	${PROJECT_F}/Individual.cpp
	${PROJECT_F}/Genome.cpp
	${PROJECT_F}/_2w1a.cpp
	${PROJECT_F}/VrepAPI.cpp
	${PROJECT_F}/Physics.cpp
	${PROJECT_F}/Object.cpp
	${PROJECT_F}/Articulation.cpp
	${PROJECT_F}/Fitness.cpp
	${PROJECT_F}/Maths.cpp
)

# Include headers directories
include_directories(
	${SIO_F}/src
	${VREP_F}
	${PROJECT_F}
)

# C
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -ggdb")

# C++ compilation flags
set_property(TARGET 2w1a_dev PROPERTY CXX_STANDARD 11)
set_property(TARGET 2w1a_dev PROPERTY CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -ggdb -W -Wall -Wextra")

# Vrep compilation flags
ADD_DEFINITIONS(-DNON_MATLAB_PARSING -DMAX_EXT_API_CONNECTIONS=255)

# Libraries to link with project
add_library(sioclient STATIC IMPORTED)
set_target_properties(sioclient PROPERTIES IMPORTED_LOCATION ${SIO_BUILD_F}/libsioclient.a)
target_link_libraries(2w1a_dev sioclient)
target_link_libraries(2w1a_dev ${Boost_LIBRARIES})
target_link_libraries(2w1a_dev pthread)
