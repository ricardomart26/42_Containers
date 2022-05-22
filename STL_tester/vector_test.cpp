#include <iostream>

#ifndef FT
    #define FT 1
#endif

#if FT==1 //CREATE A REAL STL EXAMPLE
	#include <map>
	#include <stack>
	#include <vector>
	namespace ft = std;
#else
    #include "../STL/vector/vector.hpp"
#endif


template <typename T>
void    print_vec_info(ft::vector<T> vec)
{
    std::cout << "\n";
    if (vec.empty())
        std::cout << "Empty: YES\n";
    else
        std::cout << "Empty: NO\n";
    
    std::cout << "SIZE: " << vec.size() << std::endl;
    std::cout << "CAPACITY: " << vec.capacity() << std::endl;
    
    ft::vector<int>::iterator it = vec.begin();
    std::cout << "ELEMENTS: [ ";
    for (; it != vec.end(); it++)
    {
        std::cout << *it << ", ";
    }
    std::cout << "\\0 ]\n\n";
}

void	push_back_test()
{

        ft::vector<int> vecA(10);
        ft::vector<int> vecB(10);
        ft::vector<int> vecC(10);
        ft::vector<int> vecD(10);

        for (int i = 0; i < 10; i++)
            vecA.push_back(i);

        int i = 0;
        for (ft::vector<int>::iterator it = vecA.begin(); it != vecA.end(); it++)
            std::cout << i++ << ": " << *it << std::endl;
        
        std::cout << "\n<<<<<<<<<<<  Push back  >>>>>>>>>>>>\n";
        vecA.push_back(20);
        i = 0;
        for (ft::vector<int>::iterator it = vecA.begin(); it != vecA.end(); it++)
            std::cout << i++ << ": " << *it << std::endl;
        std::cout << "last element: " << vecA[vecA.size() - 1] << "\n";
        std::cout << "size: " << vecA.size() << "\n";
}

void	constructor_test()
{
    {
        std::cout << "<<<<<<<<<<<  Default constructor  >>>>>>>>>>>>" << std::endl;
        ft::vector<int> vecA;
        print_vec_info(vecA);
    }

    {
        std::cout << "<<<<<<<<<<<  Constructor with size  >>>>>>>>>>>>" << std::endl;
        ft::vector<int> vecA(10);
        ft::vector<int> vecB(0);
        try {
            ft::vector<int> vecC(-10);
            print_vec_info(vecC);
        } catch (const std::exception &e) {
            e.what();
        }
        print_vec_info(vecA);
        print_vec_info(vecB);
    }

    {
        std::cout << "<<<<<<<<<<<    >>>>>>>>>>>>" << std::endl;
    }
    // std::cout << "" << std::endl;
	// ft::vector<int> vecB(10);
    // std::cout << "" << std::endl;
	// ft::vector<int> vecC(10);
    
}


int main()
{

    std::cout << std::endl;
    constructor_test();
    #if 0
    {
        ft::vector<int> vec;

        for(int i = 0; i < 10; i++)
            vec.push_back(i);

        for(int i = 0; i < 1; i++)
            vec.insert(vec.begin() + 2, 10, 5);

        for(ft::vector<int>::iterator it = vec.begin(); it != vec.end() ; it++)
            std::cout << *it << std::endl;

    }
    {
        ft::vector<int> vec(10, 2);
        
        std::cout << "\n<<<<<<<<<<<  Pop back  >>>>>>>>>>>>\n";

        vec.pop_back();
        i = 0;
        for (ft::vector<int>::iterator it = vec.begin(); it != vec.end(); it++)
            std::cout << i++ << ": " << *it << std::endl;
        std::cout << "size: " << vec.size() << "\n";
        // std::cout << "capacity: " << vec.capacity() << "\n";

        std::cout << "\n<<<<<<<<<<<  Resize  >>>>>>>>>>>>\n";

        vec.resize(vec.size() - 10);
        i = 0;
        for (ft::vector<int>::iterator it = vec.begin(); it != vec.end(); it++)
            std::cout << i++ << ": " << *it << std::endl;
        std::cout << "size: " << vec.size() << "\n";
        // std::cout << "capacity: " << vec.capacity() << "\n";
        
        vec.resize(vec.size() + 10);
        i = 0;
        for (ft::vector<int>::iterator it = vec.begin(); it != vec.end(); it++)
            std::cout << i++ << ": " << *it << std::endl;
        std::cout << "size: " << vec.size() << "\n";
        // std::cout << "capacity: " << vec.capacity() << "\n";
        
        vec.resize(vec.size());
        i = 0;
        for (ft::vector<int>::iterator it = vec.begin(); it != vec.end(); it++)
            std::cout << i++ << ": " << *it << std::endl;
        std::cout << "size: " << vec.size() << "\n";
        // std::cout << "capacity: " << vec.capacity() << "\n";
        
        vec.resize(vec.size(), 10);
        i = 0;
        for (ft::vector<int>::iterator it = vec.begin(); it != vec.end(); it++)
            std::cout << i++ << ": " << *it << std::endl;
        std::cout << "size: " << vec.size() << "\n";
        // std::cout << "capacity: " << vec.capacity() << "\n";
        
        vec.resize(vec.size() + 5, 10);
        i = 0;
        for (ft::vector<int>::iterator it = vec.begin(); it != vec.end(); it++)
            std::cout << i++ << ": " << *it << std::endl;
        std::cout << "size: " << vec.size() << "\n";
        // std::cout << "capacity: " << vec.capacity() << "\n";
        
        std::cout << "\n<<<<<<<<<<<  Assign  >>>>>>>>>>>>\n";

        vec.assign(vec.size() + 5, 10);
        i = 0;
        for (ft::vector<int>::iterator it = vec.begin(); it != vec.end(); it++)
            std::cout << i++ << ": " << *it << std::endl;
        std::cout << "size: " << vec.size() << "\n";
        // std::cout << "capacity: " << vec.capacity() << "\n";
        
        vec.assign(vec.begin() + 5, vec.end());
        i = 0;
        for (ft::vector<int>::iterator it = vec.begin(); it != vec.end(); it++)
            std::cout << i++ << ": " << *it << std::endl;
        std::cout << "size: " << vec.size() << "\n";
        // std::cout << "capacity: " << vec.capacity() << "\n";
        

        std::cout << "\n<<<<<<<<<<<  Insert  >>>>>>>>>>>>\n";

        vec.insert(vec.begin() + 4, 20);
        i = 0;
        for (ft::vector<int>::iterator it = vec.begin(); it != vec.end(); it++)
            std::cout << i++ << ": " << *it << std::endl;
        std::cout << "size: " << vec.size() << "\n";
        // std::cout << "capacity: " << vec.capacity() << "\n";
        
        ft::vector<int>::iterator pos = vec.insert(vec.begin(), 20);
        std::cout << *pos << std::endl;
        i = 0;
        for (ft::vector<int>::iterator it = vec.begin(); it != vec.end(); it++)
            std::cout << i++ << ": " << *it << std::endl;
        std::cout << "size: " << vec.size() << "\n";
        // std::cout << "capacity: " << vec.capacity() << "\n";

        pos = vec.insert(vec.end(), 25);
        i = 0;
        std::cout << *pos << std::endl;
        for (ft::vector<int>::iterator it = vec.begin(); it != vec.end(); it++)
            std::cout << i++ << ": " << *it << std::endl;
        std::cout << "size: " << vec.size() << "\n";

        ft::vector<int> vec2(10, 23);
        vec.insert(vec.begin(), vec2.begin() + 5, vec2.begin() + 10);
        // std::cout << "capacity: " << vec.capacity() << "\n";

        std::cout << "\n<<<<<<<<<<<  Copy construct  >>>>>>>>>>>>\n";
        
        ft::vector<int> vec_copy(vec);

        try {
            vec_copy.at(vec_copy.size());
        } catch(const std::out_of_range& oor)
        {
            std::cerr << "Out of Range error: " << oor.what() << '\n';
        }
        i = 0;
        for (ft::vector<int>::iterator it = vec_copy.begin(); it != vec_copy.end(); it++)
            std::cout << i++ << ": " << *it << std::endl;
        std::cout << "size: " << vec_copy.size() << "\n";
        // std::cout << "capacity: " << vec_copy.capacity() << "\n";

        i = 0;
        for (ft::vector<int>::iterator it = vec.begin(); it != vec.end(); it++)
            std::cout << i++ << ": " << *it << std::endl;
        std::cout << "size: " << vec.size() << "\n";
        // std::cout << "capacity: " << vec.capacity() << "\n";

        std::cout << "\n<<<<<<<<<<<  Assignment Operator  >>>>>>>>>>>>\n";

        ft::vector<int> vec_assign;
        vec_assign = vec;

        i = 0;
        for (ft::vector<int>::iterator it = vec_assign.begin(); it != vec_assign.end(); it++)
            std::cout << i++ << ": " << *it << std::endl;
        std::cout << "size: " << vec_assign.size() << "\n";
        // std::cout << "capacity: " << vec_assign.capacity() << "\n";

        i = 0;
        for (ft::vector<int>::iterator it = vec.begin(); it != vec.end(); it++)
            std::cout << i++ << ": " << *it << std::endl;
        std::cout << "size: " << vec.size() << "\n";
        // std::cout << "capacity: " << vec.capacity() << "\n";

        std::cout << "\n<<<<<<<<<<<  Range Contructor  >>>>>>>>>>>>\n";

        ft::vector<int> vec_range(vec.begin(), vec.end());

        i = 0;
        for (ft::vector<int>::iterator it = vec_range.begin(); it != vec_range.end(); it++)
            std::cout << i++ << ": " << *it << std::endl;
        std::cout << "size: " << vec_range.size() << "\n";
        // std::cout << "capacity: " << vec_range.capacity() << "\n";

        i = 0;
        for (ft::vector<int>::iterator it = vec.begin(); it != vec.end(); it++)
            std::cout << i++ << ": " << *it << std::endl;
        std::cout << "size: " << vec.size() << "\n";
        // std::cout << "capacity: " << vec.capacity() << "\n";

        std::cout << "\n<<<<<<<<<<<  Erase  >>>>>>>>>>>>\n";

        vec.erase(vec.begin() + 4);

        i = 0;
        for (ft::vector<int>::iterator it = vec.begin(); it != vec.end(); it++)
            std::cout << i++ << ": " << *it << std::endl;
        std::cout << "size: " << vec.size() << "\n";
        // std::cout << "capacity: " << vec.capacity() << "\n";
        
        vec.erase(vec.begin());
        // vec.erase(vec.begin() + (vec.size() - 2));

        i = 0;
        for (ft::vector<int>::iterator it = vec.begin(); it != vec.end(); it++)
            std::cout << i++ << ": " << *it << std::endl;
        std::cout << "size: " << vec.size() << "\n";


        std::cout << "\n<<<<<<<<<<<  Erase  >>>>>>>>>>>>\n";

        vec.swap(vec_range);

        i = 0;
        for (ft::vector<int>::iterator it = vec.begin(); it != vec.end(); it++)
            std::cout << i++ << ": " << *it << std::endl;
        for (ft::vector<int>::iterator it = vec_range.begin(); it != vec_range.end(); it++)
            std::cout << i++ << ": " << *it << std::endl;
        std::cout << "size: " << vec.size() << "\n";
        std::cout << "size: " << vec_range.size() << "\n";
        // std::cout << "capacity: " << vec.capacity() << "\n";
        
        vec.swap(vec_range);
        // vec.erase(vec.begin() + (vec.size() - 2));

        i = 0;
        for (ft::vector<int>::iterator it = vec.begin(); it != vec.end(); it++)
            std::cout << i++ << ": " << *it << std::endl;
        for (ft::vector<int>::iterator it = vec_range.begin(); it != vec_range.end(); it++)
            std::cout << i++ << ": " << *it << std::endl;
        std::cout << "size: " << vec.size() << "\n";
        std::cout << "size: " << vec_range.size() << "\n";
        // std::cout << "capacity: " << vec.capacity() << "\n";
        // ft::vector<int>::iterator it = vec.end();
        // it = it + 4;
        // std::cout << *it << std::endl;
        // for (; it != vec.end(); it++)
        //     std::cout << *(it) << std::endl;
        // vec.insert(it, 3, 2);
        // vec.insert(it, 3, 2);
        // // vec.insert(it + 21, 3, 2);
        // for (int i : vec)
        //     std::cout << i << std::endl;
    }
    // #if 0
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
