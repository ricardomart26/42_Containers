// -*- C++ -*-
//===-------------------------- iterator ----------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef _LIBCPP_ITERATOR
#define _LIBCPP_ITERATOR

#include <__config>
#include <iosfwd> // for forward declarations of vector and string.
#include <__functional_base>
#include <type_traits>
#include <cstddef>
#include <initializer_list>
#include <__cxx_version>
#ifdef __APPLE__
#include <Availability.h>
#endif

#include <__debug>

#if !defined(_LIBCPP_HAS_NO_PRAGMA_SYSTEM_HEADER)
#pragma GCC system_header
#endif



template <class _Iter> // Este iter e um T*
class __wrap_iter
{
public:
    typedef _Iter                                                      iterator_type;
    typedef typename iterator_traits<iterator_type>::iterator_category iterator_category;
    typedef typename iterator_traits<iterator_type>::value_type        value_type;
    typedef typename iterator_traits<iterator_type>::difference_type   difference_type;
    typedef typename iterator_traits<iterator_type>::pointer           pointer;
    typedef typename iterator_traits<iterator_type>::reference         reference;
private:
    iterator_type __i;
public:
      __wrap_iter() _NOEXCEPT {}
    template <class _Up> 
    __wrap_iter(const __wrap_iter<_Up>& __u,
        typename enable_if<is_convertible<_Up, iterator_type>::value>::type* = 0) _NOEXCEPT
        : __i(__u.base()) {}

    reference operator*() const _NOEXCEPT
    {
        return *__i;
    }
    
    pointer  operator->() const _NOEXCEPT
    {
        return (pointer)_VSTD::addressof(*__i);
    }
    __wrap_iter& operator++() _NOEXCEPT
    {
        ++__i;
        return *this;
    }
    __wrap_iter  operator++(int) _NOEXCEPT {__wrap_iter __tmp(*this); ++(*this); return __tmp;}

    __wrap_iter& operator--() _NOEXCEPT
    {
        --__i;
        return *this;
    }
    __wrap_iter  operator--(int) _NOEXCEPT {__wrap_iter __tmp(*this); --(*this); return __tmp;}
    __wrap_iter  operator+ (difference_type __n) const _NOEXCEPT {__wrap_iter __w(*this); __w += __n; return __w;}
    __wrap_iter& operator+=(difference_type __n) _NOEXCEPT
    {
        __i += __n;
        return *this;
    }
    __wrap_iter  operator- (difference_type __n) const _NOEXCEPT {return *this + (-__n);}
    __wrap_iter& operator-=(difference_type __n) _NOEXCEPT {*this += -__n; return *this;}
     reference    operator[](difference_type __n) const _NOEXCEPT {return __i[__n];}

     iterator_type base() const _NOEXCEPT {return __i;}

private:

     __wrap_iter(iterator_type __x) _NOEXCEPT : __i(__x) {}

    template <class _Up> friend class __wrap_iter;
    template <class _CharT, class _Traits, class _Alloc> friend class basic_string;
    template <class _Tp, class _Alloc> friend class _LIBCPP_TEMPLATE_VIS vector;
    template <class _Tp, size_t> friend class _LIBCPP_TEMPLATE_VIS span;

    template <class _Iter1, class _Iter2>
    friend bool operator==(const __wrap_iter<_Iter1>&, const __wrap_iter<_Iter2>&) _NOEXCEPT
    {return __x.base() == __y.base();}
    
    template <class _Iter1, class _Iter2>
    friend bool operator<(const __wrap_iter<_Iter1>&, const __wrap_iter<_Iter2>&) _NOEXCEPT
    {return __x.base() < __y.base();}
    
    template <class _Iter1, class _Iter2>
    friend bool operator!=(const __wrap_iter<_Iter1>&, const __wrap_iter<_Iter2>&) _NOEXCEPT
    {return !(__x == __y);}
    
    template <class _Iter1, class _Iter2>
    friend bool operator>(const __wrap_iter<_Iter1>&, const __wrap_iter<_Iter2>&) _NOEXCEPT
    {return __y < __x;}
    
    template <class _Iter1, class _Iter2>
    friend bool operator>=(const __wrap_iter<_Iter1>&, const __wrap_iter<_Iter2>&) _NOEXCEPT
    {return !(__x < __y);}

    template <class _Iter1, class _Iter2>
    friend bool operator<=(const __wrap_iter<_Iter1>&, const __wrap_iter<_Iter2>&) _NOEXCEPT
    {return !(__y < __x);}

    template <class _Iter1, class _Iter2>
    friend typename __wrap_iter<_Iter1>::difference_type   operator-(const __wrap_iter<_Iter1>&, const __wrap_iter<_Iter2>&) _NOEXCEPT;


    template <class _Iter1>
    friend __wrap_iter<_Iter1> operator+(typename __wrap_iter<_Iter1>::difference_type, __wrap_iter<_Iter1>) _NOEXCEPT;

    template <class _Ip, class _Op> friend _LIBCPP_CONSTEXPR_AFTER_CXX17 _Op copy(_Ip, _Ip, _Op);
    template <class _B1, class _B2> friend _LIBCPP_CONSTEXPR_AFTER_CXX17 _B2 copy_backward(_B1, _B1, _B2);
    template <class _Ip, class _Op> friend _Op move(_Ip, _Ip, _Op);
    template <class _B1, class _B2> friend _B2 move_backward(_B1, _B1, _B2);

    template <class _Tp>
    friend typename enable_if <is_trivially_copy_assignable<_Tp>::value, _Tp*>::type
    __unwrap_iter(__wrap_iter<_Tp*>);

};


template <class _Iter1>
inline  
bool
operator!=(const __wrap_iter<_Iter1>& __x, const __wrap_iter<_Iter1>& __y) _NOEXCEPT
{
    return !(__x == __y);
}

template <class _Iter1>
inline  
bool
operator>(const __wrap_iter<_Iter1>& __x, const __wrap_iter<_Iter1>& __y) _NOEXCEPT
{
    return __y < __x;
}

template <class _Iter1>
inline  
bool
operator>=(const __wrap_iter<_Iter1>& __x, const __wrap_iter<_Iter1>& __y) _NOEXCEPT
{
    return !(__x < __y);
}

template <class _Iter1>
inline  
bool
operator<=(const __wrap_iter<_Iter1>& __x, const __wrap_iter<_Iter1>& __y) _NOEXCEPT
{
    return !(__y < __x);
}

template <class _Iter1, class _Iter2>
inline  
typename __wrap_iter<_Iter1>::difference_type
operator-(const __wrap_iter<_Iter1>& __x, const __wrap_iter<_Iter2>& __y) _NOEXCEPT
{
    return __x.base() - __y.base();
}

template <class _Iter>
inline  
__wrap_iter<_Iter>
operator+(typename __wrap_iter<_Iter>::difference_type __n,
          __wrap_iter<_Iter> __x) _NOEXCEPT
{
    __x += __n;
    return __x;
}

template <class _Iter>
struct __libcpp_is_trivial_iterator
    : public _LIBCPP_BOOL_CONSTANT(is_pointer<_Iter>::value) {};

template <class _Iter>
struct __libcpp_is_trivial_iterator<move_iterator<_Iter> >
    : public _LIBCPP_BOOL_CONSTANT(__libcpp_is_trivial_iterator<_Iter>::value) {};

template <class _Iter>
struct __libcpp_is_trivial_iterator<reverse_iterator<_Iter> >
    : public _LIBCPP_BOOL_CONSTANT(__libcpp_is_trivial_iterator<_Iter>::value) {};

template <class _Iter>
struct __libcpp_is_trivial_iterator<__wrap_iter<_Iter> >
    : public _LIBCPP_BOOL_CONSTANT(__libcpp_is_trivial_iterator<_Iter>::value) {};


template <class _Tp, size_t _Np>
 _LIBCPP_CONSTEXPR_AFTER_CXX11
_Tp*
begin(_Tp (&__array)[_Np])
{
    return __array;
}

template <class _Tp, size_t _Np>
 _LIBCPP_CONSTEXPR_AFTER_CXX11
_Tp*
end(_Tp (&__array)[_Np])
{
    return __array + _Np;
}

_LIBCPP_BEGIN_NAMESPACE_STD
template <class _Iter>
struct _LIBCPP_TEMPLATE_VIS iterator_traits;

struct _LIBCPP_TEMPLATE_VIS input_iterator_tag {};
struct _LIBCPP_TEMPLATE_VIS output_iterator_tag {};
struct _LIBCPP_TEMPLATE_VIS forward_iterator_tag       : public input_iterator_tag {};
struct _LIBCPP_TEMPLATE_VIS bidirectional_iterator_tag : public forward_iterator_tag {};
struct _LIBCPP_TEMPLATE_VIS random_access_iterator_tag : public bidirectional_iterator_tag {};

template <class _Iter>
struct __iter_traits_cache {
  using type = _If< __is_primary_template<iterator_traits<_Iter> >::value, _Iter, iterator_traits<_Iter>>;
};

template <class _Iter>
using _ITER_TRAITS = typename __iter_traits_cache<_Iter>::type;

struct __iter_concept_concept_test {
  template <class _Iter>
  using _Apply = typename _ITER_TRAITS<_Iter>::iterator_concept;
};

struct __iter_concept_category_test {
  template <class _Iter>
  using _Apply = typename _ITER_TRAITS<_Iter>::iterator_category;
};

struct __iter_concept_random_fallback {
  template <class _Iter>
  using _Apply = _EnableIf< __is_primary_template<iterator_traits<_Iter> >::value, random_access_iterator_tag>;
};

    template <class _Iter, class _Tester> struct __test_iter_concept
    : _IsValidExpansion<_Tester::template _Apply, _Iter>,
        _Tester
    {};

    template <class _Iter>
    struct __iter_concept_cache {
    using type = _Or< __test_iter_concept<_Iter, __iter_concept_concept_test>, __test_iter_concept<_Iter, __iter_concept_category_test>, __test_iter_concept<_Iter, __iter_concept_random_fallback>>;
};

template <class _Iter>
using _ITER_CONCEPT = typename __iter_concept_cache<_Iter>::type::template _Apply<_Iter>;


template <class _Tp>
struct __has_iterator_typedefs
{
private:
    struct __two {char __lx; char __lxx;};
    template <class _Up> static __two __test(...);
    template <class _Up> static char __test(typename std::__void_t<typename _Up::iterator_category>::type* = 0,
    										typename std::__void_t<typename _Up::difference_type>::type* = 0,
    										typename std::__void_t<typename _Up::value_type>::type* = 0,
    										typename std::__void_t<typename _Up::reference>::type* = 0,
    										typename std::__void_t<typename _Up::pointer>::type* = 0
    										);
public:
    static const bool value = sizeof(__test<_Tp>(0,0,0,0,0)) == 1;
};


template <class _Tp>
struct __has_iterator_category
{
private:
    struct __two {char __lx; char __lxx;};
    template <class _Up> static __two __test(...);
    template <class _Up> static char __test(typename _Up::iterator_category* = 0);
public:
    static const bool value = sizeof(__test<_Tp>(0)) == 1;
};

template <class _Iter, bool> struct __iterator_traits_impl {};

template <class _Iter>
struct __iterator_traits_impl<_Iter, true>
{
    typedef typename _Iter::difference_type   difference_type;
    typedef typename _Iter::value_type        value_type;
    typedef typename _Iter::pointer           pointer;
    typedef typename _Iter::reference         reference;
    typedef typename _Iter::iterator_category iterator_category;
};

template <class _Iter, bool> struct __iterator_traits {};

template <class _Iter>
struct __iterator_traits<_Iter, true>
    :  __iterator_traits_impl <_Iter, is_convertible<typename _Iter::iterator_category, input_iterator_tag>::value || is_convertible<typename _Iter::iterator_category, output_iterator_tag>::value>
{};

// iterator_traits<Iterator> will only have the nested types if Iterator::iterator_category
//    exists.  Else iterator_traits<Iterator> will be an empty class.  This is a
//    conforming extension which allows some programs to compile and behave as
//    the client expects instead of failing at compile time.

template <class _Iter>
struct _LIBCPP_TEMPLATE_VIS iterator_traits
    : __iterator_traits<_Iter, __has_iterator_typedefs<_Iter>::value> {
  using __primary_template = iterator_traits;
};

template<class _Tp>
struct _LIBCPP_TEMPLATE_VIS iterator_traits<_Tp*>
{
    typedef ptrdiff_t difference_type;
    typedef typename remove_cv<_Tp>::type value_type;
    typedef _Tp* pointer;
    typedef _Tp& reference;
    typedef random_access_iterator_tag iterator_category;
};

template <class _Tp, class _Up, bool = __has_iterator_category<iterator_traits<_Tp> >::value>
struct __has_iterator_category_convertible_to
    : public integral_constant<bool, is_convertible<typename iterator_traits<_Tp>::iterator_category, _Up>::value>
{};

template <class _Tp, class _Up>
struct __has_iterator_category_convertible_to<_Tp, _Up, false> : public false_type {};

template <class _Tp>
struct __is_cpp17_input_iterator : public __has_iterator_category_convertible_to<_Tp, input_iterator_tag> {};

template <class _Tp>
struct __is_cpp17_forward_iterator : public __has_iterator_category_convertible_to<_Tp, forward_iterator_tag> {};

template <class _Tp>
struct __is_cpp17_bidirectional_iterator : public __has_iterator_category_convertible_to<_Tp, bidirectional_iterator_tag> {};

template <class _Tp>
struct __is_cpp17_random_access_iterator : public __has_iterator_category_convertible_to<_Tp, random_access_iterator_tag> {};

template <class _Tp>
struct __is_cpp17_contiguous_iterator : public false_type {};

template <class _Tp>
struct __is_exactly_cpp17_input_iterator
    : public integral_constant<bool, __has_iterator_category_convertible_to<_Tp, input_iterator_tag>::value && !__has_iterator_category_convertible_to<_Tp, forward_iterator_tag>::value> 
{};


template<class _Category, class _Tp, class _Distance = ptrdiff_t,
         class _Pointer = _Tp*, class _Reference = _Tp&>
struct iterator
{
    typedef _Tp        value_type;
    typedef _Distance  difference_type;
    typedef _Pointer   pointer;
    typedef _Reference reference;
    typedef _Category  iterator_category;
};

template <class _InputIter>
void __advance(_InputIter& __i, typename iterator_traits<_InputIter>::difference_type __n, input_iterator_tag)
{
    for (; __n > 0; --__n)
        ++__i;
}

template <class _BiDirIter>
void __advance(_BiDirIter& __i, typename iterator_traits<_BiDirIter>::difference_type __n, bidirectional_iterator_tag)
{
    if (__n >= 0)
        for (; __n > 0; --__n)
            ++__i;
    else
        for (; __n < 0; ++__n)
            --__i;
}

template <class _RandIter>
void __advance(_RandIter& __i, typename iterator_traits<_RandIter>::difference_type __n, random_access_iterator_tag)
{
   __i += __n;
}

template <class _InputIter>
void advance(_InputIter& __i, typename iterator_traits<_InputIter>::difference_type __n)
{
    _LIBCPP_ASSERT(__n >= 0 || __is_cpp17_bidirectional_iterator<_InputIter>::value,
                       "Attempt to advance(it, -n) on a non-bidi iterator");
    __advance(__i, __n, typename iterator_traits<_InputIter>::iterator_category());
}

template <class _InputIter>
typename iterator_traits<_InputIter>::difference_type   __distance(_InputIter __first, _InputIter __last, input_iterator_tag)
{
    typename iterator_traits<_InputIter>::difference_type __r(0);
    for (; __first != __last; ++__first)
        ++__r;
    return __r;
}

template <class _RandIter>
typename iterator_traits<_RandIter>::difference_type    __distance(_RandIter __first, _RandIter __last, random_access_iterator_tag)
{
    return __last - __first;
}

template <class _InputIter>
typename iterator_traits<_InputIter>::difference_type   distance(_InputIter __first, _InputIter __last)
{
    return __distance(__first, __last, typename iterator_traits<_InputIter>::iterator_category());
}

template <class _InputIter>
typename enable_if <__is_cpp17_input_iterator<_InputIter>::value, _InputIter>::type next(_InputIter __x, typename iterator_traits<_InputIter>::difference_type __n = 1)
{
    _LIBCPP_ASSERT(__n >= 0 || __is_cpp17_bidirectional_iterator<_InputIter>::value,
                       "Attempt to next(it, -n) on a non-bidi iterator");

    _VSTD::advance(__x, __n);
    return __x;
}

template <class _InputIter>
typename enable_if
< __is_cpp17_input_iterator<_InputIter>::value, _InputIter >::type prev(_InputIter __x, typename iterator_traits<_InputIter>::difference_type __n = 1)
{
    _LIBCPP_ASSERT(__n <= 0 || __is_cpp17_bidirectional_iterator<_InputIter>::value,
                       "Attempt to prev(it, +n) on a non-bidi iterator");
    _VSTD::advance(__x, -__n);
    return __x;
}


template <class _Tp, class = void>
struct __is_stashing_iterator : false_type {};

template <class _Tp>
struct __is_stashing_iterator<_Tp, typename __void_t<typename _Tp::__stashing_iterator_tag>::type>
  : true_type {};

template <class _Iter>
class _LIBCPP_TEMPLATE_VIS reverse_iterator
    : public iterator<typename iterator_traits<_Iter>::iterator_category, typename iterator_traits<_Iter>::value_type,
                      typename iterator_traits<_Iter>::difference_type, typename iterator_traits<_Iter>::pointer,
                      typename iterator_traits<_Iter>::reference>
{

private:
    /*mutable*/ _Iter __t;  // no longer used as of LWG #2360, not removed due to ABI break

    static_assert(!__is_stashing_iterator<_Iter>::value,
      "The specified iterator type cannot be used with reverse_iterator; "
      "Using stashing iterators with reverse_iterator causes undefined behavior");

protected:
    _Iter current;

public:
    typedef _Iter                                            iterator_type;
    typedef typename iterator_traits<_Iter>::difference_type difference_type;
    typedef typename iterator_traits<_Iter>::reference       reference;
    typedef typename iterator_traits<_Iter>::pointer         pointer;

    reverse_iterator() : __t(), current() {}
    explicit reverse_iterator(_Iter __x) 
        : __t(__x), current(__x) {}
    
    template <class _Up> 
    reverse_iterator(const reverse_iterator<_Up>& __u) 
        : __t(__u.base()), current(__u.base()) {}
    
    template <class _Up> 
    reverse_iterator& operator=(const reverse_iterator<_Up>& __u)
            { __t = current = __u.base(); return *this; }
    
    _Iter base() const 
    {return current;}
    
    reference operator*() const 
    {_Iter __tmp = current; return *--__tmp;}
    
    pointer  operator->() const 
    {return _VSTD::addressof(operator*());}
    
    reverse_iterator& operator++()
    {--current; return *this;}
    
    reverse_iterator  operator++(int) 
    {reverse_iterator __tmp(*this); --current; return __tmp;}
    
    reverse_iterator& operator--() 
    {++current; return *this;}
    
    reverse_iterator  operator--(int) 
    {reverse_iterator __tmp(*this); ++current; return __tmp;}
    
    reverse_iterator  operator+ (difference_type __n) const 
    {return reverse_iterator(current - __n);}
    
    reverse_iterator& operator+=(difference_type __n) 
    {current -= __n; return *this;}
    
    reverse_iterator  operator- (difference_type __n) const 
    {return reverse_iterator(current + __n);}
    
    reverse_iterator& operator-=(difference_type __n) 
    {current += __n; return *this;}
    
    reference         operator[](difference_type __n) const 
    {return *(*this + __n);}
};

template <class _Iter1, class _Iter2>
bool    operator==(const reverse_iterator<_Iter1> __x, const reverse_iterator<_Iter2>& __y)
{
    return __x.base() == __y.base();
}

template <class _Iter1, class _Iter2>
bool    operator<(const reverse_iterator<_Iter1>& __x, const reverse_iterator<_Iter2>& __y)
{
    return __x.base() > __y.base();
}

template <class _Iter1, class _Iter2>
bool    operator!=(const reverse_iterator<_Iter1>& __x, const reverse_iterator<_Iter2>& __y)
{
    return __x.base() != __y.base();
}

template <class _Iter1, class _Iter2>
bool    operator>(const reverse_iterator<_Iter1>& __x, const reverse_iterator<_Iter2>& __y)
{
    return __x.base() < __y.base();
}

template <class _Iter1, class _Iter2>
bool    operator>=(const reverse_iterator<_Iter1>& __x, const reverse_iterator<_Iter2>& __y)
{
    return __x.base() <= __y.base();
}

template <class _Iter1, class _Iter2>
bool    operator<=(const reverse_iterator<_Iter1>& __x, const reverse_iterator<_Iter2>& __y)
{
    return __x.base() >= __y.base();
}


template <class _Iter1, class _Iter2>
typename reverse_iterator<_Iter1>::difference_type  operator-(const reverse_iterator<_Iter1>& __x, const reverse_iterator<_Iter2>& __y)
{
    return __y.base() - __x.base();
}

template <class _Iter>
reverse_iterator<_Iter> operator+(typename reverse_iterator<_Iter>::difference_type __n, const reverse_iterator<_Iter>& __x)
{
    return reverse_iterator<_Iter>(__x.base() - __n);
}

template <class _Container>
class _LIBCPP_TEMPLATE_VIS back_insert_iterator
    : public iterator<output_iterator_tag, void, void, void, void>
{
protected:
    _Container* container;
public:
    typedef _Container container_type;

    explicit back_insert_iterator(_Container& __x) : container(_VSTD::addressof(__x)) {}
    back_insert_iterator& operator=(const typename _Container::value_type& __value_)
        {container->push_back(__value_); return *this;}
    back_insert_iterator& operator*()     {return *this;}
    back_insert_iterator& operator++()    {return *this;}
    back_insert_iterator  operator++(int) {return *this;}
};

template <class _Container>
back_insert_iterator<_Container>    back_inserter(_Container& __x)
{
    return back_insert_iterator<_Container>(__x);
}

template <class _Container>
class _LIBCPP_TEMPLATE_VIS front_insert_iterator
    : public iterator<output_iterator_tag, void, void, void, void>
{
protected:
    _Container* container;
public:
    typedef _Container container_type;

    explicit front_insert_iterator(_Container& __x) : container(_VSTD::addressof(__x)) {}
    front_insert_iterator& operator=(const typename _Container::value_type& __value_)
        {container->push_front(__value_); return *this;}
    front_insert_iterator& operator*()     {return *this;}
    front_insert_iterator& operator++()    {return *this;}
    front_insert_iterator  operator++(int) {return *this;}
};

template <class _Container>
front_insert_iterator<_Container>   front_inserter(_Container& __x)
{
    return front_insert_iterator<_Container>(__x);
}

template <class _Container>
class _LIBCPP_TEMPLATE_VIS insert_iterator
    : public iterator<output_iterator_tag, void, void, void, void>
{
protected:
    _Container* container;
    typename _Container::iterator iter;
public:
    typedef _Container container_type;

    insert_iterator(_Container& __x, typename _Container::iterator __i)
        : container(_VSTD::addressof(__x)), iter(__i) {}
    insert_iterator& operator=(const typename _Container::value_type& __value_)
        {iter = container->insert(iter, __value_); ++iter; return *this;}
    insert_iterator& operator*()        {return *this;}
    insert_iterator& operator++()       {return *this;}
    insert_iterator& operator++(int)    {return *this;}
};

template <class _Container>
insert_iterator<_Container> inserter(_Container& __x, typename _Container::iterator __i)
{
    return insert_iterator<_Container>(__x, __i);
}

template <class _Tp, class _CharT = char,
          class _Traits = char_traits<_CharT>, class _Distance = ptrdiff_t>
class _LIBCPP_TEMPLATE_VIS istream_iterator
    : public iterator<input_iterator_tag, _Tp, _Distance, const _Tp*, const _Tp&>
{
public:
    typedef _CharT char_type;
    typedef _Traits traits_type;
    typedef basic_istream<_CharT,_Traits> istream_type;
private:
    istream_type* __in_stream_;
    _Tp __value_;
public:
    istream_iterator() : __in_stream_(0), __value_() {}
    istream_iterator(istream_type& __s) : __in_stream_(_VSTD::addressof(__s))
    {
        if (!(*__in_stream_ >> __value_))
            __in_stream_ = 0;
    }

    const _Tp& operator*() const {return __value_;}
    const _Tp* operator->() const {return _VSTD::addressof((operator*()));}
    istream_iterator& operator++()
    {
        if (!(*__in_stream_ >> __value_))
            __in_stream_ = 0;
        return *this;
    }
    
    istream_iterator  operator++(int)
    {istream_iterator __t(*this); ++(*this); return __t;}

    template <class _Up, class _CharU, class _TraitsU, class _DistanceU>
    friend     bool operator==(const istream_iterator<_Up, _CharU, _TraitsU, _DistanceU>& __x,
               const istream_iterator<_Up, _CharU, _TraitsU, _DistanceU>& __y);

    template <class _Up, class _CharU, class _TraitsU, class _DistanceU>
    friend     bool operator==(const istream_iterator<_Up, _CharU, _TraitsU, _DistanceU>& __x,
               const istream_iterator<_Up, _CharU, _TraitsU, _DistanceU>& __y);
};

template <class _Tp, class _CharT, class _Traits, class _Distance>
bool    operator==(const istream_iterator<_Tp, _CharT, _Traits, _Distance>& __x,
           const istream_iterator<_Tp, _CharT, _Traits, _Distance>& __y)
{
    return __x.__in_stream_ == __y.__in_stream_;
}

template <class _Tp, class _CharT, class _Traits, class _Distance>
bool    operator!=(const istream_iterator<_Tp, _CharT, _Traits, _Distance>& __x,
           const istream_iterator<_Tp, _CharT, _Traits, _Distance>& __y)
{
    return !(__x == __y);
}

template <class _Tp, class _CharT = char, class _Traits = char_traits<_CharT> >
class _LIBCPP_TEMPLATE_VIS ostream_iterator
    : public iterator<output_iterator_tag, void, void, void, void>
{
public:
    typedef _CharT char_type;
    typedef _Traits traits_type;
    typedef basic_ostream<_CharT,_Traits> ostream_type;
private:
    ostream_type* __out_stream_;
    const char_type* __delim_;
public:
    ostream_iterator(ostream_type& __s) _NOEXCEPT
        : __out_stream_(_VSTD::addressof(__s)), __delim_(0) {}
    ostream_iterator(ostream_type& __s, const _CharT* __delimiter) _NOEXCEPT
        : __out_stream_(_VSTD::addressof(__s)), __delim_(__delimiter) {}
    ostream_iterator& operator=(const _Tp& __value_)
        {
            *__out_stream_ << __value_;
            if (__delim_)
                *__out_stream_ << __delim_;
            return *this;
        }

    ostream_iterator& operator*()     {return *this;}
    ostream_iterator& operator++()    {return *this;}
    ostream_iterator& operator++(int) {return *this;}
};

template<class _CharT, class _Traits>
class _LIBCPP_TEMPLATE_VIS istreambuf_iterator
    : public iterator<input_iterator_tag, _CharT,
                      typename _Traits::off_type, _CharT*,
                      _CharT>
{
public:
    typedef _CharT                          char_type;
    typedef _Traits                         traits_type;
    typedef typename _Traits::int_type      int_type;
    typedef basic_streambuf<_CharT,_Traits> streambuf_type;
    typedef basic_istream<_CharT,_Traits>   istream_type;
private:
    mutable streambuf_type* __sbuf_;

    class __proxy
    {
        char_type __keep_;
        streambuf_type* __sbuf_;
        __proxy(char_type __c, streambuf_type* __s)
            : __keep_(__c), __sbuf_(__s) {}
        friend class istreambuf_iterator;
    public:
        char_type operator*() const {return __keep_;}
    };

    bool __test_for_eof() const
    {
        if (__sbuf_ && traits_type::eq_int_type(__sbuf_->sgetc(), traits_type::eof()))
            __sbuf_ = 0;
        return __sbuf_ == 0;
    }
public:
    istreambuf_iterator() _NOEXCEPT : __sbuf_(0) {}
    istreambuf_iterator(istream_type& __s) _NOEXCEPT
        : __sbuf_(__s.rdbuf()) {}
    istreambuf_iterator(streambuf_type* __s) _NOEXCEPT
        : __sbuf_(__s) {}
    istreambuf_iterator(const __proxy& __p) _NOEXCEPT
        : __sbuf_(__p.__sbuf_) {}

    char_type  operator*() const
    {return static_cast<char_type>(__sbuf_->sgetc());}
    istreambuf_iterator& operator++()
    {
        __sbuf_->sbumpc();
        return *this;
    }
    __proxy              operator++(int)
    {
        return __proxy(__sbuf_->sbumpc(), __sbuf_);
    }

    bool equal(const istreambuf_iterator& __b) const
        {return __test_for_eof() == __b.__test_for_eof();}
};

template <class _CharT, class _Traits>
bool operator==(const istreambuf_iterator<_CharT,_Traits>& __a, const istreambuf_iterator<_CharT,_Traits>& __b)
                {return __a.equal(__b);}

template <class _CharT, class _Traits>
bool operator!=(const istreambuf_iterator<_CharT,_Traits>& __a, const istreambuf_iterator<_CharT,_Traits>& __b)
                {return !__a.equal(__b);}

template <class _CharT, class _Traits>
class ostreambuf_iterator
    : public iterator<output_iterator_tag, void, void, void, void>
{
public:
    typedef _CharT                          char_type;
    typedef _Traits                         traits_type;
    typedef basic_streambuf<_CharT,_Traits> streambuf_type;
    typedef basic_ostream<_CharT,_Traits>   ostream_type;
private:
    streambuf_type* __sbuf_;
public:
    ostreambuf_iterator(ostream_type& __s) _NOEXCEPT
        : __sbuf_(__s.rdbuf()) {}
    
    ostreambuf_iterator(streambuf_type* __s) _NOEXCEPT
        : __sbuf_(__s) {}
    
    ostreambuf_iterator& operator=(_CharT __c)
    {
        if (__sbuf_ && traits_type::eq_int_type(__sbuf_->sputc(__c), traits_type::eof()))
            __sbuf_ = 0;
        return *this;
    }

    ostreambuf_iterator& operator*()     {return *this;}
    ostreambuf_iterator& operator++()    {return *this;}
    ostreambuf_iterator& operator++(int) {return *this;}
    
    bool failed() const _NOEXCEPT {return __sbuf_ == 0;}

    template <class _Ch, class _Tr>
    friend  ostreambuf_iterator<_Ch, _Tr>   __pad_and_output(ostreambuf_iterator<_Ch, _Tr> __s,
                     const _Ch* __ob, const _Ch* __op, const _Ch* __oe,
                     ios_base& __iob, _Ch __fl);
};

template <class _Iter>
class move_iterator
{
private:
    _Iter __i;
public:
    typedef _Iter                                            iterator_type;
    typedef typename iterator_traits<iterator_type>::iterator_category iterator_category;
    typedef typename iterator_traits<iterator_type>::value_type value_type;
    typedef typename iterator_traits<iterator_type>::difference_type difference_type;
    typedef iterator_type pointer;
    typedef typename iterator_traits<iterator_type>::reference reference;

    move_iterator() : __i() {}
    explicit move_iterator(_Iter __x) : __i(__x) {}
    
    template <class _Up>
    move_iterator(const move_iterator<_Up>& __u) : __i(__u.base()) {}
    
    _Iter base() const {return __i;}
    reference operator*() const { return static_cast<reference>(*__i); }
    pointer  operator->() const { return __i;}
    move_iterator& operator++() {++__i; return *this;}
    move_iterator  operator++(int) {move_iterator __tmp(*this); ++__i; return __tmp;}
    move_iterator& operator--() {--__i; return *this;}
    move_iterator  operator--(int) {move_iterator __tmp(*this); --__i; return __tmp;}
    move_iterator  operator+ (difference_type __n) const {return move_iterator(__i + __n);}
    move_iterator& operator+=(difference_type __n) {__i += __n; return *this;}
    move_iterator  operator- (difference_type __n) const {return move_iterator(__i - __n);}
    move_iterator& operator-=(difference_type __n) {__i -= __n; return *this;}
    reference operator[](difference_type __n) const { return static_cast<reference>(__i[__n]); }
};

template <class _Iter1, class _Iter2>
bool    operator==(const move_iterator<_Iter1>& __x, const move_iterator<_Iter2>& __y)
{
    return __x.base() == __y.base();
}

template <class _Iter1, class _Iter2>
bool    operator<(const move_iterator<_Iter1>& __x, const move_iterator<_Iter2>& __y)
{
    return __x.base() < __y.base();
}

template <class _Iter1, class _Iter2>
bool    operator!=(const move_iterator<_Iter1>& __x, const move_iterator<_Iter2>& __y)
{
    return __x.base() != __y.base();
}

template <class _Iter1, class _Iter2>
bool    operator>(const move_iterator<_Iter1>& __x, const move_iterator<_Iter2>& __y)
{
    return __x.base() > __y.base();
}

template <class _Iter1, class _Iter2>
bool    operator>=(const move_iterator<_Iter1>& __x, const move_iterator<_Iter2>& __y)
{
    return __x.base() >= __y.base();
}

template <class _Iter1, class _Iter2>
bool    operator<=(const move_iterator<_Iter1>& __x, const move_iterator<_Iter2>& __y)
{
    return __x.base() <= __y.base();
}


template <class _Iter1, class _Iter2>
typename move_iterator<_Iter1>::difference_type operator-(const move_iterator<_Iter1>& __x, const move_iterator<_Iter2>& __y)
{
    return __x.base() - __y.base();
}

template <class _Iter>
move_iterator<_Iter>    operator+(typename move_iterator<_Iter>::difference_type __n, const move_iterator<_Iter>& __x)
{
    return move_iterator<_Iter>(__x.base() + __n);
}

template <class _Iter>
move_iterator<_Iter>    make_move_iterator(_Iter __i)
{
    return move_iterator<_Iter>(__i);
}

// __wrap_iter

template <class _Iter> class __wrap_iter;

template <class _Iter1, class _Iter2>
bool    operator==(const __wrap_iter<_Iter1>&, const __wrap_iter<_Iter2>&) _NOEXCEPT;

template <class _Iter1, class _Iter2>
bool    operator<(const __wrap_iter<_Iter1>&, const __wrap_iter<_Iter2>&) _NOEXCEPT;

template <class _Iter1, class _Iter2>
bool    operator!=(const __wrap_iter<_Iter1>&, const __wrap_iter<_Iter2>&) _NOEXCEPT;

template <class _Iter1, class _Iter2>
bool    operator>(const __wrap_iter<_Iter1>&, const __wrap_iter<_Iter2>&) _NOEXCEPT;

template <class _Iter1, class _Iter2>
bool    operator>=(const __wrap_iter<_Iter1>&, const __wrap_iter<_Iter2>&) _NOEXCEPT;

template <class _Iter1, class _Iter2>
bool    operator<=(const __wrap_iter<_Iter1>&, const __wrap_iter<_Iter2>&) _NOEXCEPT;


template <class _Iter1, class _Iter2>
typename __wrap_iter<_Iter1>::difference_type   operator-(const __wrap_iter<_Iter1>&, const __wrap_iter<_Iter2>&) _NOEXCEPT;

template <class _Iter>
__wrap_iter<_Iter>  operator+(typename __wrap_iter<_Iter>::difference_type, __wrap_iter<_Iter>) _NOEXCEPT;

template <class _Ip, class _Op> _Op copy(_Ip, _Ip, _Op);
template <class _B1, class _B2> _B2 copy_backward(_B1, _B1, _B2);
template <class _Ip, class _Op> _Op move(_Ip, _Ip, _Op);
template <class _B1, class _B2> _B2 move_backward(_B1, _B1, _B2);


template <class _Tp>
typename enable_if  <is_trivially_copy_assignable<_Tp>::value, _Tp*>::type  __unwrap_iter(__wrap_iter<_Tp*>);


template <class _Iter> // pointer para a base (T *)
class __wrap_iter
{
public:
    typedef _Iter                                                      iterator_type;
    typedef typename iterator_traits<iterator_type>::iterator_category iterator_category;
    typedef typename iterator_traits<iterator_type>::value_type        value_type;
    typedef typename iterator_traits<iterator_type>::difference_type   difference_type;
    typedef typename iterator_traits<iterator_type>::pointer           pointer;
    typedef typename iterator_traits<iterator_type>::reference         reference;
private:
    iterator_type __i;
public:
    __wrap_iter() _NOEXCEPT
    {}
    template <class _Up>
    __wrap_iter(const __wrap_iter<_Up>& __u, typename enable_if<is_convertible<_Up, iterator_type>::value>::type* = 0) _NOEXCEPT
            : __i(__u.base())
    {}

    reference operator*() const _NOEXCEPT
    {
        return *__i;
    }
    pointer  operator->() const _NOEXCEPT
    {
        return (pointer)_VSTD::addressof(*__i);
    }
    __wrap_iter& operator++() _NOEXCEPT
    {
        ++__i;
        return *this;
    }
    __wrap_iter  operator++(int) _NOEXCEPT
        {__wrap_iter __tmp(*this); ++(*this); return __tmp;}

    __wrap_iter& operator--() _NOEXCEPT
    {
        --__i;
        return *this;
    }
    __wrap_iter  operator--(int) _NOEXCEPT
        {__wrap_iter __tmp(*this); --(*this); return __tmp;}
    __wrap_iter  operator+ (difference_type __n) const _NOEXCEPT
        {__wrap_iter __w(*this); __w += __n; return __w;}
    __wrap_iter& operator+=(difference_type __n) _NOEXCEPT
    {
        __i += __n;
        return *this;
    }
    __wrap_iter  operator- (difference_type __n) const _NOEXCEPT
        {return *this + (-__n);}
    __wrap_iter& operator-=(difference_type __n) _NOEXCEPT
        {*this += -__n; return *this;}
    reference    operator[](difference_type __n) const _NOEXCEPT
    {
        return __i[__n];
    }

 iterator_type base() const _NOEXCEPT {return __i;}

private:
    __wrap_iter(iterator_type __x) _NOEXCEPT : __i(__x) {}

    template <class _Up> friend class __wrap_iter;
    template <class _CharT, class _Traits, class _Alloc> friend class basic_string;
    template <class _Tp, class _Alloc> friend class _LIBCPP_TEMPLATE_VIS vector;
    template <class _Tp, size_t> friend class _LIBCPP_TEMPLATE_VIS span;

    template <class _Iter1, class _Iter2>
    friend  bool    operator==(const __wrap_iter<_Iter1>&, const __wrap_iter<_Iter2>&) _NOEXCEPT;

    template <class _Iter1, class _Iter2>
    friend bool operator<(const __wrap_iter<_Iter1>&, const __wrap_iter<_Iter2>&) _NOEXCEPT;

    template <class _Iter1, class _Iter2>
    friend bool    operator!=(const __wrap_iter<_Iter1>&, const __wrap_iter<_Iter2>&) _NOEXCEPT;

    template <class _Iter1, class _Iter2>
    friend bool operator>(const __wrap_iter<_Iter1>&, const __wrap_iter<_Iter2>&) _NOEXCEPT;

    template <class _Iter1, class _Iter2>
    friend bool operator>=(const __wrap_iter<_Iter1>&, const __wrap_iter<_Iter2>&) _NOEXCEPT;

    template <class _Iter1, class _Iter2>
    friend bool    operator<=(const __wrap_iter<_Iter1>&, const __wrap_iter<_Iter2>&) _NOEXCEPT;

    template <class _Iter1, class _Iter2>
    friend  typename __wrap_iter<_Iter1>::difference_type   operator-(const __wrap_iter<_Iter1>&, const __wrap_iter<_Iter2>&) _NOEXCEPT;

    template <class _Iter1>
    friend __wrap_iter<_Iter1>  operator+(typename __wrap_iter<_Iter1>::difference_type, __wrap_iter<_Iter1>) _NOEXCEPT;

    template <class _Ip, class _Op> friend _Op copy(_Ip, _Ip, _Op);
    template <class _B1, class _B2> friend _B2 copy_backward(_B1, _B1, _B2);
    template <class _Ip, class _Op> friend _Op move(_Ip, _Ip, _Op);
    template <class _B1, class _B2> friend _B2 move_backward(_B1, _B1, _B2);

    template <class _Tp>
    friend  typename enable_if  < is_trivially_copy_assignable<_Tp>::value, _Tp*>::type __unwrap_iter(__wrap_iter<_Tp*>);
};

template <class _Iter1, class _Iter2>
bool    operator==(const __wrap_iter<_Iter1>& __x, const __wrap_iter<_Iter2>& __y) _NOEXCEPT
{
    return __x.base() == __y.base();
}

template <class _Iter1, class _Iter2>
bool    operator<(const __wrap_iter<_Iter1>& __x, const __wrap_iter<_Iter2>& __y) _NOEXCEPT
{
    return __x.base() < __y.base();
}

template <class _Iter1, class _Iter2>
bool    operator!=(const __wrap_iter<_Iter1>& __x, const __wrap_iter<_Iter2>& __y) _NOEXCEPT
{
    return !(__x == __y);
}

template <class _Iter1, class _Iter2>
bool    operator>(const __wrap_iter<_Iter1>& __x, const __wrap_iter<_Iter2>& __y) _NOEXCEPT
{
    return __y < __x;
}

template <class _Iter1, class _Iter2>
bool    operator>=(const __wrap_iter<_Iter1>& __x, const __wrap_iter<_Iter2>& __y) _NOEXCEPT
{
    return !(__x < __y);
}

template <class _Iter1, class _Iter2>
bool    operator<=(const __wrap_iter<_Iter1>& __x, const __wrap_iter<_Iter2>& __y) _NOEXCEPT
{
    return !(__y < __x);
}

template <class _Iter1>
bool    operator!=(const __wrap_iter<_Iter1>& __x, const __wrap_iter<_Iter1>& __y) _NOEXCEPT
{
    return !(__x == __y);
}

template <class _Iter1>
bool    operator>(const __wrap_iter<_Iter1>& __x, const __wrap_iter<_Iter1>& __y) _NOEXCEPT
{
    return __y < __x;
}

template <class _Iter1>
bool    operator>=(const __wrap_iter<_Iter1>& __x, const __wrap_iter<_Iter1>& __y) _NOEXCEPT
{
    return !(__x < __y);
}

template <class _Iter1>
bool    operator<=(const __wrap_iter<_Iter1>& __x, const __wrap_iter<_Iter1>& __y) _NOEXCEPT
{
    return !(__y < __x);
}

template <class _Iter1, class _Iter2>
typename __wrap_iter<_Iter1>::difference_type   operator-(const __wrap_iter<_Iter1>& __x, const __wrap_iter<_Iter2>& __y) _NOEXCEPT
{
    return __x.base() - __y.base();
}

template <class _Iter>
__wrap_iter<_Iter>  operator+(typename __wrap_iter<_Iter>::difference_type __n,
          __wrap_iter<_Iter> __x) _NOEXCEPT
{
    __x += __n;
    return __x;
}

template <class _Iter>
struct __libcpp_is_trivial_iterator
    : public _LIBCPP_BOOL_CONSTANT(is_pointer<_Iter>::value) {};

template <class _Iter>
struct __libcpp_is_trivial_iterator<move_iterator<_Iter> >
    : public _LIBCPP_BOOL_CONSTANT(__libcpp_is_trivial_iterator<_Iter>::value) {};

template <class _Iter>
struct __libcpp_is_trivial_iterator<reverse_iterator<_Iter> >
    : public _LIBCPP_BOOL_CONSTANT(__libcpp_is_trivial_iterator<_Iter>::value) {};

template <class _Iter>
struct __libcpp_is_trivial_iterator<__wrap_iter<_Iter> >
    : public _LIBCPP_BOOL_CONSTANT(__libcpp_is_trivial_iterator<_Iter>::value) {};


template <class _Tp, size_t _Np>
_Tp*    begin(_Tp (&__array)[_Np])
{
    return __array;
}

template <class _Tp, size_t _Np>
_Tp*    end(_Tp (&__array)[_Np])
{
    return __array + _Np;
}

template <class _Cp>
typename _Cp::iterator  begin(_Cp& __c)
{
    return __c.begin();
}

template <class _Cp>
typename _Cp::const_iterator    begin(const _Cp& __c)
{
    return __c.begin();
}

template <class _Cp>
typename _Cp::iterator  end(_Cp& __c)
{
    return __c.end();
}

template <class _Cp>
typename _Cp::const_iterator    end(const _Cp& __c)
{
    return __c.end();
}

_LIBCPP_END_NAMESPACE_STD

#endif  // _LIBCPP_ITERATOR
