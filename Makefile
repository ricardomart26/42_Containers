NAME = container

CC = clang++ -Wall -Wextra -g -Werror -pedantic -std=c++98

SRC = vector/my_vector.cpp

SRC_TESTE = vector/teste.cpp

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
