#include <iostream>
#include <vector>
#include <iterator>

int main()
{
    {
        std::vector<int> vec(10);
        for (int i = 0; i < 10; i++)
            vec.push_back(i);
        // std::cout << vec.max_size() << std::endl;
        
        std::cout << "size: " << vec.size() << "\n";
        // std::cout << "last element: " << vec[vec.size()] << "\n";
        int i = 0;
        for (std::vector<int>::iterator it = vec.begin(); it != vec.end(); it++)
            std::cout << i++ << ": " << *it << std::endl;
        std::cout << "size: " << vec.size() << "\n";
        vec.push_back(20);
        std::cout << "last element: " << vec[vec.size() - 1] << "\n";
        std::cout << "size: " << vec.size() << "\n";
        i = 0;
        for (std::vector<int>::iterator it = vec.begin(); it != vec.end(); it++)
            std::cout << i++ << ": " << *it << std::endl;
        std::cout << "<<<<<<<<<<<   Pop back  >>>>>>>>>>>>\n";
        vec.pop_back();
        i = 0;
        for (std::vector<int>::iterator it = vec.begin(); it != vec.end(); it++)
            std::cout << i++ << ": " << *it << std::endl;
        
    }
    
    #if 0
    {
        std::vector<int> vec(10);
        for (int i = 0; i < 10; i++)
            vec.push_back(i);
        std::cout << vec.max_size() << std::endl;
        vec.push_back(10);
        std::cout << vec[vec.size() - 1];
        // std::vector<int> vec(10);
        // for (int i = 0; i < 10; i++)
        //     vec.push_back(i);
        // vec.insert(vec.begin(), 3, 10);
        // for (int i : vec)
        //     std::cout << i << std::endl;
    }
    // {
    //     std::vector<int> vec {1, 2, 3, 4};

    //     for (auto x : vec)
    //         std::cout << x << std::endl;
    //     // std::cout << vec.capacity() << std::endl;
    //     // std::cout << vec.size() << std::endl;
    // }
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
