#include "../inc.hpp"

void	pop_back_test()
{
    std::cout << "||" << BLUE << std::string(52, '#') << RESET << "||\n";
    std::cout << "||" << BLUE << std::string(20, '#') << RESET << "Pop Back" << BLUE << std::string(20, '#') << RESET << "||\n";
    std::cout << "||" << BLUE << std::string(52, '#') << RESET << "||\n";
    std::cout << std::endl << std::endl;

    std::cout << "Pop empty vec: ";

    std::vector<int> std_vec;
    ft::vector<int> ft_vec;

    std_vec.pop_back();
    ft_vec.pop_back();
   	if (compare_vec(ft_vec, std_vec) && compare_vec_ref(ft_vec, std_vec))
		std::cout << GREEN << " [ OK ] " << RESET;;


    std::cout << "Pop full vec: ";

    for (size_t i = 0; i < MID; i++)
    {
        ft_vec.push_back(i);
        std_vec.push_back(i);
    }

    std_vec.pop_back();
    ft_vec.pop_back();
   	if (compare_vec(ft_vec, std_vec) && compare_vec_ref(ft_vec, std_vec))
		std::cout << GREEN << " [ OK ] " << RESET;;

    {

        std::vector<int> std_vec;
        ft::vector<int> ft_vec;

        std::cout << "Pop full vec: ";

        for (size_t i = 0; i < HIGH; i++)
        {
            ft_vec.push_back(i);
            std_vec.push_back(i);
        }

        std_vec.pop_back();
        ft_vec.pop_back();
       	if (compare_vec(ft_vec, std_vec) && compare_vec_ref(ft_vec, std_vec))
		    std::cout << GREEN << " [ OK ] " << RESET;;

    }

    std::cout << "Pop full vec: ";

    for (size_t i = 0; i < MID; i++)
    {
        ft_vec.pop_back();
        std_vec.pop_back();
    }

   	if (compare_vec(ft_vec, std_vec) && compare_vec_ref(ft_vec, std_vec))
		std::cout << GREEN << " [ OK ] " << RESET;;


}
