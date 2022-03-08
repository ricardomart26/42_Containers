#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <cstring>




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

            void    push_back(const T &val);
            void    assign(size_t n, const T &val);
            void    assign(size_t n, const T &val);
            T       *begin();
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
    _arr = new T[n];
    _capacity = n;
    for (auto i = 0; i < n; i++)
        _arr[i] = 0;
}

template <class T>
ft::vector<T>::vector(size_t n, const T &val)
{
    _arr = new T[n];
    _capacity = n;
    for (auto i = 0; i < n; i++)
        _arr[i] = val;
}

template <class T>
ft::vector<T>::vector()
{

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

#endif
