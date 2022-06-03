
#include "../inc.hpp"

void	constructor_test()
{
    std::cout << "||" << BLUE << std::string(52, '#') << RESET << "||\n";
    std::cout << "||" << BLUE << std::string(21, '#') << RESET << "Constructor" << BLUE << std::string(20, '#') << RESET << "||\n";
    std::cout << "||" << BLUE << std::string(52, '#') << RESET << "||\n";
    std::cout << std::endl;

    std::cout << "Default Constructor: ";
    if (compare_vec(ft::vector<int>(), std::vector<int>()))
        std::cout << GREEN << " [ OK ] " << RESET;

    std::cout << "\nFill Constructor: ";
    if (compare_vec(ft::vector<int>(10), std::vector<int>(10)))
		std::cout << GREEN << " [ OK ] " << RESET;

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
    if (compare_vec(ft::vector<int>(10, 2), std::vector<int>(10, 2)))
        std::cout << GREEN << " [ OK ] " << RESET;
    if (compare_vec(ft::vector<int>(10, -1), std::vector<int>(10, -1)))
        std::cout << GREEN << " [ OK ] " << RESET;
    if (compare_vec(ft::vector<int>(0, 3), std::vector<int>(0, 3)))
        std::cout << GREEN << " [ OK ] " << RESET;

    std::cout << "\nRange Constructor: ";

    int arr[] = {1, 2, 5, 1, 2, 6, 3, 2};
    if (compare_vec(ft::vector<int>(arr + 0, arr + 4), std::vector<int>(arr + 0, arr + 4)))
        std::cout << GREEN << " [ OK ] " << RESET;
    if (compare_vec(ft::vector<int>(arr + 0, arr + 8), std::vector<int>(arr + 0, arr + 8)))
        std::cout << GREEN << " [ OK ] " << RESET;

    std::cout << "\nCopy Constructor: ";
    {
        std::vector<int> std_vec;
        ft::vector<int> ft_vec;

        std::vector<int> std_vec_cp(std_vec);
        ft::vector<int> ft_vec_cp(ft_vec);

        if (compare_vec(ft_vec_cp, std_vec_cp) && compare_vec_ref(ft_vec_cp, std_vec_cp))
            std::cout << GREEN << " [ OK ] " << RESET;

    }
    
    {
        std::vector<int> std_vec(MID);
        ft::vector<int> ft_vec(MID);

        std::vector<int> std_vec_cp(std_vec);
        ft::vector<int> ft_vec_cp(ft_vec);

        if (compare_vec(ft_vec_cp, std_vec_cp) && compare_vec_ref(ft_vec_cp, std_vec_cp))
            std::cout << GREEN << " [ OK ] " << RESET;
    }
    
    
    {
        std::vector<int> std_vec(MID, 4);
        ft::vector<int> ft_vec(MID, 4);

        std::vector<int> std_vec_cp(std_vec);
        ft::vector<int> ft_vec_cp(ft_vec);

        if (compare_vec(ft_vec_cp, std_vec_cp) && compare_vec_ref(ft_vec_cp, std_vec_cp))
            std::cout << GREEN << " [ OK ] " << RESET;
    }
    

	std::cout << std::endl << std::endl;

}

