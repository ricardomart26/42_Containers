
#include "../inc.hpp"

void	constructor_test()
{
    std::cout << "||" << BLUE << std::string(52, '#') << RESET << "||\n";
    std::cout << "||" << BLUE << std::string(21, '#') << RESET << "Constructor" << BLUE << std::string(20, '#') << RESET << "||\n";
    std::cout << "||" << BLUE << std::string(52, '#') << RESET << "||\n";
    std::cout << std::endl << std::endl;

    std::cout << "Default Constructor: ";
    compare_vec(ft::vector<int>(), std::vector<int>());

    std::cout << "\nFill Constructor: ";
    compare_vec(ft::vector<int>(10), std::vector<int>(10));
    compare_vec(ft::vector<int>(0), std::vector<int>(0));
    {
        try {
            ft::vector<int> vecC(-10);
        } catch (const std::exception &e) {
            e.what();
        }
        try {
            std::vector<int> vecC(-10);
        } catch (const std::exception &e) {
            e.what();
        }
    }
    compare_vec(ft::vector<int>(10, 2), std::vector<int>(10, 2));
    compare_vec(ft::vector<int>(10, -1), std::vector<int>(10, -1));
    compare_vec(ft::vector<int>(0, 3), std::vector<int>(0, 3));

    std::cout << "\nRange Constructor: ";

    int arr[] = {1, 2, 5, 1, 2, 6, 3, 2};
    compare_vec(ft::vector<int>(arr + 0, arr + 4), std::vector<int>(arr + 0, arr + 4));
    compare_vec(ft::vector<int>(arr + 0, arr + 8), std::vector<int>(arr + 0, arr + 8));

    std::cout << "\nCopy Constructor: ";
    {
        std::vector<int> std_vec;
        ft::vector<int> ft_vec;

        std::vector<int> std_vec_cp(std_vec);
        ft::vector<int> ft_vec_cp(ft_vec);

        compare_vec(ft_vec_cp, std_vec_cp);
    }
    
    {
        std::vector<int> std_vec(MID);
        ft::vector<int> ft_vec(MID);

        std::vector<int> std_vec_cp(std_vec);
        ft::vector<int> ft_vec_cp(ft_vec);

        compare_vec(ft_vec_cp, std_vec_cp);
    }
    
    
    {
        std::vector<int> std_vec(MID, 4);
        ft::vector<int> ft_vec(MID, 4);

        std::vector<int> std_vec_cp(std_vec);
        ft::vector<int> ft_vec_cp(ft_vec);

        compare_vec(ft_vec_cp, std_vec_cp);
    }
    

    std::cout << std::endl;
}

