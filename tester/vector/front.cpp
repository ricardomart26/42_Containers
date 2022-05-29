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
    std::cout << "||" << BLUE << std::string(52, '#') << RESET << "||\n";
    std::cout << "||" << BLUE << std::string(24, '#') << RESET << "Front" << BLUE << std::string(23, '#') << RESET << "||\n";
    std::cout << "||" << BLUE << std::string(52, '#') << RESET << "||\n";
    std::cout << std::endl << std::endl;
	{
		std::vector<int> std_vec = random_vector_constructor<std::vector<int> >(100);
		ft::vector<int> ft_vec = random_vector_constructor<ft::vector<int> >(100);

		std::cout << "Front: ";
		if	(std_vec.front() == ft_vec.front())
			std::cout << GREEN << "[ OK ]" << RESET;
		else
			std::cout << RED << "[ KO ]" << RESET;
	}

	{
		const std::vector<int> std_vec = random_vector_constructor<std::vector<int> >(100);
		const ft::vector<int> ft_vec = random_vector_constructor<ft::vector<int> >(100);;

		std::cout << "\nFront const: ";
		if	(std_vec.front() == ft_vec.front())
			std::cout << GREEN << "[ OK ]" << RESET;
		else
			std::cout << RED << "[ KO ]" << RESET;

	}
	std::cout << std::endl;
}
