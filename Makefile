NAME = container

CC = clang++ -Wall -Wextra -g -Werror -pedantic -std=c++98

SRC = vector/my_vector.cpp

VEC_SRC = STL_tester/vector_test.cpp

SRC_TEST = vector/test.cpp

all: $(NAME)

$(NAME): 
	$(CC) $(SRC) -o $(NAME)



vec_test:
	$(CC) $(VEC_SRC) -D "FT=0" -o my_vecTest
	$(CC) $(VEC_SRC) -D "FT=1" -o stl_vecTest

test:
	$(CC) $(SRC_TEST) -o test

clean:
	test ! -s $(NAME) || rm $(NAME)

clean_test:
	test ! -s test || rm test

re: clean all

re_test: clean_test test

.PHONY: all clean re
