#include "../inc.hpp"

// O capacity muda quando e usado o copy constructor
void	resize_test()
{
    std::cout << "||" << BLUE << std::string(52, '#') << RESET << "||\n";
    std::cout << "||" << BLUE << std::string(23, '#') << RESET << "Resize" << BLUE << std::string(23, '#') << RESET << "||\n";
    std::cout << "||" << BLUE << std::string(52, '#') << RESET << "||\n";
    std::cout << std::endl;

    {
        std::cout << "Resize empty vector: ";
        ft::vector<int> ft_vec(0);
        std::vector<int> std_vec(0);

        ft_vec.resize(10, 2);
        std_vec.resize(10, 2);

        // ft::vector<int> ft_vecB(0);
        std::vector<int> std_vecB(0);

        // ft_vecB.resize(0, 2);
        std_vecB.resize(0, 2);

        // compare_vec(ft_vecB, std_vecB);

    }

        
    {
        std::cout << "\nResize to same size: ";
        ft::vector<int> ft_vec(10, 4);
        std::vector<int> std_vec(10, 4);

        ft_vec.resize(10, 2);
        std_vec.resize(10, 2);
        if (compare_vec(ft_vec, std_vec) && compare_vec_ref(ft_vec, std_vec))
            std::cout << GREEN << " [ OK ] " << RESET;
    }

    {

        ft::vector<int> ft_vec(10, 4);
        std::vector<int> std_vec(10, 4);

        ft_vec.resize(ft_vec.size() - 10);
        std_vec.resize(std_vec.size() - 10);
        print_vec_info(std_vec);
        compare_vec_ref(ft_vec, std_vec);
        //	if (compare_vec(ft_vec, std_vec) && compare_vec_ref(ft_vec, std_vec))
		std::cout << GREEN << " [ OK ] " << RESET;;

        ft_vec.resize(ft_vec.size() + 10);
        std_vec.resize(std_vec.size() + 10);
       	if (compare_vec(ft_vec, std_vec) && compare_vec_ref(ft_vec, std_vec))
		std::cout << GREEN << " [ OK ] " << RESET;;
        compare_vec_ref(ft_vec, std_vec);
        
        ft_vec.resize(ft_vec.size());
        std_vec.resize(std_vec.size());
       	if (compare_vec(ft_vec, std_vec) && compare_vec_ref(ft_vec, std_vec))
		std::cout << GREEN << " [ OK ] " << RESET;;
        
        ft_vec.resize(ft_vec.size(), 10);
        std_vec.resize(std_vec.size(), 10);
       	if (compare_vec(ft_vec, std_vec) && compare_vec_ref(ft_vec, std_vec))
		std::cout << GREEN << " [ OK ] " << RESET;;
        
        ft_vec.resize(ft_vec.size() + 5, 10);
        std_vec.resize(std_vec.size() + 5, 10);
       	if (compare_vec(ft_vec, std_vec) && compare_vec_ref(ft_vec, std_vec))
		std::cout << GREEN << " [ OK ] " << RESET;;

    }


    {
        std::cout << "\n\bResize lower size: ";
        ft::vector<int> ft_vec(10);
        std::vector<int> std_vec(10);

        ft_vec.resize(2, 2);
        std_vec.resize(2, 2);
       	if (compare_vec(ft_vec, std_vec) && compare_vec_ref(ft_vec, std_vec))
		std::cout << GREEN << " [ OK ] " << RESET;;

    }

    
    std::cout << std::endl << std::endl;
}
