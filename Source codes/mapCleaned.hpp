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
using namespace std;

template <class _Key, class _CP, class _Compare,
          bool = is_empty<_Compare>::value && !__libcpp_is_final<_Compare>::value>
class map_compare
    : private _Compare
{
public:
    map_compare() : _Compare() {}
    map_compare(_Compare c) : _Compare(c) {}

    const _Compare& key_comp() const {return *this;}

    bool operator()(const _CP& __x, const _CP& __y) const
        {return static_cast<const _Compare&>(*this)(__x.__get_value().first, __y.__get_value().first);}
    bool operator()(const _CP& __x, const _Key& __y) const
        {return static_cast<const _Compare&>(*this)(__x.__get_value().first, __y);}
    bool operator()(const _Key& __x, const _CP& __y) const
        {return static_cast<const _Compare&>(*this)(__x, __y.__get_value().first);}

    void swap(map_compare&__y)
    {
      using _VSTD::swap;
      swap(static_cast<_Compare&>(*this), static_cast<_Compare&>(__y));
    }
};

template <class _Key, class _CP, class _Compare>
class map_compare<_Key, _CP, _Compare, false>
{
    _Compare comp;

public:
    map_compare() : comp() {}
    map_compare(_Compare c) : comp(c) {}
    const _Compare& key_comp() const {return comp;}

    bool operator()(const _CP& __x, const _CP& __y) const
        {return comp(__x.__get_value().first, __y.__get_value().first);}
    bool operator()(const _CP& __x, const _Key& __y) const
        {return comp(__x.__get_value().first, __y);}
    bool operator()(const _Key& __x, const _CP& __y) const
        {return comp(__x, __y.__get_value().first);}
    
    void swap(map_compare&__y)
    {
        using _VSTD::swap;
        swap(comp, __y.comp);
    }

};

template <class _Key, class _CP, class _Compare, bool __b>
void    swap(map_compare<_Key, _CP, _Compare, __b>& __x,
     map_compare<_Key, _CP, _Compare, __b>& __y)
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

    explicit __map_node_destructor(allocator_type& __na)
        : __na_(__na), __first_constructed(false), __second_constructed(false) {}

    void operator()(pointer __p)
    {
        if (__second_constructed)
            __alloc_traits::destroy(__na_, _VSTD::addressof(__p->__value_.__get_value().second));
        if (__first_constructed)
            __alloc_traits::destroy(__na_, _VSTD::addressof(__p->__value_.__get_value().first));
        if (__p)
            __alloc_traits::deallocate(__na_, __p, 1);
    }
};

template <class _Key, class _Tp>
struct __value_type
{
    typedef _Key                                     key;
    typedef _Tp                                      mapped;
    typedef pair<const key, mapped>        value_type;

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

template <class _Key, class _Tp, class _Compare = less<_Key>,
          class _Allocator = allocator<pair<const _Key, _Tp> > >
class map
{
    public:

        typedef _Key                                                    key;
        typedef _Tp                                                     mapped;
        typedef pair<const key, mapped>                                 value_type;
        typedef typename __identity<_Compare>::type                     key_comp;
        typedef typename __identity<_Allocator>::type                   allocator_type;
        typedef value_type&                                             reference;
        typedef const value_type&                                       const_reference;
        typedef allocator_traits<allocator_type>                        alloc_traits;
        typedef typename alloc_traits::pointer                        pointer;
        typedef typename alloc_traits::const_pointer                  const_pointer;
        typedef typename alloc_traits::size_type                      size_type;
        typedef typename alloc_traits::difference_type                difference_type;
        typedef __map_iterator<typename __base::iterator>               iterator;
        typedef __map_const_iterator<typename __base::const_iterator>   const_it;
        typedef _VSTD::reverse_iterator<iterator>                       reverse_iterator;
        typedef _VSTD::reverse_iterator<const_iterator>                 const_reverse_iterator;

        class value_compare : public binary_function<value_type, value_type, bool>
        {
            friend class map;
            protected:
                key_comp comp;
                value_compare(key_comp c) : comp(c) {}

            public:
                bool operator()(const value_type& __x, const value_type& __y) const
                    {return comp(__x.first, __y.first);}
        };

        map() : _tree(compare(key_comp())) {}

        explicit map(const key_comp& __comp) : _tree(compare(__comp)) {}

        explicit map(const key_comp& __comp, const allocator_type& __a)
            : _tree(compare(__comp), typename __base::allocator_type(__a)) {}

        template <class  inputIt>
        map( inputIt __f,  inputIt __l, const key_comp& __comp, const allocator_type& __a)
            : _tree(compare(__comp), typename __base::allocator_type(__a))
        {
            insert(__f, __l);
        }

        map(const map& __m) : _tree(__m._tree) { insert(__m.begin(), __m.end()); }

        map& operator=(const map& __m)
        {
            if (this != &__m) {
                _tree.clear();
                _tree.value_comp() = __m._tree.value_comp();
                _tree.__copy_assign_alloc(__m._tree);
                insert(__m.begin(), __m.end());
            }
            return *this;
        }

        explicit map(const allocator_type& __a) : _tree(typename __base::allocator_type(__a)) {}

        map(const map& __m, const allocator_type& __a)
            : _tree(__m._tree.value_comp(), typename __base::allocator_type(__a))
        {
            insert(__m.begin(), __m.end());
        }

        ~map() {
            static_assert(sizeof(__diagnose_non_const_comparator<_Key, _Compare>()), "");
        }

        iterator begin() {return _tree.begin();}
        const_it begin() const {return _tree.begin();}
        iterator end() {return _tree.end();}
        const_it end() const {return _tree.end();}

        reverse_iterator rbegin() {return reverse_iterator(end());}
        const_reverse_iterator rbegin() const {return const_reverse_iterator(end());}
        reverse_iterator rend() {return reverse_iterator(begin());}
        const_reverse_iterator rend() const {return const_reverse_iterator(begin());}

        const_it cbegin() const {return begin();}
        const_it cend() const {return end();}
        const_reverse_iterator crbegin() const {return rbegin();}
        const_reverse_iterator crend() const {return rend();}

        bool      empty() const {return _tree.size() == 0;}
        size_type size() const {return _tree.size();}
        size_type max_size() const {return _tree.max_size();}

        mapped& operator[](const key& __k)
        {
            __parent_pointer __parent;
            __node_base_pointer& __child = _tree.__find_equal(__parent, __k);
            __node_pointer __r = static_cast<__node_pointer>(__child);
            if (__child == nullptr)
            {
                __node_holder __h = __construct_node_with_key(__k);
                _tree.__insert_node_at(__parent, __child, static_cast<__node_base_pointer>(__h.get()));
                __r = __h.release();
            }
            return __r->__value_.__get_value().second;
        }

        mapped& at(const key& __k)
        {
            __parent_pointer __parent;
            __node_base_pointer& __child = _tree.__find_equal(__parent, __k);
            if (__child == nullptr)
                __throw_out_of_range("map::at:  key not found");
            return static_cast<__node_pointer>(__child)->__value_.__get_value().second;
        }

        const mapped& at(const key& __k) const
        {
            __parent_pointer __parent;
            __node_base_pointer __child = _tree.__find_equal(__parent, __k);
            if (__child == nullptr)
                __throw_out_of_range("map::at:  key not found");
            return static_cast<__node_pointer>(__child)->__value_.__get_value().second;
        }

        allocator_type get_allocator() const {return allocator_type(_tree.__alloc());}
        key_comp    key_comp() const {return _tree.value_comp().key_comp();}
        value_compare  value_comp() const {return value_compare(_tree.value_comp().key_comp());}

        pair<iterator, bool>    insert(const value_type& __v) {return _tree.__insert_unique(__v);}

        iterator    insert(const_it __p, const value_type& __v) {return _tree.__insert_unique(__p.__i_, __v);}

        template <class _InputIterator>
        void insert(_InputIterator __f, _InputIterator __l)
        {
            for (const_it __e = cend(); __f != __l; ++__f)
                insert(__e.__i_, *__f);
        }

        iterator erase(const_it __p) {return _tree.erase(__p.__i_);}
        iterator erase(iterator __p) {return _tree.erase(__p.__i_);}
        size_type erase(const key& __k) {return _tree.__erase_unique(__k);}
        iterator  erase(const_it __f, const_it __l) {return _tree.erase(__f.__i_, __l.__i_);}

        void clear() {_tree.clear();}

        void swap(map& m) {_tree.swap(m._tree);}

        iterator find(const key& __k) {return _tree.find(__k);}
        const_it find(const key& __k) const {return _tree.find(__k);}

        size_type   count(const key& __k) const {return _tree.__count_unique(__k);}

        iterator lower_bound(const key& __k)   {return _tree.lower_bound(__k);}
        const_it lower_bound(const key& __k) const {return _tree.lower_bound(__k);}

        iterator upper_bound(const key& __k)   {return _tree.upper_bound(__k);}
        const_it upper_bound(const key& __k) const {return _tree.upper_bound(__k);}

        pair<iterator,iterator> equal_range(const key& __k)    {return _tree.__equal_range_unique(__k);}
        pair<const_it,const_it> equal_range(const key& __k) const {return _tree.__equal_range_unique(__k);}

    private:

        typedef _VSTD::__value_type<key, mapped>                __value_type;
        typedef map_compare<key, __value_type, key_comp>        compare;
        typedef allocator                                       allocator_type;
        typedef __tree<__value_type, compare, allocator_type>   bst;
        typedef typename bst::__node_traits                     __node_traits;

        bst _tree;

        typedef typename bst::__node                        __node;
        typedef typename bst::__node_allocator              __node_allocator;
        typedef typename bst::__node_pointer                __node_pointer;
        typedef typename bst::__node_base_pointer           __node_base_pointer;
        typedef typename bst::__parent_pointer              __parent_pointer;
        typedef __map_node_destructor<__node_allocator>     _Dp;
        typedef unique_ptr<__node, _Dp>                     __node_holder;

        __node_holder __construct_node_with_key(const key& __k)
        {
            __node_allocator& __na = _tree.__node_alloc();
            __node_holder __h(__node_traits::allocate(__na, 1), _Dp(__na));
            __node_traits::construct(__na, _VSTD::addressof(__h->__value_.__get_value().first), __k);
            __h.get_deleter().__first_constructed = true;
            __node_traits::construct(__na, _VSTD::addressof(__h->__value_.__get_value().second));
            __h.get_deleter().__second_constructed = true;
            return _LIBCPP_EXPLICIT_MOVE(__h);  // explicitly moved for C++03
        }
};

template <class _Key, class _Tp, class _Compare, class _Allocator>
bool    operator==(const map<_Key, _Tp, _Compare, _Allocator>& __x,
           const map<_Key, _Tp, _Compare, _Allocator>& __y)
{
    return __x.size() == __y.size() && _VSTD::equal(__x.begin(), __x.end(), __y.begin());
}

template <class _Key, class _Tp, class _Compare, class _Allocator>
bool    operator< (const map<_Key, _Tp, _Compare, _Allocator>& __x,
           const map<_Key, _Tp, _Compare, _Allocator>& __y)
{
    return _VSTD::lexicographical_compare(__x.begin(), __x.end(), __y.begin(), __y.end());
}

template <class _Key, class _Tp, class _Compare, class _Allocator>
bool    operator!=(const map<_Key, _Tp, _Compare, _Allocator>& __x,
           const map<_Key, _Tp, _Compare, _Allocator>& __y)
{
    return !(__x == __y);
}

template <class _Key, class _Tp, class _Compare, class _Allocator>
bool    operator> (const map<_Key, _Tp, _Compare, _Allocator>& __x,
           const map<_Key, _Tp, _Compare, _Allocator>& __y)
{
    return __y < __x;
}

template <class _Key, class _Tp, class _Compare, class _Allocator>
bool    operator>=(const map<_Key, _Tp, _Compare, _Allocator>& __x,
           const map<_Key, _Tp, _Compare, _Allocator>& __y)
{
    return !(__x < __y);
}

template <class _Key, class _Tp, class _Compare, class _Allocator>
bool    operator<=(const map<_Key, _Tp, _Compare, _Allocator>& __x,
           const map<_Key, _Tp, _Compare, _Allocator>& __y)
{
    return !(__y < __x);
}

template <class _Key, class _Tp, class _Compare, class _Allocator>
void    swap(map<_Key, _Tp, _Compare, _Allocator>& __x,
     map<_Key, _Tp, _Compare, _Allocator>& __y)
    _NOEXCEPT_(_NOEXCEPT_(__x.swap(__y)))
{
    __x.swap(__y);
}

#endif  // _LIBCPP_MAP
