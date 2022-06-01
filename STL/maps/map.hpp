#ifndef MAP_HPP
#define MAP_HPP

#include <memory>
#include "pair.hpp"
#include "../vector/random_access_it.hpp"
#include "../vector/reverse_iterator.hpp"
#include "../utils/type_traits.hpp"
#include "binary_search_tree.hpp"
#include "map_iterator.hpp"
#include "map_reverse_it.hpp"

namespace ft {

	// https://www.cplusplus.com/reference/functional/less/
	template <typename T>
	struct less {
		public:
			bool	operator()(const T& x, const T& y) const {return (x < y);};
	};

	template <typename key, typename T, 
	typename compare = less<key>, typename allocator = std::allocator<ft::pair<const key, T> > >
	class map
	{
		public:

			typedef map_iterator<map <key, T> >					iterator;
			typedef map_iterator<map <const key, T> > 			const_iterator;
			typedef map_reverse_iterator<map <key, T> >			reverse_iterator;
			// // typedef reverse_iterator <map <const key, T> >		const_reverse_iterator;
			typedef	key											key_type;
			typedef T 											mapped_type;
			typedef ft::pair<const key_type, mapped_type>		value_type;
			typedef compare										value_compare;
			typedef	std::allocator_traits<value_type>			alloc_traits;
			typedef	std::allocator<value_type>					allocator_type;
			typedef typename allocator_type::reference			reference;
			typedef typename allocator_type::const_reference	const_reference;
			typedef typename allocator_type::pointer			pointer;
			typedef typename allocator_type::const_pointer		const_pointer;
			typedef typename allocator_type::difference_type	difference_type;
		
			/**
			 *		Contructores
			*/

			//https://www.cplusplus.com/reference/map/map/map/
			// map();
			explicit map(const compare &comp = compare(), const allocator &alloc = allocator_type())
			: _size(0), _alloc(alloc), _tree(comp) {}
	
			template <typename InputIterator>
			map(InputIterator first, InputIterator last,
			const compare &comp = compare(),
			const allocator &alloc = allocator_type());

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
			// const_reverse_iterator rbegin() const;

			// https://www.cplusplus.com/reference/map/map/rend/
			reverse_iterator rend();
			// const_reverse_iterator rend() const;

			/**
			 *		Capacity
			 */

			// https://www.cplusplus.com/reference/map/map/empty/
			bool	empty() const {return (_size == 0);};

			// https://www.cplusplus.com/reference/map/map/size/
			size_t	size() const {return (_size);};

			// https://www.cplusplus.com/reference/map/map/max_size/
			size_t	max_size() const {return (alloc_traits::max_size(_alloc));}

			/**
			 *		Element Acess
			 */
			
			// https://www.cplusplus.com/reference/map/map/operator[]/
			T	&operator[](const key &k)
			{
				for (size_t i = 0; i < _size; i++)
				{
					if (k == _arr->first)
						return (_arr->second);
					_arr++;
				}
				return (nullptr);
			}

			/**
			 *		Modifiers
			 */
			
			// https://www.cplusplus.com/reference/map/map/insert/
			// value = <vector, int>
			ft::pair<iterator, bool>	insert(const value_type &val)
			{
				_tree.add_node(val);
				ft::pair <iterator, ft::true_type> ret;
				return (ft::make_pair(it, true));
			};

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

			allocator get_allocator() const;

		private:
		
			size_t		_size;
			allocator	_alloc;
			value_type	*_arr;

			bst<key_type, mapped_type, value_compare>	_tree;
	};
}


#endif
