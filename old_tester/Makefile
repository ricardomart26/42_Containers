NAME = container
CC = c++ -Wall -Wextra -Werror -pedantic -std=c++98 -g -fsanitize=address
VEC_SRC = tester.cpp vector/constructor.cpp vector/push_back.cpp
TEST_SRC = 
BIN= ../bin

all: $(NAME)

$(NAME): vec_test

vec_test:
	$(CC) $(VEC_SRC) -D "FT=0" -o $(BIN)/my_vecTest
	$(CC) $(VEC_SRC) -D "FT=1" -o $(BIN)/stl_vecTest
	$(CC)

compare:

clean:
	test ! -s $(NAME) || rm $(NAME)

re: clean all

.PHONY: all clean re
