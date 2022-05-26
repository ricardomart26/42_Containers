#include "../inc.hpp"

// Returns a reference to the first element in the container.
// Calling front on an empty container is undefined.

// Parameters
// (none)

// Return value
// reference to the first element

// Complexity
// Constant

// Notes
// For a container c, the expression c.front() is equivalent to *c.begin().

void	front_test()
{
	{
		std::vector<int> std_vec = random_vector_constructor<std::vector<int> >(100);
		ft::vector<int> ft_vec = random_vector_constructor<ft::vector<int> >(100);
		compare_vec(ft_vec, std_vec);    

		std::cout << "\nFront: ";
		if	(std_vec.front() == ft_vec.front())
			std::cout << GREEN << "[ OK ]" << RESET;
		else
			std::cout << RED << "[ KO ]" << RESET;
	}

	{
		std::vector<int> std_vec;
		ft::vector<int> ft_vec;

		std::cout << "\nFront empty vector: ";
		if	(std_vec.front() == ft_vec.front())
			std::cout << GREEN << "[ OK ]" << RESET;
		else
			std::cout << RED << "[ KO ]" << RESET;

	}

	{
		const std::vector<int> std_vec = random_vector_constructor<std::vector<int> >(100);
		const ft::vector<int> ft_vec = random_vector_constructor<ft::vector<int> >(100);;
		compare_vec(ft_vec, std_vec);

		std::cout << "\nFront const: Verificar se entra no const front";
		if	(std_vec.front() == ft_vec.front())
			std::cout << GREEN << "[ OK ]" << RESET;
		else
			std::cout << RED << "[ KO ]" << RESET;

	}
}
