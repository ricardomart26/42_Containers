#include <iostream>
#include <vector>
#include <iterator>
int main()
{
    {
        std::vector<int> vec(10);
        for (int i = 0; i < 10; i++)
            vec.push_back(i);
        vec.insert(vec.begin(), 3, 10);
        for (int i : vec)
            std::cout << i << std::endl;
    }
    // {
    //     std::vector<int> vec {1, 2, 3, 4};

    //     for (auto x : vec)
    //         std::cout << x << std::endl;
    //     // std::cout << vec.capacity() << std::endl;
    //     // std::cout << vec.size() << std::endl;
    // }
    #if 0
    {
        std::vector<int> vec(10, 20);
        std::cout << "capacity: " << vec.capacity() << std::endl;
        std::cout << "size: "<< vec.size() << std::endl;
        // for (auto i : vec)
        // {
            // std::cout << i << std::endl;
        // }
        vec.reserve(20);
        vec.push_back(21);
        std::vector<int>::iterator it = vec.begin();
        // std::cout << *it << std::endl;
        int counter = 0;
        for (;it != vec.end(); it++)
        {
            std::cout <<counter<<": "<< *it << std::endl;
            counter++;
        }
        std::cout << "capacity: " << vec.capacity() << std::endl;
        std::cout << "size: "<< vec.size() << std::endl;
        
    }

    std::vector<int> vec;
    std::cout << vec.capacity() << std::endl;

    std::vector<int>::iterator it_start = vec.begin();
    // std::vector<int>::iterator it_end = vec.end();

    while (it_start != vec.end())
    {
        std::cout << *it_start << std::endl;
        it_start++;
    }
    #endif
}
