
#include "../inc.hpp"

void	constructor_test()
{
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

    std::cout << "\nCopy Constructor: ";

    std::cout << "\nConstruct with max size: ";




   std::cout << std::endl;
}

