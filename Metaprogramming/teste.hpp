#ifndef TESTE_HPP
#define TESTE_HPP

#include <type_traits>

template<typename T, typename U>
struct is_same : ;

template<typename T>
struct is_same {}

template<typename T, typename... Args>
struct is_one_of : is_same<;

#endif
