#include "../inc.hpp"

// O capacity muda quando e usado o copy constructor
void	push_back_test()
{
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
    
    compare_vec(ft_vecA, std_vecA);

    for (int i = 0; i < MID; i++)
    {
        ft_vecB.push_back(i);
        std_vecB.push_back(i);
    }

    compare_vec(ft_vecB, std_vecB);

    std_vecB.push_back(420);
    ft_vecB.push_back(420);
    compare_vec(ft_vecB, std_vecB);

    for (int i = 0; i < HIGH; i++)
    {
        ft_vecC.push_back(i);
        std_vecC.push_back(i);
    }

    compare_vec(ft_vecC, std_vecC);

    for (int i = 0; i < CRAZY_HIGH; i++)
    {
        ft_vecD.push_back(i);
        std_vecD.push_back(i);
    }

    compare_vec(ft_vecD, std_vecD);
    
    std::cout << std::endl;
}
