#ifndef BIDIRECTIONAL_IT_HPP
#define BIDIRECTIONAL_IT_HPP

namespace ft
{
    template <typename vec> // Vec é o objeto vector<T>, e a partir do parametro do 
    // do template conseguimos usar as variaveis que declaramos na classe do vector
    class bidirection_it
    {
        public:

            typedef typename vec::value_type value_type;
            typedef typename vec::value_type* pointer;
            typedef typename vec::value_type& reference;
            typedef typename vec::difference_type difference_type;

            bidirection_it(pointer ptr) : _ptr(ptr){} 

            // bidirection_it &operator=(const bidirection_it &rhs)
            // {
            // 	_ptr = rhs._ptr;
            // }

            ~bidirection_it() {};
            bidirection_it &operator++()
            {
                _ptr++;
                return *this;
            }

            bidirection_it	operator++(int)
            {
                bidirection_it temp = *this;
                ++(*this);
                return temp;
            }

            bidirection_it &operator--()
            {
                _ptr--;
                return *this;
            }

            bidirection_it operator--(int)
            {
                bidirection_it temp = *this;
                --(*this);
                return temp;
            }

            reference operator[] (int index) {return *(_ptr + index);}
            reference operator*() { return *(_ptr);}
            difference_type operator - (const bidirection_it &rhs) const {return (_ptr - rhs._ptr);}
            bidirection_it operator + (const difference_type &rhs) const {return (_ptr + rhs);}
            
            bool    operator == (const bidirection_it &rhs) const {return _ptr == rhs._ptr;}
            bool    operator != (const bidirection_it &rhs) const {return _ptr != rhs._ptr;}
            bool    operator > (const bidirection_it &rhs) const {return _ptr > rhs._ptr;}
            bool    operator >= (const bidirection_it &rhs) const {return _ptr >= rhs._ptr;}
            bool    operator < (const bidirection_it &rhs) const {return _ptr < rhs._ptr;}
            bool    operator <= (const bidirection_it &rhs) const {return _ptr <= rhs._ptr;}
        
        private:
            pointer _ptr;
    };
}

#endif