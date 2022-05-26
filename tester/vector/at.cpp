#include "../inc.hpp"

// Returns a reference to the element at specified location pos, with bounds checking.
// If pos is not within the range of the container, an exception of type std::out_of_range is thrown.

// Parameters
// pos 	- 	position of the element to return

// Return value
// Reference to the requested element.

// Exceptions
// std::out_of_range if !(pos < size()).

// Complexity
// Constant. 

void	at_test()
{
	std::vector<int> std_vec = random_vector_constructor<std::vector<int> >(100);
	ft::vector<int> ft_vec = random_vector_constructor<ft::vector<int> >(100);
	compare_vec(ft_vec, std_vec);

    std::cout << "\nAt: ";
	if	(std_vec.at(std_vec.size() - 1) == ft_vec.at(ft_vec.size() - 1))
		std::cout << GREEN << "[ OK ]" << RESET;
	else
		std::cout << RED << "[ KO ]" << RESET;

	
	if	(std_vec.at(0) == ft_vec.at(0))
		std::cout << GREEN << "[ OK ]" << RESET;
	else
		std::cout << RED << "[ KO ]" << RESET;

	if	(std_vec.at(std_vec.size()) == ft_vec.at(ft_vec.size()))
		std::cout << GREEN << "[ OK ]" << RESET;
	else
		std::cout << RED << "[ KO ]" << RESET;

	try {
		ft_vec.at(ft_vec.size() + 1);
		std::cout << RED << "[ KO ]" << RESET;
	} catch (const std::exception &e) {
		std::cout << e.what();
		std::cout << GREEN << "[ OK ]" << RESET;
	}

}
