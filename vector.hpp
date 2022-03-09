#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <cstring>
#include <memory>

namespace ft 
{
    template <class T>
    class vector 
    {
        public:
            vector();
            vector(size_t n);
            vector(size_t n, const T &val);
            vector(const vector &obj);
            ~vector();
            vector operator = (const vector &rhs);

            void    reserve(size_t capacity);
            void    push_back(const T &val);
            void    assign(size_t n, const T &val);
            // void    assign(size_t n, const T &val);
            T       *begin();
            T       *end();
            size_t  capacity();
            // template <class IT>
            class iterator
            {
                public:
                    iterator();
                    ~iterator();
                    iterator &operator = (const iterator *rhs)
                    {
                        
                        return ();
                    }
            }

        private:

            T       *_arr;
            size_t  _capacity;
            size_t  _size;
            
            std::allocator<T> _alloc;
    };
}

template <class T>
ft::vector<T>::vector()
{
    _capacity = 0;
}

template <class T>
ft::vector<T>::vector(size_t n)
{
    _capacity = n;
    _arr = _alloc.allocate(n);
    for (auto i = 0; i < n; i++)
        _alloc.construct(_arr + i, 0);
}

template <class T>
ft::vector<T>::vector(size_t n, const T &val)
{
    _arr = _alloc.allocate(n);
    _capacity = n;
    for (auto i = 0; i < n; i++)
        _alloc.construct(_arr + i, val);
}

template <class T>
ft::vector<T>::vector()
{

}

template<class T>
void    ft::vector<T>::reserve(size_t capacity)
{
    T *temp;

    temp = alloc.allocate(this->_capacity);
    for (int i = 0; i < this->_capacity; i++)
        temp.construct(temp + i, this->_arr[i]);

    _alloc.deallocate(_arr, capacity);
    _arr = _alloc.allocate(capacity);
    for (auto i = 0; i < capacity; i++)
        _alloc.construct(_arr + i, temp[i]);
    temp.deallocate(temp, capacity);
}


template <class T>
size_t  ft::vector<T>::capacity()
{
    return (_capacity);
}

template <class T>
T   *ft::vector<T>::begin()
{
    T *ptr = _arr[0];
    return (ptr);
}

template <class T>
T   *ft::vector<T>::end()
{
    T *ptr = _arr[_capacity - 1];
    return (ptr);
}

#endif
