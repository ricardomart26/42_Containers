#ifndef LEXICAL_COMPARE_HPP
#define LEXICAL_COMPARE_HPP


// Returns true if the range [first,last] compares lexicographically less than the range [first2,last2].

namespace ft
{
    template <class Iterator1, class Iterator2>
    bool    lexicographical_compare(Iterator1 first, Iterator1 last, 
    Iterator2 first2, Iterator2 last2)
    {
        while (first != last)
        {
            if (last2 == first2 || *first > *first2)
                return false;
            if (*first < *first2) 
                return (true);
            first2++;
            first++;
        }
        return (first2 != last2);
    }

    template <class Iterator1, class Iterator2, class Compare>
    bool    lexicographical_compare(Iterator1 first, Iterator1 last, 
    Iterator2 first2, Iterator2 last2, Compare cmp) // Testar para ver se o cmp é assim ou ao contrario
    {
        while (first != last)
        {
            if (last2 == first2 || !cmp(first, first2))
                return false;
            if (cmp(first, first2))
                return (true);
            first2++;
            first++;
        }
        return (first2 != last2);
    }
}


#endif
