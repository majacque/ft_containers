
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
NAME_FT				= ft_container.out
NAME_STD			= std_container.out

#######################################
#             DIRECTORIES             #
#######################################
OBJ_DIR_FT			= objs_ft/
OBJ_DIR_STD			= objs_std/
INC_DIR				= include/
PRV_DIR				= private/
SRC_DIR				= $(shell find src -type d)

vpath %.cpp $(foreach dir, $(SRC_DIR), $(dir):)
######################################
#            SOURCE FILES            #
######################################
SRC				=	\
					main.cpp			\
					run_sub_tests.cpp	\
					test_algorithm.cpp	\
					test_iterator_traits.cpp	\
					test_reverse_iterator.cpp	\
					test_type_traits.cpp	\
					test_utility.cpp		\
					test_vector.cpp			\
					test_map.cpp
#					test_rb_tree.cpp

######################################
#            OBJECT FILES            #
######################################
OBJ_FT				= ${SRC:.cpp=.o}
OBJ_FT				:= ${addprefix ${OBJ_DIR_FT}, ${OBJ_FT}}

OBJ_STD				= ${SRC:.cpp=.o}
OBJ_STD				:= ${addprefix ${OBJ_DIR_STD}, ${OBJ_STD}}

DEP_FT				= ${OBJ_FT:.o=.d}
DEP_STD				= ${OBJ_STD:.o=.d}

#######################################
#                FLAGS                #
#######################################
CXXFLAGS			= -Wall -Wextra -Werror -Wno-unused
CXXFLAGS			+= -std=c++98
CXXFLAGS			+= -MMD -MP
CXXFLAGS			+= -Weffc++ -pedantic
CXXFLAGS			+= -I${INC_DIR} -I${PRV_DIR}

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

${NAME_FT}: ${OBJ_FT}
	${CXX} ${OUTPUT_OPTION} ${OBJ_FT} ${LDFLAGS}

${NAME_STD}: ${OBJ_STD}
	${CXX} ${OUTPUT_OPTION} ${OBJ_STD} ${LDFLAGS}

all: ${NAME_FT}

-include ${DEP_FT}
-include ${DEP_STD}

${OBJ_DIR_FT}%.o: %.cpp | ${OBJ_DIR_FT}
	${CXX} -c ${OUTPUT_OPTION} ${CXXFLAGS} $<

${OBJ_DIR_FT}:
	${MKDIR} ${@D}

${OBJ_DIR_STD}%.o: %.cpp | ${OBJ_DIR_STD}
	${CXX} -c ${OUTPUT_OPTION} ${CXXFLAGS} -DSTD $<

${OBJ_DIR_STD}:
	${MKDIR} ${@D}

clean:
	${RM} ${OBJ_DIR_FT} ${OBJ_DIR_STD}

fclean:
	${RM} ${OBJ_DIR_FT} ${NAME_FT} ${OBJ_DIR_STD} ${NAME_STD}

re: fclean all