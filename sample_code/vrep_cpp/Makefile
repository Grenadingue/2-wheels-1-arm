# Utilities
CC = gcc

CXX = g++

RM = rm -f

# Exe name
NAME = vrep_sample

# Folders
VREP_F = vrep

# Srcs
PROJ_SRCS = 	main.cpp

VREP_SRCS = 	$(VREP_F)/extApi.c \
		$(VREP_F)/extApiPlatform.c

# Objs
OBJS =		$(PROJ_SRCS:.cpp=.o) $(VREP_SRCS:.c=.o)

# Flags
VREP_FLAGS = 	-DNON_MATLAB_PARSING -DMAX_EXT_API_CONNECTIONS=255 -I $(VREP_F)/

CFLAGS += 	$(VREP_FLAGS)

CXXFLAGS += 	$(VREP_FLAGS)

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
