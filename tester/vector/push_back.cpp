#include "../inc.hpp"

// O capacity muda quando e usado o copy constructor
void	push_back_test()
{
    std::cout << "||" << BLUE << std::string(52, '#') << RESET << "||\n";
    std::cout << "||" << BLUE << std::string(22, '#') << RESET << "Push Back" << BLUE << std::string(21, '#') << RESET << "||\n";
    std::cout << "||" << BLUE << std::string(52, '#') << RESET << "||\n";
    std::cout << std::endl;

    std::cout << "Push back: ";

    ft::vector<int> ft_vecA(10);
    ft::vector<int> ft_vecB(0);
    ft::vector<int> ft_vecC(1000);
    ft::vector<int> ft_vecD(1000);
    
    std::vector<int> std_vecA(10);
    std::vector<int> std_vecB(0);
    std::vector<int> std_vecC(1000);
    std::vector<int> std_vecD(1000);


    for (int i = 0; i < LOW; i++)
    {
        ft_vecA.push_back(i);
        std_vecA.push_back(i);
    }
    
    if (compare_vec(ft_vecA, std_vecA) && compare_vec_ref(ft_vecA, std_vecA))
		std::cout << GREEN << " [ OK ] " << RESET;

    for (int i = 0; i < MID; i++)
    {
        ft_vecB.push_back(i);
        std_vecB.push_back(i);
    }

    if (compare_vec(ft_vecB, std_vecB) && compare_vec_ref(ft_vecB, std_vecB))
		std::cout << GREEN << " [ OK ] " << RESET;

    std_vecB.push_back(420);
    ft_vecB.push_back(420);
    if (compare_vec(ft_vecB, std_vecB) && compare_vec_ref(ft_vecB, std_vecB))
		std::cout << GREEN << " [ OK ] " << RESET;

    for (int i = 0; i < HIGH; i++)
    {
        ft_vecC.push_back(i);
        std_vecC.push_back(i);
    }

    if (compare_vec(ft_vecC, std_vecC) && compare_vec_ref(ft_vecC, std_vecC))
		std::cout << GREEN << " [ OK ] " << RESET;

    for (int i = 0; i < CRAZY_HIGH; i++)
    {
        ft_vecD.push_back(i);
        std_vecD.push_back(i);
    }

    if (compare_vec(ft_vecD, std_vecD) && compare_vec_ref(ft_vecD, std_vecD))
		std::cout << GREEN << " [ OK ] " << RESET;
    
    std::cout << std::endl;
}
