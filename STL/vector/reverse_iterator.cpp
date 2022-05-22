#include "reverse_iterator.hpp"
#include "vector.hpp"

int main(void)
{
    ft::vector<int> vec;

    for (int i = 0; i < 100; i++)
        vec.push_back(i * 2);

    ft::vector<int>::reverse_iterator it = vec.rbegin();

    return (0);
}