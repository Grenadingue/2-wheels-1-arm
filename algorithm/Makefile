# Utilities
CC = 		gcc

CXX = 		g++

RM = 		rm -f

# Exe name
NAME = 		2w1a

# Folders
CODE_F =	cpp

VREP_F = 	$(CODE_F)/vrep

# Srcs
VREP_SRCS = 	$(VREP_F)/extApi.c \
		$(VREP_F)/extApiPlatform.c

PROJ_SRCS = 	$(CODE_F)/MainController.cpp \
		$(CODE_F)/AThreadedDataHandler.cpp \
		$(CODE_F)/WebServerBridge.cpp \
		$(CODE_F)/BackupDataController.cpp \
		$(CODE_F)/GeneticAlgoController.cpp \
		$(CODE_F)/AlgoParameters.cpp \
		$(CODE_F)/ResultModel.cpp \
		$(CODE_F)/WritableResultModel.cpp \
		$(CODE_F)/World.cpp \
		$(CODE_F)/MotherNature.cpp \
		$(CODE_F)/Random.cpp \
		$(CODE_F)/Individual.cpp \
		$(CODE_F)/Genome.cpp \
		$(CODE_F)/_2w1a.cpp \
		$(CODE_F)/VrepAPI.cpp \
		$(CODE_F)/Physics.cpp \
		$(CODE_F)/Object.cpp \
		$(CODE_F)/Articulation.cpp \
		$(CODE_F)/Fitness.cpp \
		$(CODE_F)/Maths.cpp

# Objs
OBJS =		$(VREP_SRCS:.c=.o) $(PROJ_SRCS:.cpp=.o)

# Flags
VREP_FLAGS = 	-DNON_MATLAB_PARSING -DMAX_EXT_API_CONNECTIONS=255 -I $(VREP_F)/

ERROR_FLAGS =	-W -Wall -Wextra

CFLAGS += 	$(VREP_FLAGS) -ggdb

CXXFLAGS += 	$(VREP_FLAGS) $(ERROR_FLAGS) -std=c++11 -ggdb

LDFLAGS +=	-lpthread


all:		$(NAME)

$(NAME):	$(OBJS)
		$(CXX) -o $(NAME) $(OBJS) $(LDFLAGS)

clean:
		$(RM) $(OBJS)

fclean:		clean
		$(RM) $(NAME)

re:		fclean all

.PHONY: 	all clean fclean re
