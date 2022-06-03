NAME = container
CC = c++ -Wall -Wextra -Werror -std=c++98 -g -fsanitize=address
VEC_SRC = compare.cpp vector/constructor.cpp vector/push_back.cpp vector/max_size.cpp vector/resize.cpp \
		vector/assign.cpp vector/at.cpp vector/back.cpp vector/clear.cpp vector/erase.cpp vector/front.cpp \
		vector/get_allocator.cpp vector/insert.cpp vector/op.cpp vector/pop_back.cpp vector/reserve.cpp vector/swap.cpp

all: $(NAME)

$(NAME): vec_test

vec_test:
	$(CC) $(VEC_SRC) -D "FT=0" -o vecTest

compare:

clean:
	test ! -s $(NAME) || rm $(NAME)

re: clean all

.PHONY: all clean re
