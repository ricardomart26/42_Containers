#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <cstring>
#include <memory>
#include <iostream>
#include <exception>

namespace ft 
{

	// class error_handling 
	// 	: public std::exception
	// {
	// 	virtual const char *what() const throw();
	// };

	template <typename Vec> // Vec é o objeto vector<T>, e a partir do parametro do 
	// do template conseguimos usar as variaveis que declaramos na classe do vector
	class VecIterator
	{
		public:

			typedef typename Vec::value_type value_type;
			typedef typename Vec::value_type* pointer;
			typedef typename Vec::value_type& reference;
			typedef typename Vec::diff_type diff_type;

			VecIterator(pointer ptr) : _ptr(ptr){} 

			// VecIterator &operator=(const VecIterator &rhs)
			// {
			// 	_ptr = rhs._ptr;
			// }

			~VecIterator() {};
			VecIterator& operator++()
			{
				_ptr++;
				return *this;
			}

			VecIterator operator++(int)
			{
				VecIterator temp = *this;
				++(*this);
				return temp;
			}

			VecIterator& operator--()
			{
				_ptr--;
				return *this;
			}

			VecIterator operator--(int)
			{
				VecIterator temp = *this;
				--(*this);
				return temp;
			}

			reference operator[] (int index) {return *(_ptr + index);}

			reference operator*() { return *(_ptr);}
			// VecIterator &operator = (const VecIterator *rhs)
			// {

			// }
			diff_type operator - (const VecIterator &rhs) const {return (_ptr - rhs._ptr);}
			VecIterator operator + (const diff_type &rhs) const {return (_ptr + rhs);}
			
			bool    operator == (const VecIterator &rhs) const {return _ptr == rhs._ptr;}
			bool    operator != (const VecIterator &rhs) const {return _ptr != rhs._ptr;}
			bool    operator > (const VecIterator &rhs) const {return _ptr > rhs._ptr;}
			bool    operator >= (const VecIterator &rhs) const {return _ptr >= rhs._ptr;}
			bool    operator < (const VecIterator &rhs) const {return _ptr < rhs._ptr;}
			bool    operator <= (const VecIterator &rhs) const {return _ptr <= rhs._ptr;}
		
		private:
			pointer _ptr;
	};
	
	template <typename T, typename _allocator = std::allocator<T> >
	class vector 
	{
		public:

			typedef _allocator allocator_type; 
			typedef std::allocator_traits<_allocator> alloc_traits;
			typedef T value_type;
			typedef value_type * pointer;
			typedef VecIterator<vector<T> > iterator;

			typedef ptrdiff_t diff_type;
			// typedef __gnu_cxx::iterator_traits<T>::
			typedef const iterator const_iterator;

			/**
			 * 
			 *  Contructors
			 * 
			 */ 

			// vector()
			// : _arr(nullptr), _capacity(0), _size(0) {}

			vector(const allocator_type& alloc = allocator_type())
			:  _arr(nullptr), _capacity(0), _size(0), _alloc(alloc) {}

			// vector() {
			// 	// std::cout << "Vector constructed\n";
			// 	_arr = NULL;
			// 	_capacity = 0;
			// 	_size = 0;
			// }


			// vector(size_t n)
			// {
			// 	// std::cout << "Vector constructed\n";
			// 	_capacity = n;
			// 	_size = n;
			// 	_arr = _alloc.allocate(n);
			// 	for (size_t i = 0; i < n; i++)
			// 		_alloc.construct(_arr + i, 0);
			// }

			// vector(size_t n, const T &val)
			// {
			// 	// std::cout << "Vector constructed\n";
			// 	_arr = _alloc.allocate(n);
			// 	_capacity = n;
			// 	_size = n;
			// 	for (size_t i = 0; i < n; i++)
			// 		_alloc.construct(_arr + i, val);
			// }

			// vector(size_t n, const T &val)
			// {
			// 	// std::cout << "Vector constructed\n";
			// 	_arr = _alloc.allocate(n);
			// 	_capacity = n;
			// 	_size = n;
			// 	for (size_t i = 0; i < n; i++)
			// 		_alloc.construct(_arr + i, val);
			// }

			explicit vector(size_t n, const T &val = T(), const allocator_type& alloc = allocator_type())
			:	_capacity(n), _size(n), _alloc(alloc)
			{
				// std::cout << "Vector constructed\n";
				_arr = _alloc.allocate(n);
				for (size_t i = 0; i < n; i++)
					_alloc.construct(_arr + i, val);
			}

			template <class InputIterator>
			vector(InputIterator first, InputIterator last, const _allocator& alloc = _allocator())
			{
				_alloc = alloc;
				diff_type size = last - first;
				_size = (size_t)size;
				_capacity = _size;
				_arr = _alloc.allocate(_capacity);
				for (size_t i = 0; first != last; first++, i++)
					_alloc.construct(_arr + i, *first);
			}

			vector(const vector &obj) // Nao esta acabado
			:	_capacity(obj._capacity), _size(obj._size), _alloc(allocator_type())
			{
				// std::cout << "Vector Copy constructor\n";
				_arr = _alloc.allocate(_capacity);
				for (size_t i = 0; i < _size; i++)
					_alloc.construct(_arr + i, *(obj._arr + i));
			}
			
			~vector() {
				// std::cout << "Vector deconstructed\n";
				_destroy_arr();
			}
			
			vector	&operator = (const vector &rhs) {
				if (this == &rhs)
					return (*this);
				if (_capacity != 0)
					_destroy_arr();
				_capacity = rhs._capacity;
				_size = rhs._size;
				if (_alloc != rhs._alloc)
					_alloc = rhs._alloc;
				// _arr = rhs._arr;
				_arr = _alloc.allocate(_capacity);
				for (size_t i = 0; i < _capacity; i++)
					_alloc.construct(_arr + i, rhs._arr[i]);
				return (*this);
			}

			/**
			 *		Iterators
			 */

			iterator  begin() { return (iterator(_arr));}
			const_iterator	begin() const; // Nao esta feito
			
			iterator  end() { return (iterator(_arr + _size));}
			const_iterator  end() const; // Nao esta feito
			
			// reverse_iterator rbegin(); // Nao fiz
			// const_reverse_iterator rbegin() const; // Nao fiz

			// reverse_iterator rend(); // Nao fiz
			// const_reverse_iterator rend() const; // Nao fiz
			
			/**
			 *		Capacity
			 */
	
			size_t	size() const {return (_size);}
			
			size_t max_size() const {return (alloc_traits::max_size(_alloc));};
			
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
				if (n == 0)
					_destroy_arr();
				if (n < _size) {
					for (size_t i = n; i < _size; i++)
						_alloc.destroy(_arr + i);
				} else if (n > _size && n < _capacity) {
					for (size_t i = _size; i < n; i++)
						_alloc.construct(_arr + i, val);
				} else if (n > _capacity && n < max_size()) {
					reserve(n);
					insert(begin(), n - _size, val);
				}
				_size = n;
			} 
			
			size_t  capacity() const {return (_capacity);};

			bool empty() const {return (_size == 0);}

			// Este funciona
			void	reserve(size_t newCapacity) {
				if (newCapacity <= _capacity)
					return ;
				T *temp = _alloc.allocate(newCapacity);
				for (size_t i = 0; i < _capacity; i++)
					_alloc.construct(temp + i, _arr[i]);
				for (size_t i = _capacity; i < newCapacity; i++)
					_alloc.construct(temp + i, 0);
				_destroy_arr();
				_arr = temp;
				_capacity = newCapacity;
			}

			// void	reserve(size_t newCapacity) {
			// 	if (newCapacity <= _capacity)
			// 		return ;
			// 	for (size_t i = 0; i < _capacity; i++)
			// 		_alloc.construct(temp + i, _arr[i]);
			// 	for (size_t i = _capacity; i < newCapacity; i++)
			// 		_alloc.construct(temp + i, 0);
			// 	_destroy_arr();
			// 	_arr = temp;
			// 	_capacity = newCapacity;
			// }

			/**
			 *		Element acess 
			 */


			/**
			 * Secalhar vou ter que retirar a validacao (assert)
			 */ 
			T	&operator[](size_t index)
			{
				assert(index < _size);
				return (_arr[index]);
			}
			const T	&operator[](size_t index) const
			{
				assert(index < _size);
				return (_arr[index]);
			}

			/**
			 * @definition: Returns a reference to the element at position n in the vector.
			 * The function automatically checks whether n is within the bounds of valid elements in the vector, 
			 * throwing an out_of_range exception if it is not (i.e., if n is greater than, or equal to its size). 
			 */ 

			T	&at(size_t n) // Nao esta testado
			{
				assert(n < _size);
				return (_arr[n]);					
			}
			const T	&at(size_t n) const // Nao esta testado
			{
				assert(n < _size);
				return (_arr[n]);					
			}

			
			/**
			 * Possivelmente vou ter que tirar o assert do front e do back
			 */ 

			T	&front()  // Nao esta testado
			{
				assert(!empty());
				return (_arr);
			}
			const T	&front() const // Nao esta testado
			{
				assert(!empty());
				return (_arr);
			}

			T	&back() // Nao esta testado
			{
				assert(!empty());
				return (_arr[_size - 1]);
			}
			const T	&back() const // Nao esta testado
			{
				assert(!empty());
				return (_arr[_size - 1]);
			}

			/**
			 *		Modifiers
			 */

			void	assign(size_t n, const T &val)
			{
				vector<T> newOne(n, val);
				*this = newOne;
				// newOne.~vector();
			}
			// Range
			template <class InputIterator>
			void	assign(InputIterator first, InputIterator last); // Nao esta feito

			void    push_back(const T &val) {
				// std::cout << "size: "<< _size<<" capacity: "<<_capacity<<"\n";
				if (_capacity == 0)
					reserve(2);
				if (_size >= _capacity)
					reserve(_capacity * 2);
				_alloc.construct(_arr + _size, val);
				_size++;
			}

			void pop_back()
			{
				assert(!empty()); // Verificar se funciona
				// std::cout << _arr[_size - 1] << std::endl;
				_alloc.destroy(_arr + _size); // Ver se este e o ultimo valor
				_size--;
			}


			iterator	insert(iterator position, const T &val) 
			{
				// std::cout << *position << std::endl;
				// std::cout << *position << std::endl;
				diff_type offset = position - begin();
				// if (_size == 0) // Isto possivelmente esta errado
				// 	return (nullptr);
				_size++;
				if (_size > _capacity)
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
				// std::cout << *position << std::endl;
				assert(n != 0);
				diff_type offset = position - begin();
				// if (_size == 0) // Isto possivelmente esta errado
				// 	return (nullptr);
				_size += n;
				if (_size > _capacity)
					reserve(_size + 1);
				T*	temp = _alloc.allocate(_capacity);
				
				
				// size_t i = 0;
				// for (; i < (size_t)offset; i++)
				// 	_alloc.construct(temp + i, (_arr + i));
				// for (; i < n; i++)
				// 	_alloc.construct(temp + i, val);
				// size_t x = i - n;
				// for (; i < _size; i++, x++)
				// 	_alloc.construct(temp + i, (_arr + x));

				for (size_t i = 0, x = 0; i < _size; i++)
				{
					for (; i >= (size_t)offset && x >= n; x++)
						_alloc.construct(temp + i + x, val);
					_alloc.construct(temp + i + x, *(_arr + i));
				}

				// for (size_t i = 0, x = 0; i < _size; i++)
				// {
				// 	while (i < (size_t)offset || x >= n)
				// 	{
				// 		_alloc.construct(temp + i, *(_arr + i - n));
				// 		i++;
				// 		x++;
				// 	}
				// }
				_destroy_arr();
				_arr = temp;
				return (begin() + offset);
			}
			
			template <typename InputIterator>
			void	insert(iterator position, InputIterator first, InputIterator last) // Nao esta feito
			{
				diff_type offset = position - begin();
				std::cout << "offset e o tamanho?" << last - first << std::endl;
				size_t n = 0;
				ft::vector<int>::iterator it = begin();
				for (; it != position || it != end(); it++, n++)

				std::cout << "n: " << n << "and offset: " << offset << std::endl;
				if (it == end())
					return; // Ver o que faz se nao encontrar a position

				T* temp = _alloc.allocate(_capacity);
				size_t oldSize = _size; // + tamanho do first ao last 
				// Proteger se o tamanho + _size > capacity
				for (size_t i = 0, j = 0; i < oldSize; i++)
				{
					if (i == n)
					{
						for (;first != last; first++, j++)
							_alloc.construct(temp + j + i, *first);
					}
					_alloc.construct(temp + j + i, _arr + i);
				}
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
	
			// iterator	erase(iterator first, iterator last) // Nao esta feito
			// {

			// }


			/**
			 *	Exchanges the content of the container by the content of x, which is another vector object of the same type. Sizes may differ.
			 *	After the call to this member function, the elements in this container are those which were in x before the call, 
			 * 	and the elements of x are those which were in this. All iterators, references and pointers remain valid for the swapped objects.
			 *	Notice that a non-member function exists with the same name, swap, overloading that algorithm with an optimization that behaves like this member function. 
			 */
			void	swap(vector& x); // Nao esta feito

			void 	clear()
			{
				for (size_t i = 0; i < _size; i++)
					_alloc.destroy(_arr + i);
				_size = 0;
			}

			/**
			 *		Allocator
			 */

			_allocator	get_allocator() const; // Nao esta feito

			/**
			 *	Relational operators - Non member functions overloads
			 */

			friend	bool	operator==(const vector &lhs, const vector &rhs); // Nao esta feito
			friend	bool	operator!=(const vector &lhs, const vector &rhs); // Nao esta feito
			friend	bool	operator<(const vector &lhs, const vector &rhs); // Nao esta feito
			friend	bool	operator<=(const vector &lhs, const vector &rhs); // Nao esta feito
			friend	bool	operator>(const vector &lhs, const vector &rhs); // Nao esta feito
			friend	bool	operator>=(const vector &lhs, const vector &rhs); // Nao esta feito

			void	swap(vector &x, vector &y); // Nao esta feito

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
			T			*_arr;
			size_t		_capacity;
			size_t		_size;
			_allocator	_alloc;
	};

}

#endif
