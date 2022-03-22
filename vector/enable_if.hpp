#ifndef ENABLE_IF
#define ENABLE_IF

#include <iostream>

namespace ft {
    template <bool Cond, class T = void>
    struct enable_if 
    {
        // std::cout << "E verdadeiro\n";
        typedef T type;
    };

    template <class T>
    struct enable_if<false, T> 
    {
        // std::cout << "E falso\n";
    };
}

#endif
