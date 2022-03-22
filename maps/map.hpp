#ifndef MAP_HPP
#define MAP_HPP

#include <memory>
#include "pair.hpp"

namespace ft {

	// https://www.cplusplus.com/reference/functional/less/
	template <typename T>
	struct less {
		public:
			less();
	};

	template <typename key, typename T, 
	typename compare = less<key>, typename _allocator = std::allocator<ft::pair<const key, T> > >
	class map 
	{
		public:

			typedef value_type ft::pair<const key, T>;
			/**
			 *		Contructores
			*/

			//https://www.cplusplus.com/reference/map/map/map/
			map();
			explicit map(const compare &comp = compare(),
			const _allocator &alloc = allocator_type());
			template <typename InputIterator>
			map(InputIterator first, InputIterator last,
			const compare & comp = compare(),
			const _allocator &alloc = allocator_type());
			map(const map &x);

			// https://www.cplusplus.com/reference/map/map/~map/
			~map();

			// https://www.cplusplus.com/reference/map/map/operator=/
			map	&operator=(const map &x);

			/**
			 *		iterators
			 */
			
			// https://www.cplusplus.com/reference/map/map/begin/
			iterator begin();
			const_iterator begin() const;

			// https://www.cplusplus.com/reference/map/map/end/
			iterator end();
			const_iterator end() const;

			// https://www.cplusplus.com/reference/map/map/rbegin/
			reverse_iterator rbegin();
			const_reverse_iterator rbegin() const;

			// https://www.cplusplus.com/reference/map/map/rend/
			reverse_iterator rend();
			const_reverse_iterator rend() const;

			/**
			 *		Capacity
			 */

			// https://www.cplusplus.com/reference/map/map/empty/
			bool	empty() const;

			// https://www.cplusplus.com/reference/map/map/size/
			size_t	size() const;

			// https://www.cplusplus.com/reference/map/map/max_size/
			size_t	max_size() const;

			/**
			 *		Element Acess
			 */
			
			// https://www.cplusplus.com/reference/map/map/operator[]/
			T	&operator[](const key &k);

			/**
			 *		Modifiers
			 */
			
			// https://www.cplusplus.com/reference/map/map/insert/
			ft::pair<iterator, bool>	insert(const value_type &val);
			iterator	insert(iterator position, const value_type &val);
			template <typename InputIterator>
			void	insert(InputIterator first, InputIterator last);

			// https://www.cplusplus.com/reference/map/map/erase/
			void	erase(iterator position);
			size_t	erase(const key &k);
			void	erase(iterator first, iterator last);

			// https://www.cplusplus.com/reference/map/map/swap/
			void	swap(map &x);

			// https://www.cplusplus.com/reference/map/map/clear/
			void	clear();

			/**
			 *		Observer
			 */
			
			// https://www.cplusplus.com/reference/map/map/key_comp/
			compare key_comp() const;

			// https://www.cplusplus.com/reference/map/map/value_comp/
			// Ainda nao consigo fazer o prototipo para este

			/**
			 *		Operations
			 */

			// https://www.cplusplus.com/reference/map/map/find/
			iterator	find(const key &k);
			const_iterator	find(const key &k) const;

			// https://www.cplusplus.com/reference/map/map/count/
			size_t	count(const key &k) const;

			// https://www.cplusplus.com/reference/map/map/lower_bound/
			iterator lower_bound(const key &k);
			const_iterator lower_bound(const key &k) const;

			// https://www.cplusplus.com/reference/map/map/upper_bound/
			iterator upper_bound(const key &k);
			const_iterator upper_bound(const key &k) const;

			// https://www.cplusplus.com/reference/map/map/equal_range/
			pair<const_iterator, const_iterator> equal_range(const key &k) const;
			pair<iterator, iterator> equal_range(const key &k);

			/**
			 *		Allocator
			 */

			_allocator get_allocator() const;
	};
}


#endif
