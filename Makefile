SRCS 					= ./main.cpp
GraphSrcs				= ./Graphs/s21_graph.cpp
GraphAlgorithmsSrcs		= ./Graphs/s21_graph_algorithms.cpp

OBJS 					= $(SRCS:.cpp=.o)
DEPS 					= ${SRCS:.cpp=.d}
GraphObjs				= $(GraphSrcs:.cpp=.o)
GraphAlgorithmsObjs		= $(GraphAlgorithmsSrcs:.cpp=.o)
GraphDeps				= $(GraphSrcs:.cpp=.d)
GraphAlgorithmsDeps		= $(GraphAlgorithmsSrcs:.cpp=.d)
GraphName				= s21_graph.a
GraphAlgorithmsName		= s21_graph_algorithms.a
CPP						= g++ 
RM						= rm -f
CPPFLAGS				= -std=c++14 -Wall -Wextra -Werror -MMD -I. -fsanitize=address -g

NAME			= res

all:			 ${GraphName} ${GraphAlgorithmsName} $(NAME)

-include $(DEPS) $(GraphDeps) $(GraphAlgorithmsDeps)

${GraphName}: $(GraphObjs)
	ar rcs $@ ${GraphObjs}

${GraphAlgorithmsName}: ${GraphName} $(GraphAlgorithmsObjs)
	ar rcs $@  ${GraphAlgorithmsObjs}

$(NAME):		$(OBJS)
				$(CPP) $(CPPFLAGS) $(OBJS) ${GraphAlgorithmsName} ${GraphName} -o $(NAME) 
test:	./tests/test.cc
	$(CPP) $(CPPFLAGS) ./tests/test.cc ${GraphAlgorithmsName} ${GraphName} -o test -lgtest
clean:			
				$(RM) $(OBJS)
				$(RM) $(DEPS)
				$(RM) $(GraphObjs)
				$(RM) $(GraphDeps)
				$(RM) $(GraphAlgorithmsObjs)
				$(RM) $(GraphAlgorithmsDeps)	

fclean:			clean
				$(RM) $(NAME)
				$(RM) $(GraphName)
				$(RM) $(GraphAlgorithmsName)

re:				fclean all

.PHONY:			all clean fclean re s21_graph.a s21_graph_algorithms.a