#include "../inc.hpp"

void	insert_test()
{
    {
		std::vector<int> std_vec = random_vector_constructor<std::vector<int> >(100);
		ft::vector<int> ft_vec = random_vector_constructor<ft::vector<int> >(100);

		std::cout << "\nInsert Single element: ";

        ft_vec.insert(ft_vec.begin(), 4);
        std_vec.insert(std_vec.begin(), 4);
        compare_vec(ft_vec, std_vec);

        ft_vec.insert(ft_vec.end(), 4);
        std_vec.insert(std_vec.end(), 4);
        compare_vec(ft_vec, std_vec);


        ft_vec.insert(ft_vec.end() - 5, 4);
        std_vec.insert(std_vec.end() - 5, 4);
        compare_vec(ft_vec, std_vec);


	}

    // {
	// 	std::vector<int> std_vec = random_vector_constructor<std::vector<int> >(100);
	// 	ft::vector<int> ft_vec = random_vector_constructor<ft::vector<int> >(100);

	// 	std::cout << "\nInsert Single element: ";

    //     int arr[] = {3, 1, 42, 142, 2, 44, 4, 95, 90};
    //     ft_vec.insert()
	// }

    // {
	// 	std::vector<int> std_vec = random_vector_constructor<std::vector<int> >(100);
	// 	ft::vector<int> ft_vec = random_vector_constructor<ft::vector<int> >(100);

	// 	std::cout << "\nInsert Single element: ";

    //     int arr[] = {3, 1, 42, 142, 2, 44, 4, 95, 90};
    //     ft_vec.insert()
	// }

}
