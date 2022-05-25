#include "../inc.hpp"

// O capacity muda quando e usado o copy constructor
void	resize_test()
{
    {
        std::cout << "Resize empty vector: ";
        ft::vector<int> ft_vec(0);
        std::vector<int> std_vec(0);

        ft_vec.resize(10, 2);
        std_vec.resize(10, 2);

        ft::vector<int> ft_vecB(0);
        std::vector<int> std_vecB(0);
        ft_vecB.resize(0, 2);
        std_vecB.resize(0, 2);
        // print_vec_info(std_vecB);
        compare_vec(ft_vecB, std_vecB);

    }

        
    {
        std::cout << "\nResize to same size: ";
        ft::vector<int> ft_vec(10, 4);
        std::vector<int> std_vec(10, 4);

        ft_vec.resize(10, 2);
        std_vec.resize(10, 2);
        compare_vec(ft_vec, std_vec);
    }


    // {
    //     std::cout << "Resize bigger than max_size: ";
    //     try {
    //         ft::vector<int> ft_vec(10, 4);
    //         ft_vec.resize(ft_vec.max_size(), 2);
    //     } catch (const std::exception &e) {
    //         std::cout << GREEN << " [ OK ] " << RESET;
    //     }
    //     try {
    //         std::vector<int> std_vec(10, 4);
    //         std_vec.resize(std_vec.max_size(), 2);
    //     } catch (const std::exception &e) {
    //         std::cout << GREEN << " STD [ OK ] " << RESET;
    //     }
    // }


    {
        std::cout << "\n\bResize lower size: ";
        ft::vector<int> ft_vec(10);
        std::vector<int> std_vec(10);

        ft_vec.resize(2, 2);
        std_vec.resize(2, 2);
        compare_vec(ft_vec, std_vec);

    }

    // ft::vector<int> ft_vecA(10);
    // ft::vector<int> ft_vecC(1000);
    // ft::vector<int> ft_vecD(1000);
    
    // std::vector<int> std_vecB(0);
    // std::vector<int> std_vecC(1000);
    // std::vector<int> std_vecD(1000);


    // for (int i = 0; i < LOW; i++)
    // {
    //     ft_vecA.push_back(i);
    //     std_vecA.push_back(i);
    // }
    
    // compare_vec(ft_vecA, std_vecA);

    // for (int i = 0; i < MID; i++)
    // {
    //     ft_vecB.push_back(i);
    //     std_vecB.push_back(i);
    // }

    // compare_vec(ft_vecB, std_vecB);

    // std_vecB.push_back(420);
    // ft_vecB.push_back(420);
    // compare_vec(ft_vecB, std_vecB);

    // for (int i = 0; i < HIGH; i++)
    // {
    //     ft_vecC.push_back(i);
    //     std_vecC.push_back(i);
    // }

    // compare_vec(ft_vecC, std_vecC);

    // for (int i = 0; i < CRAZY_HIGH; i++)
    // {
    //     ft_vecD.push_back(i);
    //     std_vecD.push_back(i);
    // }

    // compare_vec(ft_vecD, std_vecD);
    
    std::cout << std::endl;
}
