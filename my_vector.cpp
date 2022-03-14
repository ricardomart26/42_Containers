#include <iostream>
// #include <vector>
#include "vector.hpp"

int main()
{
    {
        ft::vector<int> vec(10);
        for (int i = 0; i < 10; i++)
            vec.push_back(i);
        ft::vector<int>::iterator it = vec.end();
        // it = it + 4;
        // std::cout << *it << std::endl;
        // for (; it != vec.end(); it++)
        //     std::cout << *(it) << std::endl;
        // vec.insert(it, 3, 2);
        vec.insert(it, 3, 2);
        // vec.insert(it + 21, 3, 2);
        for (int i : vec)
            std::cout << i << std::endl;
    }

    #if 0
    {
        // ft::vector<int> vec = {1, 2, 3};
        std::cout << vec.capacity() << std::endl;
        std::cout << vec.size() << std::endl;
        vec.push_back(20);
    }
    ft::vector<int> vec(10, 20);
    ft::vector<int> copy(20, 2);
    vec = copy;
    std::cout << "capacity: " << vec.capacity() << std::endl;
    std::cout << "size: "<< vec.size() << std::endl;
    // for (auto i : vec)
    // {
        // std::cout << i << std::endl;
    // }
    vec.reserve(20);
    vec.push_back(21);
    ft::vector<int>::Iterator it = vec.begin();
    // std::cout << *it << std::endl;
    int counter = 0;
    for (;it != vec.end(); it++)
    {
        std::cout <<counter<<": "<< *it << std::endl;
        counter++;
    }
    std::cout << "capacity: " << vec.capacity() << std::endl;
    std::cout << "size: "<< vec.size() << std::endl;
    #endif
}
