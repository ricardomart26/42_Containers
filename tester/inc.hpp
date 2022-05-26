#ifndef INC_HPP
#define INC_HPP

#include <iostream>
#include <string>
// #include <fstream>
#include <vector>
#include <algorithm>

// #include "../STL/vector/vector.hpp"
#define	GREEN "\033[0;32m"
#define	RED "\033[31m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"      /* Blue */

#define	RESET "\033[0m"
#define TEST_SIZE 16

#define LOW 10
#define MID 100
#define HIGH 1000
#define CRAZY_HIGH 10000000
// #ifndef FT
//     #define FT 1
// #endif

void	constructor_test();
void	push_back_test();
void	max_size_test();
void	assign_test();
void	at_test();
void	back_test();
void	clear_test();
void	erase_test();
void	front_test();
void	get_allocator_test();
void	insert_test();
void	max_size_test();
void	op_test();
void	pop_back_test();
void	reserve_test();
void	resize_test();
void	swap_test();

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


template    <typename T>
int    wrong_msg(const std::string &err, T ft, T std)
{
    std::cerr << RED << " [ KO " << err << ": (ft = " << ft << " and std = " << std << ")] " << RESET;
    return (-1);
}

template <typename T>
int    compare_vec(ft::vector<T> ft_vec, std::vector<T> std_vec)
{
    if (ft_vec.empty() != std_vec.empty())
        return (wrong_msg("Vectors Empty func different", ft_vec.empty(), std_vec.empty()));

    if (ft_vec.size() != std_vec.size())
        return (wrong_msg("Vectors Size is different", ft_vec.size(), std_vec.size()));

    // std::cout << "ft cap: " << ft_vec.capacity() << " std cap: " << std_vec.capacity() << std::endl;

    if (ft_vec.capacity() != std_vec.capacity())
        return (wrong_msg("Vectors Capacity is different", ft_vec.capacity(), std_vec.capacity()));

    ft::vector<int>::iterator ft_it = ft_vec.begin();
    std::vector<int>::iterator std_it = std_vec.begin();

    for (; ft_it != ft_vec.end() && std_it != std_vec.end(); ft_it++, std_it++)
    {
        if (*ft_it != *std_it)
        {
            std::cerr << RED << "[ KO Vectors Elements are different ] " << RESET << std::endl;
            ft_it = ft_vec.begin();
            std::cout << "\nFT ELEMENTS: [ ";
            for (; ft_it != ft_vec.end(); ft_it++)
                std::cout << *ft_it << ", ";
            std::cout << "\\0 ]\n";

            std_it = std_vec.begin();
            std::cout << "STD ELEMENTS: [ ";
            for (; std_it != std_vec.end(); std_it++)
                std::cout << *std_it << ", ";
            std::cout << "\\0 ]\n\n";
            return (-1);
        }
    }
    std::cout << GREEN << " [ OK ] " << RESET;
    return (0);
}


template <typename T>
void    print_vec_info(T vec)
{
    std::cout << "\n";
    if (vec.empty())
        std::cout << "Empty: YES\n";
    else
        std::cout << "Empty: NO\n";
    
    std::cout << "SIZE: " << vec.size() << std::endl;
    std::cout << "CAPACITY: " << vec.capacity() << std::endl;
    
    typename T::iterator it = vec.begin();
    std::cout << "ELEMENTS: [ ";
    for (; it != vec.end(); it++)
    {
        std::cout << *it << ", ";
    }
    std::cout << "\\0 ]\n\n";
}

template <typename T>
T   &random_vector_constructor(size_t size)
{
    T   &vec = *new T(size);

    for (size_t i = 0; i < size; i++)
        vec.push_back((size / 2) + (size * (i + 1)));

    return (vec);
}


#endif
