#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <cstring>
#include <memory>
#include <iostream>
// #include <exception>
// #include <stdexcept>
#include "../utils/type_traits.hpp"
#include "../utils/lexical_compare.hpp"
#include "../utils/equal.hpp"

#include "reverse_iterator.hpp"
#include "random_access_it.hpp"

namespace ft 
{
	
	template <typename T, typename allocator = std::allocator<T> >
	class vector
	{
		public:

			typedef T									value_type;
			typedef allocator							allocator_type;
			typedef T&									reference;  
			typedef T* 									pointer;
			typedef const T* 							const_pointer;
			typedef random_access_it<vector<T> > 		iterator;
			typedef random_access_it<vector<const T> >	const_iterator;
			typedef reverse_iterator<vector<const T> >	const_reverse_iterator;
			typedef reverse_iterator<vector<T> > 		reverse_iterator;
			typedef ptrdiff_t 							difference_type;
			typedef size_t								size_type;


			/**
			 *  Contructors
			 */ 

			vector(const allocator_type& alloc = allocator_type())
			:  _arr(NULL), _capacity(0), _size(0), _alloc(alloc) {}

			explicit vector(size_t n, const T &val = T(), const allocator_type& alloc = allocator_type())
			:	_capacity(n), _size(n), _alloc(alloc)
			{
				std::cout << "Size: " << n << std::endl;
				_arr = _alloc.allocate(n);
				for (size_t i = 0; i < n; i++)
					_alloc.construct(_arr + i, val);
			}

			template <class InputIterator>
			vector(InputIterator first, InputIterator last, const allocator& alloc = allocator(), 
			typename enable_if<!is_integral<InputIterator>::value>::type* = 0)
			{
				_alloc = alloc;
				difference_type size = last - first;
				_size = (size_t)size;
				_capacity = _size;
				_arr = _alloc.allocate(_capacity);
				for (size_t i = 0; first != last; first++, i++)
					_alloc.construct(_arr + i, *first);
			}
			
			vector(const vector &obj) // Nao esta acabado
			:	_arr(0), _capacity(0), _size(0), _alloc(obj._alloc) 
			{
				*this = obj;
				_capacity = obj._size; // Porque quando nao passamos uma ref para uma fn, a capacity ficar igual ao size, dkw
			}
			
			~vector() { _destroy_arr(); }

			vector	&operator = (const vector &rhs) 
			{
				if (this == &rhs)
					return (*this);
				if (_capacity != 0)
					_destroy_arr();
				_capacity = rhs._capacity;
				_size = rhs._size;
				if (_alloc != rhs._alloc)
					_alloc = rhs._alloc;
				_arr = _alloc.allocate(_capacity);
				for (size_t i = 0; i < _capacity; i++)
					_alloc.construct(_arr + i, rhs._arr[i]);
				return (*this);
			}

			/**
			 *		Iterators
			 */

			iterator  begin() { return ((_arr));}
			const_iterator	begin() const {return ((_arr));} // Nao esta feito
			reverse_iterator rbegin() {return (_arr);};
			const_reverse_iterator rbegin() const {return ((_arr));}
			
			iterator  end() { return (_arr + _size);}
			const_iterator  end() const  {return (_arr + _size);} // Nao esta feito

			
			/**
			 *		Capacity
			 */
	
			size_t	size() const {return (_size);}
			size_t max_size() const {return (_alloc.max_size());};
			
			// https://www.cplusplus.com/reference/vector/vector/resize/
			/**
			 * @decription: Resizes the container so that it contains n elements.
			 * @condicions: 
			 * - If n is smaller than the current container size, the content is reduced to its first n elements, removing those beyond (and destroying them).
			 * @questions: Sera que e preciso dealocar ou so destroir os objetos? Reduzir a capacity?
			 * 
			 * - If n is greater than the current container size, the content is expanded by inserting at the end as many elements as needed to reach a size of n. If val is specified, the new elements are initialized as copies of val, otherwise, they are value-initialized.
			 * - If n is also greater than the current container capacity, an automatic reallocation of the allocated storage space takes place.
			 */
			
			void	resize(size_t n, T val = T())
			{
				std::cout << "value: " << val << std::endl;
				if (n == 0 && _size != 0)
					_destroy_arr();
				else if (n < _size)
				{
					for (size_t i = n; i < _size; i++)
						_alloc.destroy(_arr + i);
				} 
				else if (n > _size && n < _capacity) 
				{
					for (size_t i = _size; i < n; i++)
						_alloc.construct(_arr + i, val);
				} 
				else if (n > _capacity && n < max_size()) 
				{
					reserve(n);
					insert(begin(), n - _size, val);
				}
				_size = n;
				_capacity = n;
			} 
			
			size_t  capacity() const { return (_capacity); };

			bool empty() const { return (_size == 0); }

			// Este funciona
			void	reserve(size_t newCapacity) 
			{
				// std::cout << "check this one: " << this->_size << "\n";
				if (newCapacity > _capacity)
				{
					T *temp = _alloc.allocate(newCapacity);
					for (size_t i = 0; i < _capacity; i++)
						_alloc.construct(temp + i, _arr[i]);
					for (size_t i = _capacity; i < newCapacity; i++)
						_alloc.construct(temp + i, 0);
					_destroy_arr();
					_arr = temp;
					_capacity = newCapacity;
				}
			}

			/**
			 *		Element acess 
			 */


			T	&operator[](size_t index) { return (_arr[index]); }
			const T	&operator[](size_t index) const { return (_arr[index]); }

			/**
			 * @definition: Returns a reference to the element at position n in the vector.
			 * The function automatically checks whether n is within the bounds of valid elements in the vector, 
			 * throwing an out_of_range exception if it is not (i.e., if n is greater than, or equal to its size). 
			 */ 

			T	&at(size_t n) // Nao esta testado
			{
				if (n >= _size)
					throw std::out_of_range("vector");
				return (_arr[n]);			
			}

			const T	&at(size_t n) const // Nao esta testado
			{
				if (n >= _size)
					throw std::out_of_range("vector");
				return (_arr[n]);					
			}

			T	&front()  { return (*_arr); }
			const T	&front() const { return (*_arr); }

			T	&back() {return (_arr[_size - 1]);}
			const T	&back() const {return (_arr[_size - 1]); }

			/**
			 *		Modifiers
			 */

			void	assign(size_t n, const T &val)
			{
				vector<T> newOne(n, val);
				*this = newOne;
			}
			
			// Range
			template <class InputIterator>
			void	assign(InputIterator first, InputIterator last, 
			typename enable_if<!is_integral<InputIterator>::value>::type* = 0) // Fazer enable 
			{
				vector<T> newOne(first, last);
				*this = newOne;
			}

			void    push_back(const T &val) {
				if (_capacity == 0)
					reserve(2);
				if (_size >= _capacity)
					reserve(_capacity * 2);
				_alloc.construct(_arr + (_size++), val);
			}

			void pop_back()
			{
				_alloc.destroy(_arr + (--_size) - 1);
			}


			iterator	insert(iterator position, const T &val) 
			{
				difference_type offset = position - begin();
				if (++_size > _capacity)
					reserve(_size * 2);
				T*	temp = _alloc.allocate(_capacity);
				for (size_t i = 0, j = 0; i < _size; i++)
				{
					if (i != (size_t)offset)
						_alloc.construct(temp + i, _arr[i - j]);
					else
						_alloc.construct(temp + i + j++, val);
				}
				_destroy_arr();
				_arr = temp;
				return (position);
			}

			iterator	insert(iterator position, size_t n, const T& val)
			{
				difference_type offset = position - begin();
				// std::cout << "offset: " << offset << "\n";
				// std::cout << "n: " << n << "\n";
				_size += n;
				if (_size > _capacity)
					reserve(_size + 1);
				T*	temp = _alloc.allocate(_capacity);
				size_t i = 0, x = 0;
				for (; i < (size_t)offset; i++)
					_alloc.construct(temp + i + x, *(_arr + i));
				// std::cout << "i: " << i << std::endl;
				for (; x < n; x++)
					_alloc.construct(temp + i + x, val);
				for (; i + x < _size; i++)
					_alloc.construct(temp + i + x, *(_arr + i));

				_destroy_arr();
				_arr = temp;
				return (begin() + offset);
			}

			template <typename InputIterator>
			void	insert(iterator position, InputIterator first, InputIterator last,
			typename enable_if<!is_integral<InputIterator>::value, InputIterator>::type* = 0) // Nao esta bem feito
			{
				size_t n = 0;
				iterator it = begin();
				
				for (; it != position && it != end(); it++, n++);
				if (it == end() && it != position)
					return ;
				size_t newSize = _size + (last - first);
				if (newSize > _capacity)
					reserve(newSize);
				T* temp = _alloc.allocate(newSize);
				for (size_t i = 0, j = 0; i + j < newSize; i++)
				{
					if (i == n)
					{
						for (;first != last; first++, j++)
							_alloc.construct(temp + j + i, *first);
					}
					if (i + j >= newSize)
						break;
					_alloc.construct(temp + j + i, *(_arr + i));
				}
				_destroy_arr();
				_arr = temp;
				_size = newSize;

			}

			/**
			 *  @describe: Removes from the vector either a single element (position) or a range of elements ([first,last)).
			 *	This effectively reduces the container size by the number of elements removed, which are destroyed.
			 *	Because vectors use an array as their underlying storage, erasing elements in positions other than the vector end causes the container to 
			 *	relocate all the elements after the segment erased to their new positions. 
			 *	This is generally an inefficient operation compared to the one performed for the same operation by other kinds of sequence containers (such as list or forward_list).
			 * 
			 */

			iterator	erase(iterator position) // Nao esta feito
			{
				for (iterator it = begin(); it != end(); it++)
				{
					if (it >= position)
					{
						iterator temp = it + 1;
						*it = *temp;
					}
				}
				_alloc.destroy(_arr + _size);
				_size--;
				if (_capacity > _size * 2)
					resize(_size + 1);
				return (position);
			}
	
			iterator	erase(iterator first, iterator last)
			{
				T* temp;
				difference_type offset = last - first;
				_size -= offset;
				_capacity = _size * 2;
				temp = _alloc.allocate(_capacity);
				iterator it = begin();
				for (size_t i = 0, j = 0; it != end(); it++, i++)
				{
					if ((it == first) && (j = offset))
						it += offset;
					else
						_alloc.construct(temp + i, _arr + i + offset);
				}
			}


			/**
			 *	Exchanges the content of the container by the content of x, which is another vector object of the same type. Sizes may differ.
			 *	After the call to this member function, the elements in this container are those which were in x before the call, 
			 * 	and the elements of x are those which were in this. All iterators, references and pointers remain valid for the swapped objects.
			 *	Notice that a non-member function exists with the same name, swap, overloading that algorithm with an optimization that behaves like this member function. 
			 */

			void 	clear()
			{
				for (size_t i = 0; i < _size; i++)
					_alloc.destroy(_arr + i);
				_size = 0;
			}

			/**
			 *		Allocator
			 */

			allocator	get_allocator() const { return _alloc; }

			/**
			 *	Relational operators - Non member functions overloads
			 */

			friend	bool	operator==(const vector &lhs, const vector &rhs) { return (ft::equal(lhs.begin(), lhs.end(), rhs.begin())); }

			friend	bool	operator!=(const vector &lhs, const vector &rhs) { return (!(lhs == rhs)); }

			friend	bool	operator<(const vector &lhs, const vector &rhs) {
				return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
			}
			
			friend	bool	operator<=(const vector &lhs, const vector &rhs) {
				return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()) 
				|| ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
			}
			
			friend	bool	operator>(const vector &lhs, const vector &rhs) { return (!(lhs <= rhs)); }
			
			friend	bool	operator>=(const vector &lhs, const vector &rhs) { return (!(lhs < rhs)); }


			/**
			 * Exchanges the content of the container by the content of x, 
			 *  which is another vector object of the same type. Sizes may differ.
			 * After the call to this member function, the elements in this container are those
			 *  which were in x before the call, and the elements of x are those which were in this.
			 *  All iterators, references and pointers remain valid for the swapped objects.
			 * Notice that a non-member function exists with the same name, swap, overloading 
			 *  that algorithm with an optimization that behaves like this member function.
			 */ 
			void	swap(vector &x) // Nao esta feito
			{
				std::swap(_arr, x._arr);
				std::swap(_capacity, x._capacity);
				std::swap(_size, x._size);
				std::swap(_alloc, x._alloc);
			}

		private:

			void	swap_elem(T &elem1, T &elem2)
			{
				T temp;
				temp = elem1;
				elem1 = elem2;
				elem2 = temp; 			
			}

			void	_destroy_arr()
			{
				for (size_t i = 0; i < _size; i++)
					_alloc.destroy(_arr + i);
				_alloc.deallocate(_arr, _capacity);
			}

			pointer		_arr;
			size_t		_capacity;
			size_t		_size;
			allocator	_alloc;
	};

}

#endif
