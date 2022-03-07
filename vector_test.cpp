#include <iostream>
#include <vector>

int main()
{
    std::vector<int> vec;
    std::cout << vec.capacity() << std::endl;

    std::vector<int>::iterator it_start = vec.begin();
    // std::vector<int>::iterator it_end = vec.end();

    while (it_start != vec.end())
    {
        std::cout << *it_start << std::endl;
        it_start++;
    }

}