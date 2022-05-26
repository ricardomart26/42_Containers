#include "../inc.hpp"

// Inserts elements at the specified location in the container.
// 1-2) inserts value before pos
// 3) inserts count copies of the value before pos
// 4) inserts elements from range [first, last) before pos.
// This overload has the same effect as overload (3) if InputIt is an integral type.
// 	(until C++11)
// This overload participates in overload resolution only if InputIt qualifies as LegacyInputIterator, to avoid ambiguity with the overload (3).
// 	(since C++11)
// The behavior is undefined if first and last are iterators into *this.
// 5) inserts elements from initializer list ilist before pos.
// Causes reallocation if the new size() is greater than the old capacity(). If the new size() is greater than capacity(), all iterators and references are invalidated. Otherwise, only the iterators and references before the insertion point remain valid. The past-the-end iterator is also invalidated.

// Parameters
// pos 	- 	iterator before which the content will be inserted. pos may be the end() iterator
// value 	- 	element value to insert
// count 	- 	number of elements to insert
// first, last 	- 	the range of elements to insert, can't be iterators into container for which insert is called
// ilist 	- 	initializer list to insert the values from

// Type requirements
// - T must meet the requirements of CopyAssignable and CopyInsertable in order to use overload (1).
// - T must meet the requirements of MoveAssignable and MoveInsertable in order to use overload (2).
// - T must meet the requirements of CopyAssignable and CopyInsertable in order to use overload (3).
// - T must meet the requirements of EmplaceConstructible in order to use overload (4,5).
// - T must meet the requirements of MoveAssignable and MoveInsertable in order to use overload (4). required only if InputIt satisfies LegacyInputIterator but not LegacyForwardIterator. (until C++17)
// - T must meet the requirements of Swappable, MoveAssignable, MoveConstructible and MoveInsertable in order to use overload (4,5). (since C++17)

// Return value
// 1-2) Iterator pointing to the inserted value
// 3) Iterator pointing to the first element inserted, or pos if count==0.
// 4) Iterator pointing to the first element inserted, or pos if first==last.
// 5) Iterator pointing to the first element inserted, or pos if ilist is empty.
// Complexity
// 1-2) Constant plus linear in the distance between pos and end of the container.
// 3) Linear in count plus linear in the distance between pos and end of the container.
// 4) Linear in std::distance(first, last) plus linear in the distance between pos and end of the container.
// 5) Linear in ilist.size() plus linear in the distance between pos and end of the container.

// Exceptions
// If an exception is thrown when inserting a single element at the end, and T is CopyInsertable or 
// std::is_nothrow_move_constructible<T>::value is true, there are no effects (strong exception guarantee). 


void	insert_test()
{
    std::cout << std::endl;
    {
		std::vector<int> std_vec = random_vector_constructor<std::vector<int> >(100);
		ft::vector<int> ft_vec = random_vector_constructor<ft::vector<int> >(100);

		std::cout << "Insert Single element: ";

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

    {
		std::vector<int> std_vec = random_vector_constructor<std::vector<int> >(100);
		ft::vector<int> ft_vec = random_vector_constructor<ft::vector<int> >(100);

		std::cout << "\nInsert Fill: ";


        ft_vec.insert(ft_vec.begin(), 4, 123);
        std_vec.insert(std_vec.begin(), 4, 123);
        compare_vec(ft_vec, std_vec);

        ft_vec.insert(ft_vec.begin(), 0, 123);
        std_vec.insert(std_vec.begin(), 0, 123);
        compare_vec(ft_vec, std_vec);

        ft_vec.insert(ft_vec.end(), 4, 123);
        std_vec.insert(std_vec.end(), 4, 123);
        compare_vec(ft_vec, std_vec);


        ft_vec.insert(ft_vec.end() - 5, 4, 123);
        std_vec.insert(std_vec.end() - 5, 4, 123);
        compare_vec(ft_vec, std_vec);

	}

    {
		std::vector<int> std_vec = random_vector_constructor<std::vector<int> >(100);
		ft::vector<int> ft_vec = random_vector_constructor<ft::vector<int> >(100);
		std::cout << "\nInsert Range: ";

        int arr[9] = {3, 1, 42, 142, 2, 44, 4, 95, 90};

        ft_vec.insert(ft_vec.begin(), arr + 0, arr + 5);
        std_vec.insert(std_vec.begin(), arr + 0, arr + 5);
        compare_vec(ft_vec, std_vec);

        ft_vec.insert(ft_vec.end(), arr + 0, arr + 5);
        std_vec.insert(std_vec.end(), arr + 0, arr + 5);
        compare_vec(ft_vec, std_vec);

        ft_vec.insert(ft_vec.end() - 5, arr + 0, arr + 5);
        std_vec.insert(std_vec.end() - 5, arr + 0, arr + 5);
        compare_vec(ft_vec, std_vec);

        ft_vec.insert(ft_vec.begin() + 2, arr + 5, arr + 7);
        std_vec.insert(std_vec.begin() + 2, arr + 5, arr + 7);
        compare_vec(ft_vec, std_vec);

	}
    std::cout << std::endl << std::endl;


}
