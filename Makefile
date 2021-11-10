SRCS		= main.cpp
		  
#OBJ_DIR		= objs/

OBJS		= $(SRCS:.cpp=.o)

HEADER		= -I includes

CXX			= clang++

CXXFLAGS	= -Wall -Wextra -Werror -g3 -std=c++98


NAME = ft_containers

.cpp.o:
	$(CXX) $(CXXFLAGS) $(HEADER) -c $< -o $(<:.cpp=.o)

$(NAME): $(OBJS) 
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)

all :$(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all	
.PHONY: all clean fclean re
