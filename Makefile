
# tester avec g++ +  -Weffc++ -pedantic
# tester avec scan-build-12 make
######################################
#              COMMANDS              #
######################################
# CXX					= g++
CXX					= c++
MKDIR				= mkdir -p
RM					= rm -rf

######################################
#             EXECUTABLE             #
######################################
NAME				= container.out

#######################################
#             DIRECTORIES             #
#######################################
OBJ_DIR				= objs/
INC_DIR				= include/
PRV_DIR				= private/
SRC_DIR				= $(shell find src -type d)

vpath %.cpp $(foreach dir, $(SRC_DIR), $(dir):)
######################################
#            SOURCE FILES            #
######################################
SRC				=	\
					main.cpp	\
					run_sub_tests.cpp	\
					test_iterator_traits.cpp	\
					test_reverse_iterator.cpp	\
					test_type_traits.cpp	\

######################################
#            OBJECT FILES            #
######################################
OBJ				= ${SRC:.cpp=.o}
OBJ				:= ${addprefix ${OBJ_DIR}, ${OBJ}}

DEP				= ${OBJ:.o=.d}

#######################################
#                FLAGS                #
#######################################
CXXFLAGS			= -Wall -Wextra -Werror -Wno-unused
CXXFLAGS			+= -I${INC_DIR} -I${PRV_DIR}
CXXFLAGS			+= -std=c++98
CXXFLAGS			+= -MMD -MP
# CXXFLAGS			+= -Weffc++ -pedantic

LDFLAGS			=

ifeq (${DEBUG}, 1)
	CXXFLAGS	+= -g3
endif

ifeq (${DEBUG}, 2)
	CXXFLAGS	+= -fsanitize=address -g3
	LDFLAGS		+= -fsanitize=address
endif

#######################################
#                RULES                #
#######################################
.PHONY: all clean fclean re

${NAME}: ${OBJ}
	${CXX} ${OUTPUT_OPTION} ${OBJ} ${LDFLAGS}

all: ${NAME}

-include ${DEP}

${OBJ_DIR}%.o: %.cpp | ${OBJ_DIR}
	${CXX} -c ${OUTPUT_OPTION} ${CXXFLAGS} $<

${OBJ_DIR}:
	${MKDIR} ${@D}

clean:
	${RM} ${OBJ_DIR}

fclean:
	${RM} ${OBJ_DIR} ${NAME}

re: fclean all