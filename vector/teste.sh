clang++ -Wall -Werror -Wextra create_teste.cpp
./a.out << END_OF_INPUTS
my_vector.cpp
ft::
std::
END_OF_INPUTS

cd ..
make re && ./container > my_output.txt
make re_teste && ./teste > teste.txt

diff my_output.txt teste.txt > diff.txt

rm my_output.txt teste.txt teste container

