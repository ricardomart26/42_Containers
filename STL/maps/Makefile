NAME = map_test 

CC = c++ -Wall -Wextra -Werror -fsanitize=address 

SRC = map_test.cpp 

all: $(NAME)

$(NAME):
	$(CC) $(SRC) -o $(NAME)

clean:
	rm $(NAME)

re: clean re

.PHONY: all clean re




