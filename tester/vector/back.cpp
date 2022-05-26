#include "../inc.hpp"

// Returns a reference to the last element in the container.
// Calling back on an empty container causes undefined behavior.

// Parameters
// (none)

// Return value
// Reference to the last element.

// Complexity
// Constant.

// Notes
// For a non-empty container c, the expression c.back() is equivalent to *std::prev(c.end()) 

void	back_test()
{
	{
		std::vector<int> std_vec = random_vector_constructor<std::vector<int> >(100);
		ft::vector<int> ft_vec = random_vector_constructor<ft::vector<int> >(100);

		std::cout << "\nBack: ";
		if	(std_vec.back() == ft_vec.back())
			std::cout << GREEN << "[ OK ]" << RESET;
		else
			std::cout << RED << "[ KO ]" << RESET;
	}

	{
		const std::vector<int> std_vec = random_vector_constructor<std::vector<int> >(100);
		const ft::vector<int> ft_vec = random_vector_constructor<ft::vector<int> >(100);;
		std::cout << "\nBack const: ";
		if	(std_vec.back() == ft_vec.back())
			std::cout << GREEN << "[ OK ]" << RESET;
		else
			std::cout << RED << "[ KO ]" << RESET;

	}
	std::cout << std::endl;
}
