// -*- C++ -*-
//===----------------------------- map ------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef _LIBCPP_MAP
#define _LIBCPP_MAP

#include <__config>
#include <__tree>
#include <__node_handle>
#include <iterator>
#include <memory>
#include <utility>
#include <functional>
#include <initializer_list>
#include <type_traits>
#include <__cxx_version>

#if !defined(_LIBCPP_HAS_NO_PRAGMA_SYSTEM_HEADER)
#pragma GCC system_header
#endif


template <class _Key, class _CP, class _Compare,
          bool = is_empty<_Compare>::value && !__libcpp_is_final<_Compare>::value>
class __map_value_compare
    : private _Compare
{
public:
    __map_value_compare()
        _NOEXCEPT_(is_nothrow_default_constructible<_Compare>::value)
        : _Compare() {}
    __map_value_compare(_Compare c)
        _NOEXCEPT_(is_nothrow_copy_constructible<_Compare>::value)
        : _Compare(c) {}
    const _Compare& key_comp() const _NOEXCEPT {return *this;}
    bool operator()(const _CP& __x, const _CP& __y) const
        {return static_cast<const _Compare&>(*this)(__x.__get_value().first, __y.__get_value().first);}
    bool operator()(const _CP& __x, const _Key& __y) const
        {return static_cast<const _Compare&>(*this)(__x.__get_value().first, __y);}
    bool operator()(const _Key& __x, const _CP& __y) const
        {return static_cast<const _Compare&>(*this)(__x, __y.__get_value().first);}
    void swap(__map_value_compare&__y)
        _NOEXCEPT_(__is_nothrow_swappable<_Compare>::value)
    {
      using _VSTD::swap;
      swap(static_cast<_Compare&>(*this), static_cast<_Compare&>(__y));
    }
};

template <class _Key, class _CP, class _Compare>
class __map_value_compare<_Key, _CP, _Compare, false>
{
    _Compare comp;

public:
    __map_value_compare()
        _NOEXCEPT_(is_nothrow_default_constructible<_Compare>::value)
        : comp() {}
    __map_value_compare(_Compare c)
        _NOEXCEPT_(is_nothrow_copy_constructible<_Compare>::value)
        : comp(c) {}
    const _Compare& key_comp() const _NOEXCEPT {return comp;}

    bool operator()(const _CP& __x, const _CP& __y) const
        {return comp(__x.__get_value().first, __y.__get_value().first);}
    bool operator()(const _CP& __x, const _Key& __y) const
        {return comp(__x.__get_value().first, __y);}
    bool operator()(const _Key& __x, const _CP& __y) const
        {return comp(__x, __y.__get_value().first);}
    void swap(__map_value_compare&__y)
        _NOEXCEPT_(__is_nothrow_swappable<_Compare>::value)
    {
        using _VSTD::swap;
        swap(comp, __y.comp);
    }

};

template <class _Key, class _CP, class _Compare, bool __b>
void
swap(__map_value_compare<_Key, _CP, _Compare, __b>& __x,
     __map_value_compare<_Key, _CP, _Compare, __b>& __y)
    _NOEXCEPT_(_NOEXCEPT_(__x.swap(__y)))
{
    __x.swap(__y);
}

template <class _Allocator>
class __map_node_destructor
{
    typedef _Allocator                          allocator_type;
    typedef allocator_traits<allocator_type>    __alloc_traits;

public:
    typedef typename __alloc_traits::pointer    pointer;

private:
    allocator_type& __na_;
    __map_node_destructor& operator=(const __map_node_destructor&);

public:
    bool __first_constructed;
    bool __second_constructed;

    explicit __map_node_destructor(allocator_type& __na) _NOEXCEPT
        : __na_(__na),
          __first_constructed(false),
          __second_constructed(false)
        {}

    void operator()(pointer __p) _NOEXCEPT
    {
        if (__second_constructed)
            __alloc_traits::destroy(__na_, _VSTD::addressof(__p->__value_.__get_value().second));
        if (__first_constructed)
            __alloc_traits::destroy(__na_, _VSTD::addressof(__p->__value_.__get_value().first));
        if (__p)
            __alloc_traits::deallocate(__na_, __p, 1);
    }
};

template <class _Key, class _Tp, class _Compare, class _Allocator>
    class map;
template <class _Key, class _Tp, class _Compare, class _Allocator>
    class multimap;
template <class _TreeIterator> class __map_const_iterator;


template <class _Key, class _Tp>
struct __value_type
{
    typedef _Key                                     key_type;
    typedef _Tp                                      mapped_type;
    typedef pair<const key_type, mapped_type>        value_type;

private:
    value_type __cc;

public:
    value_type& __get_value() { return __cc; }
    const value_type& __get_value() const { return __cc; }

private:
   __value_type();
   __value_type(__value_type const&);
   __value_type& operator=(__value_type const&);
   ~__value_type();
};


template <class _Tp>
struct __extract_key_value_types;

template <class _Key, class _Tp>
struct __extract_key_value_types<__value_type<_Key, _Tp> >
{
  typedef _Key const __key_type;
  typedef _Tp        __mapped_type;
};

template <class _TreeIterator>
class _LIBCPP_TEMPLATE_VIS __map_iterator
{
    typedef typename _TreeIterator::_NodeTypes                   _NodeTypes;
    typedef typename _TreeIterator::__pointer_traits             __pointer_traits;

    _TreeIterator __i_;

public:
    typedef bidirectional_iterator_tag                           iterator_category;
    typedef typename _NodeTypes::__map_value_type                value_type;
    typedef typename _TreeIterator::difference_type              difference_type;
    typedef value_type&                                          reference;
    typedef typename _NodeTypes::__map_value_type_pointer        pointer;

    __map_iterator() _NOEXCEPT {}

    __map_iterator(_TreeIterator __i) _NOEXCEPT : __i_(__i) {}

    reference operator*() const {return __i_->__get_value();}
    pointer operator->() const {return pointer_traits<pointer>::pointer_to(__i_->__get_value());}

    __map_iterator& operator++() {++__i_; return *this;}
    __map_iterator operator++(int)
    {
        __map_iterator __t(*this);
        ++(*this);
        return __t;
    }

    __map_iterator& operator--() {--__i_; return *this;}
    __map_iterator operator--(int)
    {
        __map_iterator __t(*this);
        --(*this);
        return __t;
    }

    bool operator==(const __map_iterator& __x, const __map_iterator& __y)
        {return __x.__i_ == __y.__i_;}
    friend
    bool operator!=(const __map_iterator& __x, const __map_iterator& __y)
        {return __x.__i_ != __y.__i_;}

    template <class, class, class, class> friend class _LIBCPP_TEMPLATE_VIS map;
    template <class, class, class, class> friend class _LIBCPP_TEMPLATE_VIS multimap;
    template <class> friend class _LIBCPP_TEMPLATE_VIS __map_const_iterator;
};

template <class _TreeIterator>
class _LIBCPP_TEMPLATE_VIS __map_const_iterator
{
    typedef typename _TreeIterator::_NodeTypes                   _NodeTypes;
    typedef typename _TreeIterator::__pointer_traits             __pointer_traits;

    _TreeIterator __i_;

public:
    typedef bidirectional_iterator_tag                           iterator_category;
    typedef typename _NodeTypes::__map_value_type                value_type;
    typedef typename _TreeIterator::difference_type              difference_type;
    typedef const value_type&                                    reference;
    typedef typename _NodeTypes::__const_map_value_type_pointer  pointer;

    __map_const_iterator() _NOEXCEPT {}

    __map_const_iterator(_TreeIterator __i) _NOEXCEPT : __i_(__i) {}
    __map_const_iterator(__map_iterator<
        typename _TreeIterator::__non_const_iterator> __i) _NOEXCEPT
        : __i_(__i.__i_) {}

    reference operator*() const {return __i_->__get_value();}
    pointer operator->() const {return pointer_traits<pointer>::pointer_to(__i_->__get_value());}

    __map_const_iterator& operator++() {++__i_; return *this;}
    __map_const_iterator operator++(int)
    {
        __map_const_iterator __t(*this);
        ++(*this);
        return __t;
    }

    __map_const_iterator& operator--() {--__i_; return *this;}
    __map_const_iterator operator--(int)
    {
        __map_const_iterator __t(*this);
        --(*this);
        return __t;
    }

    bool operator==(const __map_const_iterator& __x, const __map_const_iterator& __y)
        {return __x.__i_ == __y.__i_;}
    bool operator!=(const __map_const_iterator& __x, const __map_const_iterator& __y)
        {return __x.__i_ != __y.__i_;}
};

template <class _Key, class _Tp, class _Compare = less<_Key>,
          class _Allocator = allocator<pair<const _Key, _Tp> > >
class _LIBCPP_TEMPLATE_VIS map
{
public:
    // types:
    typedef _Key                                     key_type;
    typedef _Tp                                      mapped_type;
    typedef pair<const key_type, mapped_type>        value_type;
    typedef typename __identity<_Compare>::type      key_compare;
    typedef typename __identity<_Allocator>::type    allocator_type;
    typedef value_type&                              reference;
    typedef const value_type&                        const_reference;

    static_assert((is_same<typename allocator_type::value_type, value_type>::value),
                  "Allocator::value_type must be same type as value_type");

    class _LIBCPP_TEMPLATE_VIS value_compare
        : public binary_function<value_type, value_type, bool>
    {
        friend class map;
    protected:
        key_compare comp;

    public:
        bool operator()(const value_type& __x, const value_type& __y) const
            {return comp(__x.first, __y.first);}
    };

private:

    typedef _VSTD::__value_type<key_type, mapped_type>             __value_type;
    typedef __map_value_compare<key_type, __value_type, key_compare> __vc;
    typedef typename __rebind_alloc_helper<allocator_traits<allocator_type>,
                                                 __value_type>::type __allocator_type;
    typedef __tree<__value_type, __vc, __allocator_type>   __base;
    typedef typename __base::__node_traits                 __node_traits;
    typedef allocator_traits<allocator_type>               __alloc_traits;

    __base __tree_;

public:
    typedef typename __alloc_traits::pointer               pointer;
    typedef typename __alloc_traits::const_pointer         const_pointer;
    typedef typename __alloc_traits::size_type             size_type;
    typedef typename __alloc_traits::difference_type       difference_type;
    typedef __map_iterator<typename __base::iterator>             iterator;
    typedef __map_const_iterator<typename __base::const_iterator> const_iterator;
    typedef _VSTD::reverse_iterator<iterator>               reverse_iterator;
    typedef _VSTD::reverse_iterator<const_iterator>         const_reverse_iterator;

    map() : __tree_(__vc(key_compare())) {}

    explicit map(const key_compare& __comp) : __tree_(__vc(__comp)) {}

    explicit map(const key_compare& __comp, const allocator_type& __a)
        : __tree_(__vc(__comp), typename __base::allocator_type(__a)) {}

    template <class _InputIterator>
    map(_InputIterator __f, _InputIterator __l, const key_compare& __comp = key_compare())
        : __tree_(__vc(__comp))
    {
        insert(__f, __l);
    }

    template <class _InputIterator>
    map(_InputIterator __f, _InputIterator __l, const key_compare& __comp, const allocator_type& __a)
        : __tree_(__vc(__comp), typename __base::allocator_type(__a))
    {
        insert(__f, __l);
    }

    map(const map& __m) : __tree_(__m.__tree_)
    {
        insert(__m.begin(), __m.end());
    }

    map& operator=(const map& __m)
    {

        if (this != &__m) {
            __tree_.clear();
            __tree_.value_comp() = __m.__tree_.value_comp();
            __tree_.__copy_assign_alloc(__m.__tree_);
            insert(__m.begin(), __m.end());
        }
        return *this;
    }


    explicit map(const allocator_type& __a) : __tree_(typename __base::allocator_type(__a)) {}

    map(const map& __m, const allocator_type& __a) : __tree_(__m.__tree_.value_comp(), typename __base::allocator_type(__a))
    {
        insert(__m.begin(), __m.end());
    }

    ~map() {
        static_assert(sizeof(__diagnose_non_const_comparator<_Key, _Compare>()), "");
    }

    iterator begin() {return __tree_.begin();}
    const_iterator begin() const {return __tree_.begin();}
    iterator end() {return __tree_.end();}
    const_iterator end() const {return __tree_.end();}

    reverse_iterator rbegin() {return reverse_iterator(end());}
    const_reverse_iterator rbegin() const {return const_reverse_iterator(end());}
    reverse_iterator rend() {return reverse_iterator(begin());}
    const_reverse_iterator rend() const {return const_reverse_iterator(begin());}

    const_iterator cbegin() const {return begin();}
    const_iterator cend() const {return end();}
    const_reverse_iterator crbegin() const {return rbegin();}
    const_reverse_iterator crend() const {return rend();}

    bool      empty() const {return __tree_.size() == 0;}
    size_type size() const {return __tree_.size();}
    size_type max_size() const {return __tree_.max_size();}

    mapped_type& operator[](const key_type& __k);

    mapped_type& at(const key_type& __k);
    const mapped_type& at(const key_type& __k) const;

    allocator_type get_allocator() const {return allocator_type(__tree_.__alloc());}
    key_compare    key_comp()      const {return __tree_.value_comp().key_comp();}
    value_compare  value_comp()    const {return value_compare(__tree_.value_comp().key_comp());}

    pair<iterator, bool>    insert(const value_type& __v) {return __tree_.__insert_unique(__v);}

    iterator    insert(const_iterator __p, const value_type& __v) {return __tree_.__insert_unique(__p.__i_, __v);}

    template <class _InputIterator>
    void insert(_InputIterator __f, _InputIterator __l)
    {
        for (const_iterator __e = cend(); __f != __l; ++__f)
            insert(__e.__i_, *__f);
    }


    iterator erase(const_iterator __p) {return __tree_.erase(__p.__i_);}
    iterator erase(iterator __p)       {return __tree_.erase(__p.__i_);}
    size_type erase(const key_type& __k) {return __tree_.__erase_unique(__k);}
    iterator  erase(const_iterator __f, const_iterator __l) {return __tree_.erase(__f.__i_, __l.__i_);}
    void clear() {__tree_.clear();}


    void swap(map& __m) {__tree_.swap(__m.__tree_);}

    iterator find(const key_type& __k)             {return __tree_.find(__k);}
    const_iterator find(const key_type& __k) const {return __tree_.find(__k);}

    size_type      count(const key_type& __k) const
        {return __tree_.__count_unique(__k);}

    iterator lower_bound(const key_type& __k)
        {return __tree_.lower_bound(__k);}
    const_iterator lower_bound(const key_type& __k) const
        {return __tree_.lower_bound(__k);}


    iterator upper_bound(const key_type& __k) {return __tree_.upper_bound(__k);}
    const_iterator upper_bound(const key_type& __k) const {return __tree_.upper_bound(__k);}

    pair<iterator,iterator> equal_range(const key_type& __k) {return __tree_.__equal_range_unique(__k);}
    pair<const_iterator,const_iterator> equal_range(const key_type& __k) const {return __tree_.__equal_range_unique(__k);}

private:
    typedef typename __base::__node                    __node;
    typedef typename __base::__node_allocator          __node_allocator;
    typedef typename __base::__node_pointer            __node_pointer;
    typedef typename __base::__node_base_pointer       __node_base_pointer;
    typedef typename __base::__parent_pointer          __parent_pointer;

    typedef __map_node_destructor<__node_allocator> _Dp;
    typedef unique_ptr<__node, _Dp> __node_holder;

};


template <class _Key, class _Tp, class _Compare, class _Allocator>
typename map<_Key, _Tp, _Compare, _Allocator>::__node_holder
map<_Key, _Tp, _Compare, _Allocator>::__construct_node_with_key(const key_type& __k)
{
    __node_allocator& __na = __tree_.__node_alloc();
    __node_holder __h(__node_traits::allocate(__na, 1), _Dp(__na));
    __node_traits::construct(__na, _VSTD::addressof(__h->__value_.__get_value().first), __k);
    __h.get_deleter().__first_constructed = true;
    __node_traits::construct(__na, _VSTD::addressof(__h->__value_.__get_value().second));
    __h.get_deleter().__second_constructed = true;
    return _LIBCPP_EXPLICIT_MOVE(__h);  // explicitly moved for C++03
}

template <class _Key, class _Tp, class _Compare, class _Allocator>
_Tp&    map<_Key, _Tp, _Compare, _Allocator>::operator[](const key_type& __k)
{
    __parent_pointer __parent;
    __node_base_pointer& __child = __tree_.__find_equal(__parent, __k);
    __node_pointer __r = static_cast<__node_pointer>(__child);
    if (__child == nullptr)
    {
        __node_holder __h = __construct_node_with_key(__k);
        __tree_.__insert_node_at(__parent, __child, static_cast<__node_base_pointer>(__h.get()));
        __r = __h.release();
    }
    return __r->__value_.__get_value().second;
}


template <class _Key, class _Tp, class _Compare, class _Allocator>
_Tp&    map<_Key, _Tp, _Compare, _Allocator>::at(const key_type& __k)
{
    __parent_pointer __parent;
    __node_base_pointer& __child = __tree_.__find_equal(__parent, __k);
    if (__child == nullptr)
        __throw_out_of_range("map::at:  key not found");
    return static_cast<__node_pointer>(__child)->__value_.__get_value().second;
}

template <class _Key, class _Tp, class _Compare, class _Allocator>
const _Tp&  map<_Key, _Tp, _Compare, _Allocator>::at(const key_type& __k) const
{
    __parent_pointer __parent;
    __node_base_pointer __child = __tree_.__find_equal(__parent, __k);
    if (__child == nullptr)
        __throw_out_of_range("map::at:  key not found");
    return static_cast<__node_pointer>(__child)->__value_.__get_value().second;
}


template <class _Key, class _Tp, class _Compare, class _Allocator>
bool    operator==(const map<_Key, _Tp, _Compare, _Allocator>& __x, const map<_Key, _Tp, _Compare, _Allocator>& __y)
{
    return __x.size() == __y.size() && _VSTD::equal(__x.begin(), __x.end(), __y.begin());
}

template <class _Key, class _Tp, class _Compare, class _Allocator>
bool    operator< (const map<_Key, _Tp, _Compare, _Allocator>& __x, const map<_Key, _Tp, _Compare, _Allocator>& __y)
{
    return _VSTD::lexicographical_compare(__x.begin(), __x.end(), __y.begin(), __y.end());
}

template <class _Key, class _Tp, class _Compare, class _Allocator>
bool    operator!=(const map<_Key, _Tp, _Compare, _Allocator>& __x, const map<_Key, _Tp, _Compare, _Allocator>& __y)
{
    return !(__x == __y);
}

template <class _Key, class _Tp, class _Compare, class _Allocator>
bool    operator> (const map<_Key, _Tp, _Compare, _Allocator>& __x, const map<_Key, _Tp, _Compare, _Allocator>& __y)
{
    return __y < __x;
}

template <class _Key, class _Tp, class _Compare, class _Allocator>
bool    operator>=(const map<_Key, _Tp, _Compare, _Allocator>& __x, const map<_Key, _Tp, _Compare, _Allocator>& __y)
{
    return !(__x < __y);
}

template <class _Key, class _Tp, class _Compare, class _Allocator>
bool    operator<=(const map<_Key, _Tp, _Compare, _Allocator>& __x, const map<_Key, _Tp, _Compare, _Allocator>& __y)
{
    return !(__y < __x);
}

template <class _Key, class _Tp, class _Compare, class _Allocator>
void    swap(map<_Key, _Tp, _Compare, _Allocator>& __x, map<_Key, _Tp, _Compare, _Allocator>& __y)
{
    __x.swap(__y);
}

#endif  // _LIBCPP_MAP
