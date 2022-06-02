#include "../inc.hpp"

// Erases all elements from the container. After this call, size() returns zero.
// Invalidates any references, pointers, or iterators referring to contained elements. Any past-the-end iterators are also invalidated.  
// Leaves the capacity() of the vector unchanged (note: the standard's restriction on the changes to capacity is in the specification of vector::reserve, see [1])

// Parameters
// (none)

// Return value
// (none)

// Complexity
// Linear in the size of the container, i.e., the number of elements.

void	clear_test()
{
	std::cout << std::endl << std::endl;
	std::cout << "||" << BLUE << std::string(52, '#') << RESET << "||\n";
    std::cout << "||" << BLUE << std::string(24, '#') << RESET << "Clear" << BLUE << std::string(24, '#') << RESET << "||\n";
    std::cout << "||" << BLUE << std::string(52, '#') << RESET << "||\n";

    {
        std::cout << "Emtpy vector: ";
        std::vector<int> std_vec;
        ft::vector<int> ft_vec;

        ft_vec.clear();
        std_vec.clear();
        compare_vec(ft_vec, std_vec);

    }

    {
        std::cout << "Normal vector: ";

        std::vector<int> std_vec(LOW);
        ft::vector<int> ft_vec(LOW);

        ft_vec.clear();
        std_vec.clear();
        compare_vec(ft_vec, std_vec);

    }

    {
        std::vector<int> std_vec(MID);
        ft::vector<int> ft_vec(MID);

        ft_vec.clear();
        std_vec.clear();
        compare_vec(ft_vec, std_vec);

    }

    {
        std::vector<int> std_vec(HIGH);
        ft::vector<int> ft_vec(HIGH);

        std_vec.push_back(20);
        ft_vec.push_back(20);

        ft_vec.clear();
        std_vec.clear();
        compare_vec(ft_vec, std_vec);

    }

    {
        std::vector<int> std_vec(HIGH);
        ft::vector<int> ft_vec;

        int arr[] = {3, 43, 423, 42, 34, 34, 234, 34};
        ft_vec.insert(ft_vec.begin(), arr + 0, arr + 7);

        ft_vec.clear();
        std_vec.clear();
        compare_vec(ft_vec, std_vec);
    }

	std::cout << std::endl << std::endl;

}
