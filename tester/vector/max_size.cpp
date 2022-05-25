#include "../inc.hpp"

void	max_size_test()
{
    ft::vector<int> ft_vec(10);
    ft::vector<int> std_vec(10);

    std::cout << "Max size:";

    if (ft_vec.max_size() == std_vec.max_size())
        std::cout << GREEN << " [ OK ] " << RESET;
    else
        std::cout << RED << " [ KO ft: " << ft_vec.max_size() << " std: " << std_vec.max_size() << " ] " << RESET;
    
    std::cout << std::endl;

}

