SRCS		= main_test.cpp \
			  test_vector.cpp \
			  test_stack.cpp \
			  test_map.cpp  \
			  common.cpp
		  
OBJS		= $(addprefix test/, $(SRCS:.cpp=.o))

HEADER		= -I includes

CNTR_FILES = condition.hpp			\
			 iterator_map.hpp		\
			 map.hpp   				\
			 pair.hpp             	\
			 stack.hpp				\
			 iterator.hpp   		\
			 iterator_vector.hpp  	\
			 node.hpp  				\
			 reverse_iterator.hpp  	\
			 vector.hpp

TEST_FILES = common.hpp \
			 test_stack.hpp \
			 test_map.hpp \
			 test_vector.hpp

TEST_HPP = $(addprefix test/, $(TEST_FILES))

HPP = $(addprefix includes/, $(CNTR_FILES))

CXX			= clang++

CXXFLAGS	= -Wall -Wextra -Werror -g3 -std=c++98


NAME = ft_containers

.cpp.o: $(HPP) $(TEST_HPP) 
	$(CXX) $(CXXFLAGS) $(HEADER) -c $< -o $(<:.cpp=.o)

$(NAME): $(OBJS) $(HPP) $(TEST_HPP)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)

all :$(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all	
.PHONY: all clean fclean re
