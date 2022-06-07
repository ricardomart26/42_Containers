#ifndef MAP_ITERATOR_HPP
#define MAP_ITERATOR_HPP

#include "binary_search_tree.hpp"

namespace ft
{
    template <typename map> // map é o objeto map<T>, e a partir do parametro do 
    // do template conseguimos usar as variaveis que declaramos na classe do map
    class map_iterator 
        : protected bst<map::key_type, map::mapped_type, map::compare, > 
    {
        public:

            typedef typename map::value_type            value_type;
            typedef typename map::allocator_type        allocator_type;
            typedef typename map::key_type              key_type;
            typedef typename map::mapped_type           mapped_type;
            typedef typename map::value_type*           pointer;
            typedef typename map::value_type&           reference;
            typedef typename map::difference_type       difference_type;

            map_iterator() : _ptr(NULL) {}

            map_iterator(pointer ptr) : _ptr(ptr) {} 

            map_iterator &operator=(const map_iterator &rhs)
            {
                _ptr = rhs._ptr;
                return (*this);
            }

            ~map_iterator() {};

            map_iterator &operator++()
            {
                _ptr++;
                return *this;
            }

            map_iterator	operator++(int)
            {
                map_iterator temp = *this;
                ++(*this);
                return temp;
            }

            map_iterator &operator--()
            {
                _ptr--;
                return *this;
            }

            map_iterator operator--(int)
            {
                map_iterator temp = *this;
                --(*this);
                return temp;
            }

            reference operator[] (int index) {return *(_ptr + index);}
            reference operator*() { return *(_ptr);}
            difference_type operator - (const map_iterator &rhs) const {return (_ptr - rhs._ptr);}
            map_iterator operator + (const difference_type &rhs) const {return (_ptr + rhs);}

            bool    operator == (const map_iterator &rhs) const {return _ptr == rhs._ptr;}
            bool    operator != (const map_iterator &rhs) const {return _ptr != rhs._ptr;}
            bool    operator > (const map_iterator &rhs) const {return _ptr > rhs._ptr;}
            bool    operator >= (const map_iterator &rhs) const {return _ptr >= rhs._ptr;}
            bool    operator < (const map_iterator &rhs) const {return _ptr < rhs._ptr;}
            bool    operator <= (const map_iterator &rhs) const {return _ptr <= rhs._ptr;}
        
        private:
            pointer _ptr;
    };
}

#endif
