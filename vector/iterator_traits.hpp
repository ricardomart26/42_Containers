#ifndef ITERATOR_TRAITS_HPP
#define ITERATOR_TRAITS_HPP


#include <stddef.h>


/**
 * @links: https://www.codeproject.com/Articles/36530/An-Introduction-to-Iterator-Traits
 * https://docs.oracle.com/cd/E19422-01/819-3704/ite_2405.htm
*/
// template <typename Category, typename T, typename Distance = ptrdiff_t,
//     typename Pointer = T*, typename Reference = T&>
namespace ft 
{
    struct input_iterator_tag {};
    struct output_iterator_tag {};
    struct foward_iterator_tag : public input_iterator_tag {};
    struct bidirecional_iterator_tag : public foward_iterator_tag {};
    struct random_access_iterator_tag : public bidirecional_iterator_tag {};

    template <typename T> // Tipo de iterador
    struct iterator_traits
    {
        typedef typename T::value_type value_type;
        typedef typename T::pointer pointer;
        typedef typename T::reference reference;
        typedef typename T::iterator_category iterator_category;
        typedef typename T::difference_type difference_type;
    };


    // Especializacao para o random_access_iterator_traits
    template <typename T> // Tipo de iterador
    struct iterator_traits<T*> 
    {
        typedef typename T value_type;
        typedef typename T* pointer;
        typedef typename T& reference;
        typedef typename random_access_iterator_traits iterator_category;
        typedef typename ptrdiff_t difference_type;
    };

    template <typename T> // Tipo de iterador
    struct iterator_traits<const T*> 
    {
        typedef typename T value_type;
        typedef typename T* pointer;
        typedef typename T& reference;
        typedef typename random_access_iterator_traits iterator_category;
        typedef typename ptrdiff_t difference_type;
    };
}


#endif