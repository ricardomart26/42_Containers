#ifndef INC_HPP
#define INC_HPP

#include <iostream>
#include <string>
#include <fstream>
// #include "../STL/vector/vector.hpp"
#define	GREEN "\033[0;32m"
#define	RESET "\033[0m"


// #ifndef FT
//     #define FT 1
// #endif

void	constructor_test();
void	push_back_test();

#if FT==1 //CREATE A REAL STL EXAMPLE
	#include <map>
	#include <stack>
	#include <vector>
	namespace ft = std;
    #define VECTOR_OUTPUT_DIR "output/stl_vector_out/"
    #define MAP_OUTPUT_DIR "output/stl_map_out/"
#else
    #include "../STL/vector/vector.hpp"
    #define VECTOR_OUTPUT_DIR "output/my_vector_out/"
    #define MAP_OUTPUT_DIR "output/my_map_out/"
#endif

template <typename T>
void    print_vec_info(ft::vector<T> vec, std::ofstream &file)
{
    file << "\n";
    if (vec.empty())
        file << "Empty: YES\n";
    else
        file << "Empty: NO\n";
    
    file << "SIZE: " << vec.size() << std::endl;
    file << "CAPACITY: " << vec.capacity() << std::endl;
    
    ft::vector<int>::iterator it = vec.begin();
    file << "ELEMENTS: [ ";
    for (; it != vec.end(); it++)
    {
        file << *it << ", ";
    }
    file << "\\0 ]\n\n";
}


#endif
