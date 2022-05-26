#ifndef RANDOM_ACCESS_ITERATOR_HPP
#define RANDOM_ACCESS_ITERATOR_HPP

namespace ft 
{
    template <typename vec> // Vec é o objeto vector<T>, e a partir do parametro do 
    // do template conseguimos usar as variaveis que declaramos na classe do vector
    class random_access_it
    {
        public:

            typedef typename vec::value_type value_type;
            typedef typename vec::value_type* pointer;
            typedef typename vec::value_type& reference;
            typedef typename vec::difference_type difference_type;

            random_access_it(pointer ptr) : _ptr(ptr){} 

            // random_access_it &operator=(const random_access_it &rhs)
            // {
            // 	_ptr = rhs._ptr;
            // }

            ~random_access_it() {};
            random_access_it &operator++()
            {
                _ptr++;
                return *this;
            }

            random_access_it	operator++(int)
            {
                random_access_it temp = *this;
                ++(*this);
                return temp;
            }

            random_access_it &operator--()
            {
                _ptr--;
                return *this;
            }

            random_access_it operator--(int)
            {
                random_access_it temp = *this;
                --(*this);
                return temp;
            }

            reference operator[] (int index) {return *(_ptr + index);}
            reference operator*() { return *(_ptr);}
            difference_type operator - (const random_access_it &rhs) const {return (_ptr - rhs._ptr);}
            random_access_it operator - (int i) const {return (_ptr - i);}

            random_access_it operator + (const difference_type &rhs) const {return (_ptr + rhs);}
            
            bool    operator == (const random_access_it &rhs) const {return _ptr == rhs._ptr;}
            bool    operator != (const random_access_it &rhs) const {return _ptr != rhs._ptr;}
            bool    operator > (const random_access_it &rhs) const {return _ptr > rhs._ptr;}
            bool    operator >= (const random_access_it &rhs) const {return _ptr >= rhs._ptr;}
            bool    operator < (const random_access_it &rhs) const {return _ptr < rhs._ptr;}
            bool    operator <= (const random_access_it &rhs) const {return _ptr <= rhs._ptr;}
        
        private:
            pointer _ptr;
    };
}

#endif
