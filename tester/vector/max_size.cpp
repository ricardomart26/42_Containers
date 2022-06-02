#include "../inc.hpp"

void	max_size_test()
{
    std::cout << "||" << BLUE << std::string(52, '#') << RESET << "||\n";
    std::cout << "||" << BLUE << std::string(22, '#') << RESET << "Max size" << BLUE << std::string(22, '#') << RESET << "||\n";
    std::cout << "||" << BLUE << std::string(52, '#') << RESET << "||\n";
    std::cout << std::endl;

    ft::vector<int> ft_vec(10);
    ft::vector<int> std_vec(10);

    std::cout << "Max size:";

    if (ft_vec.max_size() == std_vec.max_size())
        std::cout << GREEN << " [ OK ] " << RESET;
    else
        std::cout << RED << " [ KO ft: " << ft_vec.max_size() << " std: " << std_vec.max_size() << " ] " << RESET;
    
    std::cout << std::endl << std::endl;

}

