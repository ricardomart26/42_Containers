NAME = map_test 

CC = c++ -Wall -Wextra -Werror -fsanitize=address 

SRC = map_test.cpp 

INC = binary_search_tree.hpp 

all: $(NAME)

$(NAME): $(SRC) $(INC)
	$(CC) $(SRC) -o $(NAME)

clean:
	rm $(NAME)

re: clean re

.PHONY: all clean re




