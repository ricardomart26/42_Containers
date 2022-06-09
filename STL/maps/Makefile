NAME = map_test 

CC = c++ -Wall -Wextra -Werror -fsanitize=address -g

SRC = map_test.cpp 

SRC_PAIR = pairs_test.cpp 
INC = binary_search_tree.hpp map.hpp 

all: $(NAME)

$(NAME): $(SRC) $(INC)
	$(CC) $(SRC) -o $(NAME)

pair: $(SRC_PAIR) $(INC)
	$(CC) $(SRC_PAIR) -o $(NAME)

clean:
	rm $(NAME)

re: clean re

.PHONY: all clean re




