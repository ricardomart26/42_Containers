#ifndef INC_HPP
#define INC_HPP

#include <iostream>
#include <string>
// #include <fstream>
#include <vector>
// #include "../STL/vector/vector.hpp"
#define	GREEN "\033[0;32m"
#define	RED "\033[31m"

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


template    <typename T>
int    wrong_msg(const std::string &err, T ft, T std)
{
    std::cerr << RED << "[ KO" << err << ": (ft = " << ft << " and std = " << std << ")]" << RESET;
    return (-1);
}

template <typename T>
int    compare_vec(ft::vector<T> ft_vec, std::vector<T> std_vec)
{
    if (ft_vec.empty() != std_vec.empty())
        return (wrong_msg("Vectors Empty func different", ft_vec.empty(), std_vec.empty()));

    if (ft_vec.size() != std_vec.size())
        return (wrong_msg("Vectors Size is different", ft_vec.size(), std_vec.size()));

    if (ft_vec.capacity() != std_vec.capacity())
        return (wrong_msg("Vectors Capacity is different", ft_vec.capacity(), std_vec.capacity()));

    ft::vector<int>::iterator ft_it = ft_vec.begin();
    std::vector<int>::iterator std_it = std_vec.begin();

    for (; ft_it != ft_vec.end() && std_it != std_vec.end(); ft_it++, std_it++)
    {
        if (*ft_it != *std_it)
        {
            ft_it = ft_vec.begin();
            std::cout << "FT ELEMENTS: [ ";
            for (; ft_it != ft_vec.end(); ft_it++)
                std::cout << *ft_it << ", ";
            std::cout << "\\0 ]\n\n";

            std_it = std_vec.begin();
            std::cout << "STD ELEMENTS: [ ";
            for (; std_it != std_vec.end(); std_it++)
                std::cout << *std_it << ", ";
            std::cout << "\\0 ]\n\n";
            std::cerr << RED << "[ KO Vectors Elements are different ] " << RESET << std::endl;
            return (-1);
        }
    }
    std::cerr << GREEN << "[ OK ]" << RESET;
    return (0);
}


#endif
