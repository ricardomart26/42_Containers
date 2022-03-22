#ifndef PAIR_HPP
#define PAIR_HPP

namespace ft 
{
	template <typename T1, typename T2>
	struct pair
	{
		/**
		 *		Constructores
		 */

		pair();
		template <class U, class V>
		pair(const pair<U,V> &obj);
		pair(const T1 &a, const T2 &b);
		
		pair	&operator=(const pair &obj);

		
		/**
		 *		Relational operators
		 */

		bool	operator==(const pair &lhs, const pair &rhs);
		bool	operator!=(const pair &lhs, const pair &rhs);
		bool	operator<(const pair &lhs, const pair &rhs);
		bool	operator<=(const pair &lhs, const pair &rhs);
		bool	operator>(const pair &lhs, const pair &rhs);
		bool	operator>=(const pair &lhs, const pair &rhs);

	};
};

#endif
