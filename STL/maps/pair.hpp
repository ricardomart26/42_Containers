#ifndef PAIR_HPP
#define PAIR_HPP

#include <iostream>
#include "../utils/type_traits.hpp"
#include "map.hpp"
#include <string>

namespace ft 
{
	template <typename T1, typename T2>
	struct pair
	{
		/**
		 *		Constructores
		 */
		typedef T1	first_type;
		typedef T2	second_type;

		pair() : first(), second() {}

		template <class U, class V>
		pair(const pair<U,V> &obj) : first(obj.first), second(obj.second) {}
        
		pair(const first_type &arg1, const second_type &arg2) : first(arg1), second(arg2) {}
		
		pair &operator=(const pair& rhs) 
		{
			if (this != &rhs)
			{
				first = rhs.first;
				second = rhs.second;
			}
			return (*this);
		}

		/**
		 *		Relational operators
		 */

		friend	bool	operator==(const pair &lhs, const pair &rhs)
		{ return (lhs.first == rhs.first && lhs.second == rhs.second); }
		friend	bool	operator!=(const pair &lhs, const pair &rhs)
		{ return (lhs.first != rhs.first || lhs.second != rhs.second); }

		friend	bool	operator<(const pair &lhs, const pair &rhs)
		{ return (lhs.first < rhs.first || (rhs.first == lhs.first && lhs.second < rhs.second)); }
		friend	bool	operator<=(const pair &lhs, const pair &rhs) { return !(rhs<lhs); }
		friend	bool	operator>(const pair &lhs, const pair &rhs) { return (rhs<lhs); }
		
		friend	bool	operator>=(const pair &lhs, const pair &rhs) { return !(lhs < rhs); }

		first_type first;
		second_type second;
	};
	
	template <typename T1, typename T2>
	pair<T1, T2>	make_pair(T1 x, T2 y) { return (pair<T1, T2>(x, y)); }

};
#endif
