#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <cstring>
#include <memory>
#include <iostream>
#include <exception>

namespace ft 
{

	class error_handling 
		: public std::exception
	{
		virtual const char *what() const throw();
	};

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

		
		private:
			pointer _ptr;
	};
	
	template <typename T, typename _Allocator = std::allocator<T> >
	class vector 
	{
		public:

			typedef std::allocator_traits<_Allocator> alloc_traits;
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

			vector() {
				// std::cout << "Vector constructed\n";
				_arr = NULL;
				_capacity = 0;
				_size = 0;
			}


			vector(size_t n)
			{
				// std::cout << "Vector constructed\n";
				_capacity = n;
				_size = n;
				_arr = _alloc.allocate(n);
				for (size_t i = 0; i < n; i++)
					_alloc.construct(_arr + i, 0);
			}

			vector(size_t n, const T &val, 
			const _Allocator& alloc = allocator_type())
			{
				// std::cout << "Vector constructed\n";
				_arr = _alloc.allocate(n);
				_capacity = n;
				_size = n;
				for (size_t i = 0; i < n; i++)
					_alloc.construct(_arr + i, val);
			}

			vector(const _Allocator& alloc = allocator_type()); // Nao fiz nem percebi muito bem

			template <class InputIterator>
			vector(InputIterator first, InputIterator last,
			const _Allocator& alloc = allocator_type()); 

			vector(const vector &obj) // Nao esta acabado
			{
				// std::cout << "Vector Copy constructor\n";
				_capacity = obj._capacity;
				_size = obj._size;
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
				_arr = _alloc.allocate(_capacity);
				for (size_t i = 0; i < _capacity; i++)
					_alloc.construct(_arr + i, rhs._arr[i]);
				return (*this);
			}

			/**
			 *		Iterators
			 */

			iterator  begin(){ return (iterator(_arr));}
			const_iterator	begin() const; // Nao esta feito
			
			iterator  end() { return (iterator(_arr + _size));}
			const_iterator  end() const; // Nao esta feito
			
			reverse_iterator rbegin();
			const_reverse_iterator rbegin() const;

			reverse_iterator rend();
			const_reverse_iterator rend() const;
			

			const_iterator  cbegin() noexcept { return (const_iterator(_arr));} // c++11
			const_iterator  cend() noexcept { return (const_iterator(_arr + _size + 1));} // c++11

			/**
			 *		Capacity
			 */
	
			size_t	size() const {return (_size);}
			
			size_t max_size() const {return (alloc_traits::max_size(_alloc));};
			
			void	resize(size_t n, T val = T()); // Nao esta feito
			
			size_t  capacity() const {return (_capacity);};

			bool empty() const {return (_size == 0);}

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

			/**
			 *		Element acess 
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

			T	&at(size_t n); // Nao esta feito
			const T	&at(size_t n) const; // Nao esta feito

			T	&front(); // Nao esta feito
			const T	&front() const; // Nao esta feito

			T	&back(); // Nao esta feito
			const T	&back() const; // Nao esta feito

			/**
			 *		Modifiers
			 */

			void	assign(size_t n, const T &val); // Nao esta feito
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


			iterator	insert(iterator position, const T val&); // Nao esta feito
			iterator	insert(iterator position, size_t n, const T& val)
			{
				// std::cout << *position << std::endl;
				diff_type offset = position - cbegin();
				if (_size == 0)
					return (nullptr);
				T*	temp = _alloc.allocate(_capacity);
				_size += n;
				if (_size > _capacity)
					reserve(_size + 1);
				for (size_t i = 0, x = 0; i < _size; i++)
				{
					if (i < (size_t)offset || x >= n)
						_alloc.construct(temp + i, *(_arr + i - n));
					else
						_alloc.construct(temp + i, val);
					x++;
				}
				_destroy_arr();
				_arr = temp;
				return (begin() + offset);
			}
			template <typename InputIterator>
			void	insert(iterator position, InputIterator first, InputIterator last); // Nao esta feito
			
			iterator	erase(iterator position); // Nao esta feito
			iterator	erase(iterator first, iterator last); // Nao esta feito

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

			_Allocator	get_allocator() const; // Nao esta feito

			/**
			 *	Relational operators - Non member functions overloads
			 */

			bool	operator==(const vector &lhs, const vector &rhs); // Nao esta feito
			bool	operator!=(const vector &lhs, const vector &rhs); // Nao esta feito
			bool	operator<(const vector &lhs, const vector &rhs); // Nao esta feito
			bool	operator<=(const vector &lhs, const vector &rhs); // Nao esta feito
			bool	operator>(const vector &lhs, const vector &rhs); // Nao esta feito
			bool	operator>=(const vector &lhs, const vector &rhs); // Nao esta feito

			void	swap(vector &x, vector &y); // Nao esta feito

		private:

			void	_destroy_arr()
			{
				for (size_t i = 0; i < _size; i++)
					_alloc.destroy(_arr + i);
				_alloc.deallocate(_arr, _capacity);
			}
			T			*_arr;
			size_t		_capacity;
			size_t		_size;
			_Allocator	_alloc;
	};

}

#endif
