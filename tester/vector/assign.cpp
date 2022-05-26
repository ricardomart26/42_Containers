#include "../inc.hpp"

// Replaces the contents of the container.
// 1) Replaces the contents with count copies of value value
// 2) Replaces the contents with copies of those in the range [first, last). The behavior is undefined if either argument is an iterator into *this.
// This overload has the same effect as overload (1) if InputIt is an integral type.
// 	(until C++11)
// This overload participates in overload resolution only if InputIt satisfies LegacyInputIterator.
// 	(since C++11)
// 3) Replaces the contents with the elements from the initializer list ilist.

// Complexity
// 1) Linear in count
// 2) Linear in distance between first and last
// 3) Linear in ilist.size()


// All iterators, pointers and references to the elements of the container are invalidated. The past-the-end iterator is also invalidated. 

// In the range version (1), the new contents are elements constructed from each of the elements in the range between first and last, in the same order.
// vectorname.assign(InputIterator first, InputIterator last)
// Parameters: 
// first - Input iterator to the initial position range.
// last - Input iterator to the final position range.


// In the fill version (2), the new contents are n elements, each initialized to a copy of val.
// vectorname.assign(int size, int value)
// Parameters: 
// size - number of values to be assigned
// value - value to be assigned to the vectorname

// If a reallocation happens,the storage needed is allocated using the internal allocator.

void	assign_test()
{
    std::cout << "Assign Range: ";
    std::cout << "\nAssign Fill: ";

	std::vector<int> std_vec(10);
	ft::vector<int> ft_vec(10);

	ft_vec.assign(ft_vec.size() + 5, 10);
	std_vec.assign(std_vec.size() + 5, 10);

	compare_vec(ft_vec, std_vec);
	print_vec_info(ft_vec);


	ft_vec.assign(ft_vec.begin() + 5, ft_vec.end());
	std_vec.assign(std_vec.begin() + 5, std_vec.end());

	compare_vec(ft_vec, std_vec);
	print_vec_info(ft_vec);

}
