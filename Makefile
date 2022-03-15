NAME = container

CC = clang++ -Wall -Wextra -Werror -fsanitize=address -pedantic -std=c++11

SRC = vector/my_vector.cpp

SRC_TESTE = vector/vector_test.cpp

all: $(NAME)

$(NAME): 
	$(CC) $(SRC) -o $(NAME)

teste: 
	$(CC) $(SRC_TESTE) -o teste

clean:
	test ! -s $(NAME) || rm $(NAME)

clean_teste:
	test ! -s teste || rm teste

re: clean all

re_teste: clean_teste teste

.PHONY: all clean re
