#ifndef EQUAL_HPP
#define EQUAL_HPP

// Exprimentar se o segundo for igual ao primeiro mas tiver mais elementos
// Ex: 1: {4, 5, 6, 7, 8, 9}    2: {4, 5, 6, 7, 8, 9, 19, 1999}

#include <iostream>

namespace ft 
{
    template <class Iterator1, class Iterator2, class Predicate>
    bool    equal(Iterator1 first, Iterator1 last, Iterator2 first2, Predicate pred)
    {
        while (first != last && pred(*first, *first2))
        {
            first++;
            first2++;
        }
        if (first == last) return (true);
        return (false);
    }
    
    template <class Iterator1, class Iterator2>
    bool    equal(Iterator1 first, Iterator1 last, Iterator2 first2)
    {
        while (first != last && *(first) == *(first2))
        {
            first++;
            first2++;
        }
        if (first == last) return (true);
        return (false);
    }

}

#endif
