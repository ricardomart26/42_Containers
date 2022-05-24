
#include "../inc.hpp"
#include <vector>

void	constructor_test()
{
    std::cout << "Constructor: ";
    compare_vec(ft::vector<int>(), std::vector<int>());
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

   std::cout << std::endl;
}

