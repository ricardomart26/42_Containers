#ifndef REVERSE_ITERATOR_HPP
#define REVERSE_ITERATOR_HPP

#include "iterator_traits.hpp"

namespace ft 
{
    template <typename iterator>
    class   reverse_iterator // Devia 
    {
        typedef iterator                                                 iterator_type;
        typedef typename iterator_traits<iterator>::iterator_category    iterator_catefory;
        typedef typename iterator_traits<iterator>::value_type           value_type;
        typedef typename iterator_traits<iterator>::difference_type      difference_type;
        typedef typename iterator_traits<iterator>::pointer              pointer;
        typedef typename iterator_traits<iterator>::reference            reference;

        reverse_iterator() : _ptr(nullptr) {};
        
        explicit    reverse_iterator(iterator_type iter) : _ptr(iter) {};
        
        template <class iter>
        reverse_iterator(const reverse_iterator<iter>& rev_it) : _ptr(rev_it.ptr) {};

        template< class iter >
        reverse_iterator& operator=( const reverse_iterator<iter>& other )
        { this->_ptr = other._ptr; }


        /**
         * 
         *  @description: Returns a copy of the base iterator.
         *  The base iterator is an iterator of the same type as the one used to 
         *  construct the reverse_iterator, but pointing to the element next to the
         *  one the reverse_iterator is currently pointing to (a reverse_iterator has
         *  always an offset of -1 with respect to its base iterator).
         * 
         *  @return: A copy of the base iterator, which iterates in the opposite direction.
         *  Member type iterator_type is the underlying bidirectional iterator type
         *  (the class template parameter: Iterator).
         * 
         */ 
        
        iterator_type   base() const    { return (_ptr); }

        /**
         * 
         *  @descrition: Returns a reference to the element pointed to by the iterator.
         *  Internally, the function decreases a copy of its base iterator 
         *  and returns the result of dereferencing it.
         *  The iterator shall point to some object in order to be dereferenceable.
         * 
         *  @return: A reference to the element pointed by the iterator.
         *  Member type reference is an alias of the base iterator's own reference type.
         */ 
        
        reference operator*() const
        { iterator temp = _ptr; return (*(--temp)); }
        
        reverse_iterator operator+ (difference_type n) const
        { return (reverse_iterator(_ptr + n)); }

        reverse_iterator operator- (difference_type n) const 
        {return (reverse_iterator(_ptr + n));}
        
        reverse_iterator &operator++() // sufixo
        { _ptr--; return (*this); }

        reverse_iterator operator++(int) // prefixo
        {
            reverse_iterator temp = *this;
            --_ptr;
            return (temp);
        }

        reverse_iterator &operator--()  // sufixo
        { _ptr++; return (*this); }
        
        reverse_iterator operator--(int) // prefixo
        {
            reverse_iterator temp = *this;
            ++_ptr;
            return (temp);
        }

        reverse_iterator& operator+= (difference_type n)
        { _ptr -= n; return (*this); }
        
        
        reverse_iterator& operator-= (difference_type n)
        { _ptr += n; return (*this); }

        pointer operator->() const  {return &(operator*());}

        reference operator[] (difference_type n) const  {return (*(_ptr + n));}


        /**
         * Relational operators
         */ 
        template <class Iterator>
        friend  bool operator== (const reverse_iterator<Iterator>& lhs,
                    const reverse_iterator<Iterator>& rhs)
        { return (lhs._ptr == rhs._ptr); }


        template <class Iterator>
        friend  bool operator!= (const reverse_iterator<Iterator>& lhs,
                    const reverse_iterator<Iterator>& rhs)
        { return (lhs._ptr != rhs._ptr); }

        template <class Iterator>
        friend  bool operator<  (const reverse_iterator<Iterator>& lhs,
        const reverse_iterator<Iterator>& rhs)
        { return (lhs._ptr < rhs._ptr); }


        template <class Iterator>
        friend  bool operator<= (const reverse_iterator<Iterator>& lhs,
                        const reverse_iterator<Iterator>& rhs)
        { return (lhs._ptr <= rhs._ptr); }


        template <class Iterator>
        friend  bool operator>  (const reverse_iterator<Iterator>& lhs,
                        const reverse_iterator<Iterator>& rhs)
        { return (lhs._ptr > rhs._ptr); }


        template <class Iterator>
        friend  bool operator>= (const reverse_iterator<Iterator>& lhs,
                        const reverse_iterator<Iterator>& rhs)
        { return (lhs._ptr >= rhs._ptr); }

        
        template <class Iterator>
        friend  reverse_iterator<Iterator> operator+ (
            typename reverse_iterator<Iterator>::difference_type n,
            const reverse_iterator<Iterator>& rev_it)
        { return (rev_it._ptr - n); } 
        
        template <class Iterator>
        friend  typename reverse_iterator<Iterator>::difference_type operator- (
            const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
        { return (lhs._ptr + rhs._ptr); }

        private:

            iterator _ptr;
    };
}

#endif
