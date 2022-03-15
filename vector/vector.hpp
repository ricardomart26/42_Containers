#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <cstring>
#include <memory>
#include <iostream>

namespace ft 
{
	template <typename Vec> // Vec é o objeto vector<T>, e a partir do parametro do 
	// do template conseguimos usar as variaveis que declaramos na classe do vector
	class VecIterator
	{
		public:
			typedef typename Vec::value_type value_type;
			typedef typename Vec::value_type* pointer;
			typedef typename Vec::value_type& reference;
			typedef typename Vec::diff_type diff_type;
		public:
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

			reference operator[] (int index)
			{return *(_ptr + index);}

			reference operator*()
			{ return *(_ptr);}
			// VecIterator &operator = (const VecIterator *rhs)
			// {

			// }
			diff_type operator - (const VecIterator &rhs) const
			{
				return (_ptr - rhs._ptr);
			}
			
			VecIterator operator + (const diff_type &rhs) const
			{
				// std::cout << "operator + with diff_type\n";
				return (_ptr + rhs);
			}

			bool    operator == (const VecIterator &rhs) const
			{return _ptr == rhs._ptr;}

			bool    operator != (const VecIterator &rhs) const
			{ return _ptr != rhs._ptr;}

		
		private:
			pointer _ptr;
	};
	
	template <typename T>
	class vector 
	{
		public:
			typedef T value_type;
			typedef value_type * pointer;
			typedef VecIterator<vector<T> > iterator;
			
			typedef ptrdiff_t diff_type;
			// typedef __gnu_cxx::iterator_traits<T>::
			typedef const iterator const_iterator;
		public:

			/**
			 * 
			 *  Contructors
			 * 
			 */ 

			vector() {
				std::cout << "Vector constructed\n";
				_arr = NULL;
				_capacity = 0;
				_size = 0;
			}

			// vector(std::initializer_list<T> l) {
			// 	_size = l.size();
			// 	_capacity = _size;
			// 	_arr = _alloc.allocate(_capacity);
			// 	for (size_t i = 0; i < _capacity; i++)
			// 		_alloc.construct(_arr + i, l[i]);
			// 	std::cout << "Vector constructed\n";
			// }

			vector(size_t n)
			{
				std::cout << "Vector constructed\n";
				_capacity = n;
				_size = n;
				_arr = _alloc.allocate(n);
				for (size_t i = 0; i < n; i++)
					_alloc.construct(_arr + i, 0);
			}

			vector(size_t n, const T &val)
			{
				std::cout << "Vector constructed\n";
				_arr = _alloc.allocate(n);
				_capacity = n;
				_size = n;
				for (size_t i = 0; i < n; i++)
					_alloc.construct(_arr + i, val);
			}

			vector(const vector &obj) {
				std::cout << "Vector Copy constructor\n";
				_capacity = obj._capacity;
				_size = obj._size;
			}
			
			~vector() {
				std::cout << "Vector deconstructed\n";
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
			 * 
			 * Member Functions
			 * 
			 */ 

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

			void    push_back(const T &val) {
				// std::cout << "size: "<< _size<<" capacity: "<<_capacity<<"\n";
				if (_capacity == 0)
					reserve(2);
				if (_size >= _capacity)
					reserve(_capacity * 2);
				_alloc.construct(_arr + _size, val);
				_size++;
			}

			iterator  insert(const_iterator position, size_t n, const T& val)
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
			
			iterator  begin(){ return (iterator(_arr));}
			const_iterator  cbegin(){ return (const_iterator(_arr));}
			iterator  end() { return (iterator(_arr + _size + 1));}
			const_iterator  cend(){ return (const_iterator(_arr + _size + 1));}
			size_t  capacity() {return (_capacity);};
			size_t	size() {return (_size);}
			void    assign(size_t n, const T &val);
			void 	clear()
			{
				for (size_t i = 0; i < _size; i++)
					_alloc.destroy(_arr + i);
				_size = 0;
			}
			// void    assign(size_t n, const T &val);

		private:

			void	_destroy_arr()
			{
				for (size_t i = 0; i < _size; i++)
					_alloc.destroy(_arr + i);
				_alloc.deallocate(_arr, _capacity);
			}
			T					*_arr;
			size_t				_capacity;
			size_t				_size;
			std::allocator<T>	_alloc;
	};

}

#endif
