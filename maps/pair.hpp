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

		pair() : _first(), _second() {}
        pair(const T1 &arg1, const T2 &arg2) : _first(arg1), _second(arg2) {}

		template <class U, class V>
		pair(const pair<U,V> &obj);
		
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
    
		private:
			T1 _first;
			T2 _second;
	};
};

#endif
