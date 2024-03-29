
#ifndef _LIBCPP___TREE
#define _LIBCPP___TREE

#include <__config>
#include <iterator>
#include <memory>
#include <stdexcept>
#include <algorithm>
#include <__undef_macros>

#if !defined(_LIBCPP_HAS_NO_PRAGMA_SYSTEM_HEADER)
#pragma GCC system_header
#endif

using namespace std;


template <class _Tp, class _Compare, class _Allocator> class __tree;
template <class _Tp, class _NodePtr, class _DiffType>
    class _LIBCPP_TEMPLATE_VIS __tree_iterator;
template <class _Tp, class _ConstNodePtr, class _DiffType>
    class _LIBCPP_TEMPLATE_VIS __tree_const_iterator;

template <class _Pointer> class __tree_end_node;
template <class _VoidPtr> class __tree_node_base;
template <class _Tp, class _VoidPtr> class __tree_node;

template <class _Key, class _Value>
struct __value_type;

template <class _Allocator> class __map_node_destructor;
template <class _TreeIterator> class _LIBCPP_TEMPLATE_VIS __map_iterator;
template <class _TreeIterator> class _LIBCPP_TEMPLATE_VIS __map_const_iterator;

/*

_NodePtr algorithms

The algorithms taking _NodePtr are red black tree algorithms.  Those
algorithms taking a parameter named __root should assume that __root
points to a proper red black tree (unless otherwise specified).

Each algorithm herein assumes that __root->__parent_ points to a non-null
structure which has a member __left_ which points back to __root.  No other
member is read or written to at __root->__parent_.

__root->__parent_ will be referred to below (in comments only) as end_node.
end_node->__left_ is an externably accessible lvalue for __root, and can be
changed by node insertion and removal (without explicit reference to end_node).

All nodes (with the exception of end_node), even the node referred to as
__root, have a non-null __parent_ field.

*/

// Returns:  true if __x is a left child of its parent, else false
// Precondition:  __x != nullptr.
template <class _NodePtr>
bool    __tree_is_left_child(_NodePtr __x)
{
    return __x == __x->__parent_->__left_;
}

// Returns:  pointer to the left-most node under __x.
// Precondition:  __x != nullptr.
template <class _NodePtr>
_NodePtr    __tree_min(_NodePtr __x)
{
    while (__x->__left_ != nullptr)
        __x = __x->__left_;
    return __x;
}

// Returns:  pointer to the right-most node under __x.
// Precondition:  __x != nullptr.
template <class _NodePtr>
_NodePtr    __tree_max(_NodePtr __x)
{
    while (__x->__right_ != nullptr)
        __x = __x->__right_;
    return __x;
}

// Returns:  pointer to the next in-order node after __x.
// Precondition:  __x != nullptr.
template <class _NodePtr>
_NodePtr    __tree_next(_NodePtr __x)
{
    if (__x->__right_ != nullptr)
        return __tree_min(__x->__right_);
    while (!__tree_is_left_child(__x))
        __x = __x->__parent_unsafe();
    return __x->__parent_unsafe();
}

template <class _EndNodePtr, class _NodePtr>
_EndNodePtr __tree_next_iter(_NodePtr __x)
{
    if (__x->__right_ != nullptr)
        return static_cast<_EndNodePtr>(__tree_min(__x->__right_));
    while (!__tree_is_left_child(__x))
        __x = __x->__parent_unsafe();
    return static_cast<_EndNodePtr>(__x->__parent_);
}

// Returns:  pointer to the previous in-order node before __x.
// Precondition:  __x != nullptr.
// Note: __x may be the end node.
template <class _NodePtr, class _EndNodePtr>
_NodePtr    __tree_prev_iter(_EndNodePtr __x)
{
    if (__x->__left_ != nullptr)
        return __tree_max(__x->__left_);
    _NodePtr __xx = static_cast<_NodePtr>(__x);
    while (__tree_is_left_child(__xx))
        __xx = __xx->__parent_unsafe();
    return __xx->__parent_unsafe();
}

// Returns:  pointer to a node which has no children
// Precondition:  __x != nullptr.
template <class _NodePtr>
_NodePtr    __tree_leaf(_NodePtr __x)
{
    while (true)
    {
        if (__x->__left_ != nullptr)
        {
            __x = __x->__left_;
            continue;
        }
        if (__x->__right_ != nullptr)
        {
            __x = __x->__right_;
            continue;
        }
        break;
    }
    return __x;
}

// Effects:  Makes __x->__right_ the subtree root with __x as its left child
//           while preserving in-order order.
// Precondition:  __x->__right_ != nullptr
template <class _NodePtr>
void    __tree_left_rotate(_NodePtr __x)
{
    _NodePtr __y = __x->__right_;
    __x->__right_ = __y->__left_;
    if (__x->__right_ != nullptr)
        __x->__right_->__set_parent(__x);
    __y->__parent_ = __x->__parent_;
    if (__tree_is_left_child(__x))
        __x->__parent_->__left_ = __y;
    else
        __x->__parent_unsafe()->__right_ = __y;
    __y->__left_ = __x;
    __x->__set_parent(__y);
}

// Effects:  Makes __x->__left_ the subtree root with __x as its right child
//           while preserving in-order order.
// Precondition:  __x->__left_ != nullptr
template <class _NodePtr>
void    __tree_right_rotate(_NodePtr __x)
{
    _NodePtr __y = __x->__left_;
    __x->__left_ = __y->__right_;
    if (__x->__left_ != nullptr)
        __x->__left_->__set_parent(__x);
    __y->__parent_ = __x->__parent_;
    if (__tree_is_left_child(__x))
        __x->__parent_->__left_ = __y;
    else
        __x->__parent_unsafe()->__right_ = __y;
    __y->__right_ = __x;
    __x->__set_parent(__y);
}

// Effects:  Rebalances __root after attaching __x to a leaf.
// Precondition:  __root != nulptr && __x != nullptr.
//                __x has no children.
//                __x == __root or == a direct or indirect child of __root.
//                If __x were to be unlinked from __root (setting __root to
//                  nullptr if __root == __x), __tree_invariant(__root) == true.
// Postcondition: __tree_invariant(end_node->__left_) == true.  end_node->__left_
//                may be different than the value passed in as __root.
template <class _NodePtr>
void    __tree_balance_after_insert(_NodePtr __root, _NodePtr __x)
{
    __x->__is_black_ = __x == __root;
    while (__x != __root && !__x->__parent_unsafe()->__is_black_)
    {
        // __x->__parent_ != __root because __x->__parent_->__is_black == false
        if (__tree_is_left_child(__x->__parent_unsafe()))
        {
            _NodePtr __y = __x->__parent_unsafe()->__parent_unsafe()->__right_;
            if (__y != nullptr && !__y->__is_black_)
            {
                __x = __x->__parent_unsafe();
                __x->__is_black_ = true;
                __x = __x->__parent_unsafe();
                __x->__is_black_ = __x == __root;
                __y->__is_black_ = true;
            }
            else
            {
                if (!__tree_is_left_child(__x))
                {
                    __x = __x->__parent_unsafe();
                    __tree_left_rotate(__x);
                }
                __x = __x->__parent_unsafe();
                __x->__is_black_ = true;
                __x = __x->__parent_unsafe();
                __x->__is_black_ = false;
                __tree_right_rotate(__x);
                break;
            }
        }
        else
        {
            _NodePtr __y = __x->__parent_unsafe()->__parent_->__left_;
            if (__y != nullptr && !__y->__is_black_)
            {
                __x = __x->__parent_unsafe();
                __x->__is_black_ = true;
                __x = __x->__parent_unsafe();
                __x->__is_black_ = __x == __root;
                __y->__is_black_ = true;
            }
            else
            {
                if (__tree_is_left_child(__x))
                {
                    __x = __x->__parent_unsafe();
                    __tree_right_rotate(__x);
                }
                __x = __x->__parent_unsafe();
                __x->__is_black_ = true;
                __x = __x->__parent_unsafe();
                __x->__is_black_ = false;
                __tree_left_rotate(__x);
                break;
            }
        }
    }
}

// Precondition:  __root != nullptr && __z != nullptr.
//                __tree_invariant(__root) == true.
//                __z == __root or == a direct or indirect child of __root.
// Effects:  unlinks __z from the tree rooted at __root, rebalancing as needed.
// Postcondition: __tree_invariant(end_node->__left_) == true && end_node->__left_
//                nor any of its children refer to __z.  end_node->__left_
//                may be different than the value passed in as __root.
template <class _NodePtr>
void    __tree_remove(_NodePtr __root, _NodePtr __z)
{
    // __z will be removed from the tree.  Client still needs to destruct/deallocate it
    // __y is either __z, or if __z has two children, __tree_next(__z).
    // __y will have at most one child.
    // __y will be the initial hole in the tree (make the hole at a leaf)
    _NodePtr __y = (__z->__left_ == nullptr || __z->__right_ == nullptr) ?
                    __z : __tree_next(__z);
    // __x is __y's possibly null single child
    _NodePtr __x = __y->__left_ != nullptr ? __y->__left_ : __y->__right_;
    // __w is __x's possibly null uncle (will become __x's sibling)
    _NodePtr __w = nullptr;
    // link __x to __y's parent, and find __w
    if (__x != nullptr)
        __x->__parent_ = __y->__parent_;
    if (__tree_is_left_child(__y))
    {
        __y->__parent_->__left_ = __x;
        if (__y != __root)
            __w = __y->__parent_unsafe()->__right_;
        else
            __root = __x;  // __w == nullptr
    }
    else
    {
        __y->__parent_unsafe()->__right_ = __x;
        // __y can't be root if it is a right child
        __w = __y->__parent_->__left_;
    }
    bool __removed_black = __y->__is_black_;
    // If we didn't remove __z, do so now by splicing in __y for __z,
    //    but copy __z's color.  This does not impact __x or __w.
    if (__y != __z)
    {
        // __z->__left_ != nulptr but __z->__right_ might == __x == nullptr
        __y->__parent_ = __z->__parent_;
        if (__tree_is_left_child(__z))
            __y->__parent_->__left_ = __y;
        else
            __y->__parent_unsafe()->__right_ = __y;
        __y->__left_ = __z->__left_;
        __y->__left_->__set_parent(__y);
        __y->__right_ = __z->__right_;
        if (__y->__right_ != nullptr)
            __y->__right_->__set_parent(__y);
        __y->__is_black_ = __z->__is_black_;
        if (__root == __z)
            __root = __y;
    }
    // There is no need to rebalance if we removed a red, or if we removed
    //     the last node.
    if (__removed_black && __root != nullptr)
    {
        // Rebalance:
        // __x has an implicit black color (transferred from the removed __y)
        //    associated with it, no matter what its color is.
        // If __x is __root (in which case it can't be null), it is supposed
        //    to be black anyway, and if it is doubly black, then the double
        //    can just be ignored.
        // If __x is red (in which case it can't be null), then it can absorb
        //    the implicit black just by setting its color to black.
        // Since __y was black and only had one child (which __x points to), __x
        //   is either red with no children, else null, otherwise __y would have
        //   different black heights under left and right pointers.
        // if (__x == __root || __x != nullptr && !__x->__is_black_)
        if (__x != nullptr)
            __x->__is_black_ = true;
        else
        {
            //  Else __x isn't root, and is "doubly black", even though it may
            //     be null.  __w can not be null here, else the parent would
            //     see a black height >= 2 on the __x side and a black height
            //     of 1 on the __w side (__w must be a non-null black or a red
            //     with a non-null black child).
            while (true)
            {
                if (!__tree_is_left_child(__w))  // if x is left child
                {
                    if (!__w->__is_black_)
                    {
                        __w->__is_black_ = true;
                        __w->__parent_unsafe()->__is_black_ = false;
                        __tree_left_rotate(__w->__parent_unsafe());
                        // __x is still valid
                        // reset __root only if necessary
                        if (__root == __w->__left_)
                            __root = __w;
                        // reset sibling, and it still can't be null
                        __w = __w->__left_->__right_;
                    }
                    // __w->__is_black_ is now true, __w may have null children
                    if ((__w->__left_  == nullptr || __w->__left_->__is_black_) &&
                        (__w->__right_ == nullptr || __w->__right_->__is_black_))
                    {
                        __w->__is_black_ = false;
                        __x = __w->__parent_unsafe();
                        // __x can no longer be null
                        if (__x == __root || !__x->__is_black_)
                        {
                            __x->__is_black_ = true;
                            break;
                        }
                        // reset sibling, and it still can't be null
                        __w = __tree_is_left_child(__x) ?
                                    __x->__parent_unsafe()->__right_ :
                                    __x->__parent_->__left_;
                        // continue;
                    }
                    else  // __w has a red child
                    {
                        if (__w->__right_ == nullptr || __w->__right_->__is_black_)
                        {
                            // __w left child is non-null and red
                            __w->__left_->__is_black_ = true;
                            __w->__is_black_ = false;
                            __tree_right_rotate(__w);
                            // __w is known not to be root, so root hasn't changed
                            // reset sibling, and it still can't be null
                            __w = __w->__parent_unsafe();
                        }
                        // __w has a right red child, left child may be null
                        __w->__is_black_ = __w->__parent_unsafe()->__is_black_;
                        __w->__parent_unsafe()->__is_black_ = true;
                        __w->__right_->__is_black_ = true;
                        __tree_left_rotate(__w->__parent_unsafe());
                        break;
                    }
                }
                else
                {
                    if (!__w->__is_black_)
                    {
                        __w->__is_black_ = true;
                        __w->__parent_unsafe()->__is_black_ = false;
                        __tree_right_rotate(__w->__parent_unsafe());
                        // __x is still valid
                        // reset __root only if necessary
                        if (__root == __w->__right_)
                            __root = __w;
                        // reset sibling, and it still can't be null
                        __w = __w->__right_->__left_;
                    }
                    // __w->__is_black_ is now true, __w may have null children
                    if ((__w->__left_  == nullptr || __w->__left_->__is_black_) &&
                        (__w->__right_ == nullptr || __w->__right_->__is_black_))
                    {
                        __w->__is_black_ = false;
                        __x = __w->__parent_unsafe();
                        // __x can no longer be null
                        if (!__x->__is_black_ || __x == __root)
                        {
                            __x->__is_black_ = true;
                            break;
                        }
                        // reset sibling, and it still can't be null
                        __w = __tree_is_left_child(__x) ?
                                    __x->__parent_unsafe()->__right_ :
                                    __x->__parent_->__left_;
                        // continue;
                    }
                    else  // __w has a red child
                    {
                        if (__w->__left_ == nullptr || __w->__left_->__is_black_)
                        {
                            // __w right child is non-null and red
                            __w->__right_->__is_black_ = true;
                            __w->__is_black_ = false;
                            __tree_left_rotate(__w);
                            // __w is known not to be root, so root hasn't changed
                            // reset sibling, and it still can't be null
                            __w = __w->__parent_unsafe();
                        }
                        // __w has a left red child, right child may be null
                        __w->__is_black_ = __w->__parent_unsafe()->__is_black_;
                        __w->__parent_unsafe()->__is_black_ = true;
                        __w->__left_->__is_black_ = true;
                        __tree_right_rotate(__w->__parent_unsafe());
                        break;
                    }
                }
            }
        }
    }
}

// node traits

template <class _Tp>
struct __tree_key_value_types {
  typedef _Tp key_type;
  typedef _Tp __node_value_type;
  typedef _Tp __container_value_type;
  static const bool __is_map = false;

  static key_type const& __get_key(_Tp const& __v) {
    return __v;
  }

  static __container_value_type const& __get_value(__node_value_type const& __v) {
    return __v;
  }

  static __container_value_type* __get_ptr(__node_value_type& __n) {
    return _VSTD::addressof(__n);
  }
};

template <class _Key, class _Tp>
struct __tree_key_value_types<__value_type<_Key, _Tp> > {
  typedef _Key                                         key_type;
  typedef _Tp                                          mapped_type;
  typedef __value_type<_Key, _Tp>                      __node_value_type;
  typedef pair<const _Key, _Tp>                        __container_value_type;
  typedef __container_value_type                       __map_value_type;
  static const bool __is_map = true;

  static key_type const&
  __get_key(__node_value_type const& __t) {
    return __t.__get_value().first;
  }

  template <class _Up>
  static typename enable_if<__is_same_uncvref<_Up, __container_value_type>::value,
      key_type const&>::type
  __get_key(_Up& __t) {
    return __t.first;
  }

  static __container_value_type const&
  __get_value(__node_value_type const& __t) {
    return __t.__get_value();
  }

  template <class _Up>
  static typename enable_if<__is_same_uncvref<_Up, __container_value_type>::value,
      __container_value_type const&>::type
  __get_value(_Up& __t) {
    return __t;
  }

  static __container_value_type* __get_ptr(__node_value_type& __n) {
    return _VSTD::addressof(__n.__get_value());
  }
};

template <class _VoidPtr>
struct __tree_node_base_types {
  typedef _VoidPtr                                               __void_pointer;

  typedef __tree_node_base<__void_pointer>                      __node_base_type;
  typedef typename __rebind_pointer<_VoidPtr, __node_base_type>::type
                                                             __node_base_pointer;

  typedef __tree_end_node<__node_base_pointer>                  __end_node_type;
  typedef typename __rebind_pointer<_VoidPtr, __end_node_type>::type
                                                             __end_node_pointer;
  typedef typename conditional<
      is_pointer<__end_node_pointer>::value,
        __end_node_pointer,
        __node_base_pointer>::type __parent_pointer;

private:
  static_assert((is_same<typename pointer_traits<_VoidPtr>::element_type, void>::value),
                  "_VoidPtr does not point to unqualified void type");
};

template <class _Tp, class _AllocPtr, class _KVTypes = __tree_key_value_types<_Tp>,
         bool = _KVTypes::__is_map>
struct __tree_map_pointer_types {};

template <class _Tp, class _AllocPtr, class _KVTypes>
struct __tree_map_pointer_types<_Tp, _AllocPtr, _KVTypes, true> {
  typedef typename _KVTypes::__map_value_type   _Mv;
  typedef typename __rebind_pointer<_AllocPtr, _Mv>::type
                                                       __map_value_type_pointer;
  typedef typename __rebind_pointer<_AllocPtr, const _Mv>::type
                                                 __const_map_value_type_pointer;
};

template <class _NodePtr, class _NodeT = typename pointer_traits<_NodePtr>::element_type>
struct __tree_node_types;

template <class _NodePtr, class _Tp, class _VoidPtr>
struct __tree_node_types<_NodePtr, __tree_node<_Tp, _VoidPtr> >
    : public __tree_node_base_types<_VoidPtr>,
             __tree_key_value_types<_Tp>,
             __tree_map_pointer_types<_Tp, _VoidPtr>
{
  typedef __tree_node_base_types<_VoidPtr> __base;
  typedef __tree_key_value_types<_Tp>      __key_base;
  typedef __tree_map_pointer_types<_Tp, _VoidPtr> __map_pointer_base;
public:

  typedef typename pointer_traits<_NodePtr>::element_type       __node_type;
  typedef _NodePtr                                              __node_pointer;

  typedef _Tp                                                 __node_value_type;
  typedef typename __rebind_pointer<_VoidPtr, __node_value_type>::type
                                                      __node_value_type_pointer;
  typedef typename __rebind_pointer<_VoidPtr, const __node_value_type>::type
                                                __const_node_value_type_pointer;

  typedef typename conditional<
      is_pointer<__node_pointer>::value,
        typename __base::__end_node_pointer,
        __node_pointer>::type __iter_pointer;

private:
    static_assert(!is_const<__node_type>::value, "_NodePtr should never be a pointer to const");
    static_assert((is_same<typename __rebind_pointer<_VoidPtr, __node_type>::type,
                          _NodePtr>::value), "_VoidPtr does not rebind to _NodePtr.");
};

template <class _ValueTp, class _VoidPtr>
struct __make_tree_node_types
{
    typedef typename __rebind_pointer<_VoidPtr, __tree_node<_ValueTp, _VoidPtr> >::type _NodePtr;
    typedef __tree_node_types<_NodePtr> type;
};


template <class _Pointer>
class __tree_end_node
{
    public:
        typedef _Pointer pointer;
        pointer __left_;

        __tree_end_node() : __left_() {}
};

template <class _VoidPtr>
class __tree_node_base
    : public __tree_node_base_types<_VoidPtr>::__end_node_type
{
        typedef __tree_node_base_types<_VoidPtr> _NodeBaseTypes;

    public:
        typedef typename _NodeBaseTypes::__node_base_pointer pointer;
        typedef typename _NodeBaseTypes::__parent_pointer __parent_pointer;

        pointer          __right_;
        __parent_pointer __parent_;
        bool __is_black_;

        _LIBCPP_INLINE_VISIBILITY
        pointer __parent_unsafe() const { return static_cast<pointer>(__parent_);}

        _LIBCPP_INLINE_VISIBILITY
        void __set_parent(pointer __p) {
            __parent_ = static_cast<__parent_pointer>(__p);
        }

    private:
    ~__tree_node_base() _LIBCPP_EQUAL_DELETE;
    __tree_node_base(__tree_node_base const&) _LIBCPP_EQUAL_DELETE;
    __tree_node_base& operator=(__tree_node_base const&) _LIBCPP_EQUAL_DELETE;
};

template <class _Tp, class _VoidPtr>
class __tree_node
    : public __tree_node_base<_VoidPtr>
{
public:
    typedef _Tp __node_value_type;

    __node_value_type __value_;

private:
  ~__tree_node() _LIBCPP_EQUAL_DELETE;
  __tree_node(__tree_node const&) _LIBCPP_EQUAL_DELETE;
  __tree_node& operator=(__tree_node const&) _LIBCPP_EQUAL_DELETE;
};


template <class _Allocator>
class __tree_node_destructor
{
    typedef _Allocator                                      allocator_type;
    typedef allocator_traits<allocator_type>                __alloc_traits;

public:
    typedef typename __alloc_traits::pointer                pointer;
private:
    typedef __tree_node_types<pointer> _NodeTypes;
    allocator_type& __na_;


public:
    bool __value_constructed;


    __tree_node_destructor(const __tree_node_destructor &) = default;
    __tree_node_destructor& operator=(const __tree_node_destructor&) = delete;

    _LIBCPP_INLINE_VISIBILITY
    explicit __tree_node_destructor(allocator_type& __na, bool __val = false)
        : __na_(__na),
          __value_constructed(__val)
        {}

    _LIBCPP_INLINE_VISIBILITY
    void operator()(pointer __p)
    {
        if (__value_constructed)
            __alloc_traits::destroy(__na_, _NodeTypes::__get_ptr(__p->__value_));
        if (__p)
            __alloc_traits::deallocate(__na_, __p, 1);
    }

    template <class> friend class __map_node_destructor;
};

template <class _Tp, class _NodePtr, class _DiffType>
class __tree_const_iterator
{
    typedef __tree_node_types<_NodePtr>                     _NodeTypes;
    typedef typename _NodeTypes::__node_pointer             __node_pointer;
    typedef typename _NodeTypes::__node_base_pointer        __node_base_pointer;
    typedef typename _NodeTypes::__end_node_pointer         __end_node_pointer;
    typedef typename _NodeTypes::__iter_pointer             __iter_pointer;
    typedef pointer_traits<__node_pointer> __pointer_traits;

    __iter_pointer __ptr_;

public:
    typedef bidirectional_iterator_tag                           iterator_category;
    typedef _Tp                                                  value_type;
    typedef _DiffType                                            difference_type;
    typedef const value_type&                                    reference;
    typedef typename _NodeTypes::__const_node_value_type_pointer pointer;

     __tree_const_iterator() {}

private:
    typedef __tree_iterator<value_type, __node_pointer, difference_type>
                                                           __non_const_iterator;
public:
    __tree_const_iterator(__non_const_iterator __p)
        : __ptr_(__p.__ptr_) {}

    reference operator*() const {return __get_np()->__value_;}
    pointer operator->() const {return pointer_traits<pointer>::pointer_to(__get_np()->__value_);}

    __tree_const_iterator& operator++() {
      __ptr_ = static_cast<__iter_pointer>(
          __tree_next_iter<__end_node_pointer>(static_cast<__node_base_pointer>(__ptr_)));
      return *this;
    }

    __tree_const_iterator operator++(int)
        {__tree_const_iterator __t(*this); ++(*this); return __t;}

    __tree_const_iterator& operator--() {
      __ptr_ = static_cast<__iter_pointer>(__tree_prev_iter<__node_base_pointer>(
          static_cast<__end_node_pointer>(__ptr_)));
      return *this;
    }

    __tree_const_iterator operator--(int)
        {__tree_const_iterator __t(*this); --(*this); return __t;}

    friend  bool operator==(const __tree_const_iterator& __x, const __tree_const_iterator& __y)
        {return __x.__ptr_ == __y.__ptr_;}
    friend
        bool operator!=(const __tree_const_iterator& __x, const __tree_const_iterator& __y)
        {return !(__x == __y);}

private:

    explicit __tree_const_iterator(__node_pointer __p)
        : __ptr_(__p) {}

    explicit __tree_const_iterator(__end_node_pointer __p)
        : __ptr_(__p) {}

    __node_pointer __get_np() const { return static_cast<__node_pointer>(__ptr_); }

    template <class, class, class> friend class bst;
    template <class, class, class, class> friend class _LIBCPP_TEMPLATE_VIS map;
    template <class, class, class, class> friend class _LIBCPP_TEMPLATE_VIS multimap;
    template <class, class, class> friend class _LIBCPP_TEMPLATE_VIS set;
    template <class, class, class> friend class _LIBCPP_TEMPLATE_VIS multiset;
    template <class> friend class _LIBCPP_TEMPLATE_VIS __map_const_iterator;

};

template<class _Tp, class _Compare>
int __diagnose_non_const_comparator();

template <class _Tp, class _Compare, class _Allocator>
class bst
{
public:
    typedef _Tp                                      value_type;
    typedef _Compare                                 value_compare;
    typedef _Allocator                               allocator_type;
    typedef typename _NodeTypes::__node_value_type      __node_value_type;
    typedef typename _NodeTypes::__container_value_type __container_value_type;

    typedef typename __alloc_traits::pointer         pointer;
    typedef typename __alloc_traits::const_pointer   const_pointer;
    typedef typename __alloc_traits::size_type       size_type;
    typedef typename __alloc_traits::difference_type difference_type;
    typedef typename _NodeTypes::__void_pointer        __void_pointer;

    typedef typename _NodeTypes::__node_type           __node;
    typedef typename _NodeTypes::__node_pointer        __node_pointer;

    typedef typename _NodeTypes::__node_base_type      __node_base;
    typedef typename _NodeTypes::__node_base_pointer   __node_base_pointer;

    typedef typename _NodeTypes::__end_node_type       __end_node_t;
    typedef typename _NodeTypes::__end_node_pointer    __end_node_ptr;

    typedef typename _NodeTypes::__parent_pointer      __parent_pointer;
    typedef typename _NodeTypes::__iter_pointer        __iter_pointer;

    typedef typename __rebind_alloc_helper<__alloc_traits, __node>::type __node_allocator;
    typedef allocator_traits<__node_allocator>         __node_traits;


private:
    typedef allocator_traits<allocator_type>         __alloc_traits;
    typedef typename __make_tree_node_types<value_type,
        typename __alloc_traits::void_pointer>::type _NodeTypes;
    typedef typename _NodeTypes::key_type           key_type;


private:
    // check for sane allocator pointer rebinding semantics. Rebinding the
    // allocator for a new pointer type should be exactly the same as rebinding
    // the pointer using 'pointer_traits'.
    static_assert((is_same<__node_pointer, typename __node_traits::pointer>::value),
                  "Allocator does not rebind pointers in a sane manner.");
    typedef typename __rebind_alloc_helper<__node_traits, __node_base>::type
        __node_base_allocator;
    typedef allocator_traits<__node_base_allocator> __node_base_traits;
    static_assert((is_same<__node_base_pointer, typename __node_base_traits::pointer>::value),
                 "Allocator does not rebind pointers in a sane manner.");

private:
    __iter_pointer                                     __begin_node_;
    __compressed_pair<__end_node_t, __node_allocator>  __pair1_;
    __compressed_pair<size_type, value_compare>        __pair3_;

public:
    __iter_pointer __end_node()
    {
        return static_cast<__iter_pointer>(
                pointer_traits<__end_node_ptr>::pointer_to(__pair1_.first())
        );
    }
    __iter_pointer __end_node() const
    {
        return static_cast<__iter_pointer>(
            pointer_traits<__end_node_ptr>::pointer_to(
                const_cast<__end_node_t&>(__pair1_.first())
            )
        );
    }
          __node_allocator& __node_alloc() {return __pair1_.second();}

private:
    const __node_allocator& __node_alloc() const
        {return __pair1_.second();}
          __iter_pointer& __begin_node() {return __begin_node_;}
    const __iter_pointer& __begin_node() const {return __begin_node_;}
          size_type& size() {return __pair3_.first();}

public:
    allocator_type __alloc() const
        {return allocator_type(__node_alloc());}
    const size_type& size() const {return __pair3_.first();}
          value_compare& value_comp() {return __pair3_.second();}
    const value_compare& value_comp() const
        {return __pair3_.second();}

    __node_pointer __root() const
        {return static_cast<__node_pointer>(__end_node()->__left_);}

    __node_base_pointer* __root_ptr() const {
        return _VSTD::addressof(__end_node()->__left_);
    }

    typedef __tree_iterator<value_type, __node_pointer, difference_type>             iterator;
    typedef __tree_const_iterator<value_type, __node_pointer, difference_type> const_iterator;

    explicit __tree(const value_compare& __comp);
    explicit __tree(const allocator_type& __a);
    __tree(const value_compare& __comp, const allocator_type& __a);
    __tree(const __tree& __t);
    __tree& operator=(const __tree& __t);
    template <class _ForwardIterator>
        void __assign_unique(_ForwardIterator __first, _ForwardIterator __last);
    template <class _InputIterator>
        void __assign_multi(_InputIterator __first, _InputIterator __last);

    ~__tree();

    iterator begin() {return    iterator(__begin_node());}
    const_iterator begin() const {return const_iterator(__begin_node());}
    iterator end() {return  iterator(__end_node());}
    const_iterator end() const {return const_iterator(__end_node());}

    size_type max_size() const {return std::min<size_type>(__node_traits::max_size(__node_alloc()),
                numeric_limits<difference_type >::max());}

    void clear()
    {
        destroy(__root());
        size() = 0;
        __begin_node() = __end_node();
        __end_node()->__left_ = nullptr;
    }

    void swap(__tree& __t)
    {
        using _VSTD::swap;
        swap(__begin_node_, __t.__begin_node_);
        swap(__pair1_.first(), __t.__pair1_.first());
        __swap_allocator(__node_alloc(), __t.__node_alloc());
        __pair3_.swap(__t.__pair3_);
        if (size() == 0)
            __begin_node() = __end_node();
        else
            __end_node()->__left_->__parent_ = static_cast<__parent_pointer>(__end_node());
        if (__t.size() == 0)
            __t.__begin_node() = __t.__end_node();
        else
            __t.__end_node()->__left_->__parent_ = static_cast<__parent_pointer>(__t.__end_node());
    }

    template <class _Key, class _Args>
    pair<iterator, bool> __emplace_unique_key_args(_Key const&, _Args& __args);

    template <class _Key, class _Args>
    iterator __emplace_hint_unique_key_args(const_iterator, _Key const&, _Args&);

    pair<iterator, bool> __insert_unique(const __container_value_type& __v) {
        return __emplace_unique_key_args(_NodeTypes::__get_key(__v), __v);
    }

    iterator __insert_unique(const_iterator __p, const __container_value_type& __v) {
        return __emplace_hint_unique_key_args(__p, _NodeTypes::__get_key(__v), __v);
    }

    iterator __insert_multi(const __container_value_type& __v);
    iterator __insert_multi(const_iterator __p, const __container_value_type& __v);


    pair<iterator, bool> __node_assign_unique(const __container_value_type& __v, __node_pointer __dest);

    iterator __node_insert_multi(__node_pointer __nd);
    iterator __node_insert_multi(const_iterator __p, __node_pointer __nd);


    iterator __remove_node_pointer(__node_pointer);

    iterator erase(const_iterator __p);
    iterator erase(const_iterator __f, const_iterator __l);
    template <class _Key>
        size_type __erase_unique(const _Key& __k);
    template <class _Key>
        size_type __erase_multi(const _Key& __k);

    void __insert_node_at(__parent_pointer     __parent,
                          __node_base_pointer& __child,
                          __node_base_pointer __new_node);

    template <class _Key>
        iterator find(const _Key& __v);
    template <class _Key>
        const_iterator find(const _Key& __v) const;

    template <class _Key>
        size_type __count_unique(const _Key& __k) const;
    template <class _Key>
        size_type __count_multi(const _Key& __k) const;

    template <class _Key>
        iterator lower_bound(const _Key& __v)
            {return __lower_bound(__v, __root(), __end_node());}
    template <class _Key>
        iterator __lower_bound(const _Key& __v,
                               __node_pointer __root,
                               __iter_pointer __result);
    template <class _Key>
        const_iterator lower_bound(const _Key& __v) const
            {return __lower_bound(__v, __root(), __end_node());}

    template <class _Key>
        const_iterator __lower_bound(const _Key& __v,
                                     __node_pointer __root,
                                     __iter_pointer __result) const;
    template <class _Key>
        iterator upper_bound(const _Key& __v)
            {return __upper_bound(__v, __root(), __end_node());}

    template <class _Key>
        iterator __upper_bound(const _Key& __v,
                               __node_pointer __root,
                               __iter_pointer __result);
    template <class _Key>
        const_iterator upper_bound(const _Key& __v) const
            {return __upper_bound(__v, __root(), __end_node());}

    template <class _Key>
        const_iterator __upper_bound(const _Key& __v,
                                     __node_pointer __root,
                                     __iter_pointer __result) const;
    template <class _Key>
        pair<iterator, iterator> __equal_range_unique(const _Key& __k);
    template <class _Key>
        pair<const_iterator, const_iterator> __equal_range_unique(const _Key& __k) const;

    template <class _Key>
        pair<iterator, iterator>
        __equal_range_multi(const _Key& __k);
    template <class _Key>
        pair<const_iterator, const_iterator>
        __equal_range_multi(const _Key& __k) const;

    typedef __tree_node_destructor<__node_allocator> _Dp;
    typedef unique_ptr<__node, _Dp> __node_holder;

    __node_holder remove(const_iterator __p);
private:
    __node_base_pointer&
        __find_leaf_low(__parent_pointer& __parent, const key_type& __v);
    __node_base_pointer&
        __find_leaf_high(__parent_pointer& __parent, const key_type& __v);
    __node_base_pointer&
        __find_leaf(const_iterator __hint,
                    __parent_pointer& __parent, const key_type& __v);
    // FIXME: Make this function const qualified. Unfortunetly doing so
    // breaks existing code which uses non-const callable comparators.
    template <class _Key>
    __node_base_pointer&
        __find_equal(__parent_pointer& __parent, const _Key& __v);
    
    template <class _Key>
    __node_base_pointer& __find_equal(__parent_pointer& __parent, const _Key& __v) const {
      return const_cast<__tree*>(this)->__find_equal(__parent, __v);
    }
    
    template <class _Key>
    __node_base_pointer&
        __find_equal(const_iterator __hint, __parent_pointer& __parent,
                     __node_base_pointer& __dummy,
                     const _Key& __v);

    __node_holder __construct_node(const __container_value_type& __v);

    void destroy(__node_pointer __nd);

    void __copy_assign_alloc(const __tree& __t)
        {__copy_assign_alloc(__t, integral_constant<bool,
             __node_traits::propagate_on_container_copy_assignment::value>());}

    void __copy_assign_alloc(const __tree& __t, true_type)
    {
    if (__node_alloc() != __t.__node_alloc())
        clear();
    __node_alloc() = __t.__node_alloc();
    }

    void __copy_assign_alloc(const __tree&, false_type) {}

    void __move_assign(__tree& __t, false_type);
    void __move_assign(__tree& __t, true_type);

    void __move_assign_alloc(__tree& __t)
        {__move_assign_alloc(__t, integral_constant<bool,
             __node_traits::propagate_on_container_move_assignment::value>());}

    void __move_assign_alloc(__tree& __t, true_type)
        {__node_alloc() = _VSTD::move(__t.__node_alloc());}

    void __move_assign_alloc(__tree&, false_type) {}

    struct _DetachedTreeCache {
      explicit _DetachedTreeCache(__tree *__t) : __t_(__t),
        __cache_root_(__detach_from_tree(__t)) {
          __advance();
        }

      __node_pointer __get() const {
        return __cache_elem_;
      }

      void __advance() {
        __cache_elem_ = __cache_root_;
        if (__cache_root_) {
          __cache_root_ = __detach_next(__cache_root_);
        }
      }

      ~_DetachedTreeCache() {
        __t_->destroy(__cache_elem_);
        if (__cache_root_) {
          while (__cache_root_->__parent_ != nullptr)
            __cache_root_ = static_cast<__node_pointer>(__cache_root_->__parent_);
          __t_->destroy(__cache_root_);
        }
      }

       _DetachedTreeCache(_DetachedTreeCache const&) = delete;
       _DetachedTreeCache& operator=(_DetachedTreeCache const&) = delete;

    private:
      static __node_pointer __detach_from_tree(__tree *__t);
      static __node_pointer __detach_next(__node_pointer);

      __tree *__t_;
      __node_pointer __cache_root_;
      __node_pointer __cache_elem_;
    };


    template <class, class, class, class> friend class _LIBCPP_TEMPLATE_VIS map;
    template <class, class, class, class> friend class _LIBCPP_TEMPLATE_VIS multimap;
};

template <class _Tp, class _Compare, class _Allocator>
__tree<_Tp, _Compare, _Allocator>::__tree(const value_compare& __comp)
    : __pair3_(0, __comp)
{
    __begin_node() = __end_node();
}

template <class _Tp, class _Compare, class _Allocator>
__tree<_Tp, _Compare, _Allocator>::__tree(const allocator_type& __a)
    : __begin_node_(__iter_pointer()),
      __pair1_(__default_init_tag(), __node_allocator(__a)),
      __pair3_(0, __default_init_tag())
{
    __begin_node() = __end_node();
}

template <class _Tp, class _Compare, class _Allocator>
__tree<_Tp, _Compare, _Allocator>::__tree(const value_compare& __comp,
                                           const allocator_type& __a)
    : __begin_node_(__iter_pointer()),
      __pair1_(__default_init_tag(), __node_allocator(__a)),
      __pair3_(0, __comp)
{
    __begin_node() = __end_node();
}

// Precondition:  size() != 0
template <class _Tp, class _Compare, class _Allocator>
typename __tree<_Tp, _Compare, _Allocator>::__node_pointer
__tree<_Tp, _Compare, _Allocator>::_DetachedTreeCache::__detach_from_tree(__tree *__t)
{
    __node_pointer __cache = static_cast<__node_pointer>(__t->__begin_node());
    __t->__begin_node() = __t->__end_node();
    __t->__end_node()->__left_->__parent_ = nullptr;
    __t->__end_node()->__left_ = nullptr;
    __t->size() = 0;
    if (__cache->__right_ != nullptr)
        __cache = static_cast<__node_pointer>(__cache->__right_);
    return __cache;
}

// Precondition:  __cache != nullptr
//    __cache->left_ == nullptr
//    __cache->right_ == nullptr
//    This is no longer a red-black tree
template <class _Tp, class _Compare, class _Allocator>
typename __tree<_Tp, _Compare, _Allocator>::__node_pointer
__tree<_Tp, _Compare, _Allocator>::_DetachedTreeCache::__detach_next(__node_pointer __cache)
{
    if (__cache->__parent_ == nullptr)
        return nullptr;
    if (__tree_is_left_child(static_cast<__node_base_pointer>(__cache)))
    {
        __cache->__parent_->__left_ = nullptr;
        __cache = static_cast<__node_pointer>(__cache->__parent_);
        if (__cache->__right_ == nullptr)
            return __cache;
        return static_cast<__node_pointer>(__tree_leaf(__cache->__right_));
    }
    // __cache is right child
    __cache->__parent_unsafe()->__right_ = nullptr;
    __cache = static_cast<__node_pointer>(__cache->__parent_);
    if (__cache->__left_ == nullptr)
        return __cache;
    return static_cast<__node_pointer>(__tree_leaf(__cache->__left_));
}

template <class _Tp, class _Compare, class _Allocator>
__tree<_Tp, _Compare, _Allocator>&
__tree<_Tp, _Compare, _Allocator>::operator=(const __tree& __t)
{
    if (this != &__t)
    {
        value_comp() = __t.value_comp();
        __copy_assign_alloc(__t);
        __assign_multi(__t.begin(), __t.end());
    }
    return *this;
}

template <class _Tp, class _Compare, class _Allocator>
template <class _ForwardIterator>
void
__tree<_Tp, _Compare, _Allocator>::__assign_unique(_ForwardIterator __first, _ForwardIterator __last)
{
    typedef iterator_traits<_ForwardIterator> _ITraits;
    typedef typename _ITraits::value_type _ItValueType;
    static_assert((is_same<_ItValueType, __container_value_type>::value),
                  "__assign_unique may only be called with the containers value type");
    static_assert(__is_cpp17_forward_iterator<_ForwardIterator>::value,
                  "__assign_unique requires a forward iterator");
    if (size() != 0)
    {
        _DetachedTreeCache __cache(this);
          for (; __cache.__get() != nullptr && __first != __last; ++__first) {
              if (__node_assign_unique(*__first, __cache.__get()).second)
                  __cache.__advance();
            }
    }
    for (; __first != __last; ++__first)
        __insert_unique(*__first);
}

template <class _Tp, class _Compare, class _Allocator>
template <class _InputIterator>
void    __tree<_Tp, _Compare, _Allocator>::__assign_multi(_InputIterator __first, _InputIterator __last)
{
    typedef iterator_traits<_InputIterator> _ITraits;
    typedef typename _ITraits::value_type _ItValueType;
    static_assert((is_same<_ItValueType, __container_value_type>::value ||
                  is_same<_ItValueType, __node_value_type>::value),
                  "__assign_multi may only be called with the containers value type"
                  " or the nodes value type");
    if (size() != 0)
    {
        _DetachedTreeCache __cache(this);
        for (; __cache.__get() && __first != __last; ++__first) {
            __cache.__get()->__value_ = *__first;
            __node_insert_multi(__cache.__get());
            __cache.__advance();
        }
    }
    for (; __first != __last; ++__first)
        __insert_multi(_NodeTypes::__get_value(*__first));
}

template <class _Tp, class _Compare, class _Allocator>
__tree<_Tp, _Compare, _Allocator>::__tree(const __tree& __t)
    : __begin_node_(__iter_pointer()),
      __pair1_(__default_init_tag(), __node_traits::select_on_container_copy_construction(__t.__node_alloc())),
      __pair3_(0, __t.value_comp())
{
    __begin_node() = __end_node();
}

template <class _Tp, class _Compare, class _Allocator>
__tree<_Tp, _Compare, _Allocator>::~__tree()
{
    static_assert((is_copy_constructible<value_compare>::value),
                 "Comparator must be copy-constructible.");
  destroy(__root());
}

template <class _Tp, class _Compare, class _Allocator>
void
__tree<_Tp, _Compare, _Allocator>::destroy(__node_pointer __nd)
{
    if (__nd != nullptr)
    {
        destroy(static_cast<__node_pointer>(__nd->__left_));
        destroy(static_cast<__node_pointer>(__nd->__right_));
        __node_allocator& __na = __node_alloc();
        __node_traits::destroy(__na, _NodeTypes::__get_ptr(__nd->__value_));
        __node_traits::deallocate(__na, __nd, 1);
    }
}

// Find lower_bound place to insert
// Set __parent to parent of null leaf
// Return reference to null leaf
template <class _Tp, class _Compare, class _Allocator>
typename __tree<_Tp, _Compare, _Allocator>::__node_base_pointer&
__tree<_Tp, _Compare, _Allocator>::__find_leaf_low(__parent_pointer& __parent,
                                                   const key_type& __v)
{
    __node_pointer __nd = __root();
    if (__nd != nullptr)
    {
        while (true)
        {
            if (value_comp()(__nd->__value_, __v))
            {
                if (__nd->__right_ != nullptr)
                    __nd = static_cast<__node_pointer>(__nd->__right_);
                else
                {
                    __parent = static_cast<__parent_pointer>(__nd);
                    return __nd->__right_;
                }
            }
            else
            {
                if (__nd->__left_ != nullptr)
                    __nd = static_cast<__node_pointer>(__nd->__left_);
                else
                {
                    __parent = static_cast<__parent_pointer>(__nd);
                    return __parent->__left_;
                }
            }
        }
    }
    __parent = static_cast<__parent_pointer>(__end_node());
    return __parent->__left_;
}

// Find upper_bound place to insert
// Set __parent to parent of null leaf
// Return reference to null leaf
template <class _Tp, class _Compare, class _Allocator>
typename __tree<_Tp, _Compare, _Allocator>::__node_base_pointer&
__tree<_Tp, _Compare, _Allocator>::__find_leaf_high(__parent_pointer& __parent,
                                                    const key_type& __v)
{
    __node_pointer __nd = __root();
    if (__nd != nullptr)
    {
        while (true)
        {
            if (value_comp()(__v, __nd->__value_))
            {
                if (__nd->__left_ != nullptr)
                    __nd = static_cast<__node_pointer>(__nd->__left_);
                else
                {
                    __parent = static_cast<__parent_pointer>(__nd);
                    return __parent->__left_;
                }
            }
            else
            {
                if (__nd->__right_ != nullptr)
                    __nd = static_cast<__node_pointer>(__nd->__right_);
                else
                {
                    __parent = static_cast<__parent_pointer>(__nd);
                    return __nd->__right_;
                }
            }
        }
    }
    __parent = static_cast<__parent_pointer>(__end_node());
    return __parent->__left_;
}

// Find leaf place to insert closest to __hint
// First check prior to __hint.
// Next check after __hint.
// Next do O(log N) search.
// Set __parent to parent of null leaf
// Return reference to null leaf
template <class _Tp, class _Compare, class _Allocator>
typename __tree<_Tp, _Compare, _Allocator>::__node_base_pointer&
__tree<_Tp, _Compare, _Allocator>::__find_leaf(const_iterator __hint,
                                               __parent_pointer& __parent,
                                               const key_type& __v)
{
    if (__hint == end() || !value_comp()(*__hint, __v))  // check before
    {
        // __v <= *__hint
        const_iterator __prior = __hint;
        if (__prior == begin() || !value_comp()(__v, *--__prior))
        {
            // *prev(__hint) <= __v <= *__hint
            if (__hint.__ptr_->__left_ == nullptr)
            {
                __parent = static_cast<__parent_pointer>(__hint.__ptr_);
                return __parent->__left_;
            }
            else
            {
                __parent = static_cast<__parent_pointer>(__prior.__ptr_);
                return static_cast<__node_base_pointer>(__prior.__ptr_)->__right_;
            }
        }
        // __v < *prev(__hint)
        return __find_leaf_high(__parent, __v);
    }
    // else __v > *__hint
    return __find_leaf_low(__parent, __v);
}

// Find place to insert if __v doesn't exist
// Set __parent to parent of null leaf
// Return reference to null leaf
// If __v exists, set parent to node of __v and return reference to node of __v
template <class _Tp, class _Compare, class _Allocator>
template <class _Key>
typename __tree<_Tp, _Compare, _Allocator>::__node_base_pointer&
__tree<_Tp, _Compare, _Allocator>::__find_equal(__parent_pointer& __parent,
                                                const _Key& __v)
{
    __node_pointer __nd = __root();
    __node_base_pointer* __nd_ptr = __root_ptr();
    if (__nd != nullptr)
    {
        while (true)
        {
            if (value_comp()(__v, __nd->__value_))
            {
                if (__nd->__left_ != nullptr) {
                    __nd_ptr = _VSTD::addressof(__nd->__left_);
                    __nd = static_cast<__node_pointer>(__nd->__left_);
                } else {
                    __parent = static_cast<__parent_pointer>(__nd);
                    return __parent->__left_;
                }
            }
            else if (value_comp()(__nd->__value_, __v))
            {
                if (__nd->__right_ != nullptr) {
                    __nd_ptr = _VSTD::addressof(__nd->__right_);
                    __nd = static_cast<__node_pointer>(__nd->__right_);
                } else {
                    __parent = static_cast<__parent_pointer>(__nd);
                    return __nd->__right_;
                }
            }
            else
            {
                __parent = static_cast<__parent_pointer>(__nd);
                return *__nd_ptr;
            }
        }
    }
    __parent = static_cast<__parent_pointer>(__end_node());
    return __parent->__left_;
}

// Find place to insert if __v doesn't exist
// First check prior to __hint.
// Next check after __hint.
// Next do O(log N) search.
// Set __parent to parent of null leaf
// Return reference to null leaf
// If __v exists, set parent to node of __v and return reference to node of __v
template <class _Tp, class _Compare, class _Allocator>
template <class _Key>
typename __tree<_Tp, _Compare, _Allocator>::__node_base_pointer&
__tree<_Tp, _Compare, _Allocator>::__find_equal(const_iterator __hint,
                                                __parent_pointer& __parent,
                                                __node_base_pointer& __dummy,
                                                const _Key& __v)
{
    if (__hint == end() || value_comp()(__v, *__hint))  // check before
    {
        // __v < *__hint
        const_iterator __prior = __hint;
        if (__prior == begin() || value_comp()(*--__prior, __v))
        {
            // *prev(__hint) < __v < *__hint
            if (__hint.__ptr_->__left_ == nullptr)
            {
                __parent = static_cast<__parent_pointer>(__hint.__ptr_);
                return __parent->__left_;
            }
            else
            {
                __parent = static_cast<__parent_pointer>(__prior.__ptr_);
                return static_cast<__node_base_pointer>(__prior.__ptr_)->__right_;
            }
        }
        // __v <= *prev(__hint)
        return __find_equal(__parent, __v);
    }
    else if (value_comp()(*__hint, __v))  // check after
    {
        // *__hint < __v
        const_iterator __next = _VSTD::next(__hint);
        if (__next == end() || value_comp()(__v, *__next))
        {
            // *__hint < __v < *_VSTD::next(__hint)
            if (__hint.__get_np()->__right_ == nullptr)
            {
                __parent = static_cast<__parent_pointer>(__hint.__ptr_);
                return static_cast<__node_base_pointer>(__hint.__ptr_)->__right_;
            }
            else
            {
                __parent = static_cast<__parent_pointer>(__next.__ptr_);
                return __parent->__left_;
            }
        }
        // *next(__hint) <= __v
        return __find_equal(__parent, __v);
    }
    // else __v == *__hint
    __parent = static_cast<__parent_pointer>(__hint.__ptr_);
    __dummy = static_cast<__node_base_pointer>(__hint.__ptr_);
    return __dummy;
}

template <class _Tp, class _Compare, class _Allocator>
void __tree<_Tp, _Compare, _Allocator>::__insert_node_at(
    __parent_pointer __parent, __node_base_pointer& __child,
    __node_base_pointer __new_node)
{
    __new_node->__left_   = nullptr;
    __new_node->__right_  = nullptr;
    __new_node->__parent_ = __parent;
    // __new_node->__is_black_ is initialized in __tree_balance_after_insert
    __child = __new_node;
    if (__begin_node()->__left_ != nullptr)
        __begin_node() = static_cast<__iter_pointer>(__begin_node()->__left_);
    __tree_balance_after_insert(__end_node()->__left_, __child);
    ++size();
}

template <class _Tp, class _Compare, class _Allocator>
template <class _Key, class _Args>
pair<typename __tree<_Tp, _Compare, _Allocator>::iterator, bool>
__tree<_Tp, _Compare, _Allocator>::__emplace_unique_key_args(_Key const& __k, _Args& __args)
{
    __parent_pointer __parent;
    __node_base_pointer& __child = __find_equal(__parent, __k);
    __node_pointer __r = static_cast<__node_pointer>(__child);
    bool __inserted = false;
    if (__child == nullptr)
    {
        __node_holder __h = __construct_node(__args);
        __insert_node_at(__parent, __child, static_cast<__node_base_pointer>(__h.get()));
        __r = __h.release();
        __inserted = true;
    }
    return pair<iterator, bool>(iterator(__r), __inserted);
}


template <class _Tp, class _Compare, class _Allocator>
template <class _Key, class _Args>
typename __tree<_Tp, _Compare, _Allocator>::iterator
__tree<_Tp, _Compare, _Allocator>::__emplace_hint_unique_key_args(
    const_iterator __p, _Key const& __k, _Args& __args)
{
    __parent_pointer __parent;
    __node_base_pointer __dummy;
    __node_base_pointer& __child = __find_equal(__p, __parent, __dummy, __k);
    __node_pointer __r = static_cast<__node_pointer>(__child);
    if (__child == nullptr)
    {
        __node_holder __h = __construct_node(__args);
        __insert_node_at(__parent, __child, static_cast<__node_base_pointer>(__h.get()));
        __r = __h.release();
    }
    return iterator(__r);
}

template <class _Tp, class _Compare, class _Allocator>
typename __tree<_Tp, _Compare, _Allocator>::__node_holder
__tree<_Tp, _Compare, _Allocator>::__construct_node(const __container_value_type& __v)
{
    __node_allocator& __na = __node_alloc();
    __node_holder __h(__node_traits::allocate(__na, 1), _Dp(__na));
    __node_traits::construct(__na, _NodeTypes::__get_ptr(__h->__value_), __v);
    __h.get_deleter().__value_constructed = true;
    return _LIBCPP_EXPLICIT_MOVE(__h);  // explicitly moved for C++03
}

template <class _Tp, class _Compare, class _Allocator>
typename __tree<_Tp, _Compare, _Allocator>::iterator
__tree<_Tp, _Compare, _Allocator>::__insert_multi(const __container_value_type& __v)
{
    __parent_pointer __parent;
    __node_base_pointer& __child = __find_leaf_high(__parent, _NodeTypes::__get_key(__v));
    __node_holder __h = __construct_node(__v);
    __insert_node_at(__parent, __child, static_cast<__node_base_pointer>(__h.get()));
    return iterator(__h.release());
}

template <class _Tp, class _Compare, class _Allocator>
typename __tree<_Tp, _Compare, _Allocator>::iterator
__tree<_Tp, _Compare, _Allocator>::__insert_multi(const_iterator __p, const __container_value_type& __v)
{
    __parent_pointer __parent;
    __node_base_pointer& __child = __find_leaf(__p, __parent, _NodeTypes::__get_key(__v));
    __node_holder __h = __construct_node(__v);
    __insert_node_at(__parent, __child, static_cast<__node_base_pointer>(__h.get()));
    return iterator(__h.release());
}

template <class _Tp, class _Compare, class _Allocator>
pair<typename __tree<_Tp, _Compare, _Allocator>::iterator, bool>
__tree<_Tp, _Compare, _Allocator>::__node_assign_unique(const __container_value_type& __v, __node_pointer __nd)
{
    __parent_pointer __parent;
    __node_base_pointer& __child = __find_equal(__parent, _NodeTypes::__get_key(__v));
    __node_pointer __r = static_cast<__node_pointer>(__child);
    bool __inserted = false;
    if (__child == nullptr)
    {
        __nd->__value_ = __v;
        __insert_node_at(__parent, __child, static_cast<__node_base_pointer>(__nd));
        __r = __nd;
        __inserted = true;
    }
    return pair<iterator, bool>(iterator(__r), __inserted);
}


template <class _Tp, class _Compare, class _Allocator>
typename __tree<_Tp, _Compare, _Allocator>::iterator
__tree<_Tp, _Compare, _Allocator>::__node_insert_multi(__node_pointer __nd)
{
    __parent_pointer __parent;
    __node_base_pointer& __child = __find_leaf_high(__parent, _NodeTypes::__get_key(__nd->__value_));
    __insert_node_at(__parent, __child, static_cast<__node_base_pointer>(__nd));
    return iterator(__nd);
}

template <class _Tp, class _Compare, class _Allocator>
typename __tree<_Tp, _Compare, _Allocator>::iterator
__tree<_Tp, _Compare, _Allocator>::__node_insert_multi(const_iterator __p,
                                                       __node_pointer __nd)
{
    __parent_pointer __parent;
    __node_base_pointer& __child = __find_leaf(__p, __parent, _NodeTypes::__get_key(__nd->__value_));
    __insert_node_at(__parent, __child, static_cast<__node_base_pointer>(__nd));
    return iterator(__nd);
}

template <class _Tp, class _Compare, class _Allocator>
typename __tree<_Tp, _Compare, _Allocator>::iterator
__tree<_Tp, _Compare, _Allocator>::__remove_node_pointer(__node_pointer __ptr)
{
    iterator __r(__ptr);
    ++__r;
    if (__begin_node() == __ptr)
        __begin_node() = __r.__ptr_;
    --size();
    __tree_remove(__end_node()->__left_,
                  static_cast<__node_base_pointer>(__ptr));
    return __r;
}

template <class _Tp, class _Compare, class _Allocator>
typename __tree<_Tp, _Compare, _Allocator>::iterator
__tree<_Tp, _Compare, _Allocator>::erase(const_iterator __p)
{
    __node_pointer __np = __p.__get_np();
    iterator __r = __remove_node_pointer(__np);
    __node_allocator& __na = __node_alloc();
    __node_traits::destroy(__na, _NodeTypes::__get_ptr(
        const_cast<__node_value_type&>(*__p)));
    __node_traits::deallocate(__na, __np, 1);
    return __r;
}

template <class _Tp, class _Compare, class _Allocator>
typename __tree<_Tp, _Compare, _Allocator>::iterator
__tree<_Tp, _Compare, _Allocator>::erase(const_iterator __f, const_iterator __l)
{
    while (__f != __l)
        __f = erase(__f);
    return iterator(__l.__ptr_);
}

template <class _Tp, class _Compare, class _Allocator>
template <class _Key>
typename __tree<_Tp, _Compare, _Allocator>::size_type
__tree<_Tp, _Compare, _Allocator>::__erase_unique(const _Key& __k)
{
    iterator __i = find(__k);
    if (__i == end())
        return 0;
    erase(__i);
    return 1;
}

template <class _Tp, class _Compare, class _Allocator>
template <class _Key>
typename __tree<_Tp, _Compare, _Allocator>::size_type
__tree<_Tp, _Compare, _Allocator>::__erase_multi(const _Key& __k)
{
    pair<iterator, iterator> __p = __equal_range_multi(__k);
    size_type __r = 0;
    for (; __p.first != __p.second; ++__r)
        __p.first = erase(__p.first);
    return __r;
}

template <class _Tp, class _Compare, class _Allocator>
template <class _Key>
typename __tree<_Tp, _Compare, _Allocator>::iterator
__tree<_Tp, _Compare, _Allocator>::find(const _Key& __v)
{
    iterator __p = __lower_bound(__v, __root(), __end_node());
    if (__p != end() && !value_comp()(__v, *__p))
        return __p;
    return end();
}

template <class _Tp, class _Compare, class _Allocator>
template <class _Key>
typename __tree<_Tp, _Compare, _Allocator>::const_iterator
__tree<_Tp, _Compare, _Allocator>::find(const _Key& __v) const
{
    const_iterator __p = __lower_bound(__v, __root(), __end_node());
    if (__p != end() && !value_comp()(__v, *__p))
        return __p;
    return end();
}

template <class _Tp, class _Compare, class _Allocator>
template <class _Key>
typename __tree<_Tp, _Compare, _Allocator>::size_type
__tree<_Tp, _Compare, _Allocator>::__count_unique(const _Key& __k) const
{
    __node_pointer __rt = __root();
    while (__rt != nullptr)
    {
        if (value_comp()(__k, __rt->__value_))
        {
            __rt = static_cast<__node_pointer>(__rt->__left_);
        }
        else if (value_comp()(__rt->__value_, __k))
            __rt = static_cast<__node_pointer>(__rt->__right_);
        else
            return 1;
    }
    return 0;
}

template <class _Tp, class _Compare, class _Allocator>
template <class _Key>
typename __tree<_Tp, _Compare, _Allocator>::size_type
__tree<_Tp, _Compare, _Allocator>::__count_multi(const _Key& __k) const
{
    __iter_pointer __result = __end_node();
    __node_pointer __rt = __root();
    while (__rt != nullptr)
    {
        if (value_comp()(__k, __rt->__value_))
        {
            __result = static_cast<__iter_pointer>(__rt);
            __rt = static_cast<__node_pointer>(__rt->__left_);
        }
        else if (value_comp()(__rt->__value_, __k))
            __rt = static_cast<__node_pointer>(__rt->__right_);
        else
            return _VSTD::distance(
                __lower_bound(__k, static_cast<__node_pointer>(__rt->__left_), static_cast<__iter_pointer>(__rt)),
                __upper_bound(__k, static_cast<__node_pointer>(__rt->__right_), __result)
            );
    }
    return 0;
}

template <class _Tp, class _Compare, class _Allocator>
template <class _Key>
typename __tree<_Tp, _Compare, _Allocator>::iterator
__tree<_Tp, _Compare, _Allocator>::__lower_bound(const _Key& __v,
                                                 __node_pointer __root,
                                                 __iter_pointer __result)
{
    while (__root != nullptr)
    {
        if (!value_comp()(__root->__value_, __v))
        {
            __result = static_cast<__iter_pointer>(__root);
            __root = static_cast<__node_pointer>(__root->__left_);
        }
        else
            __root = static_cast<__node_pointer>(__root->__right_);
    }
    return iterator(__result);
}

template <class _Tp, class _Compare, class _Allocator>
template <class _Key>
typename __tree<_Tp, _Compare, _Allocator>::const_iterator
__tree<_Tp, _Compare, _Allocator>::__lower_bound(const _Key& __v,
                                                 __node_pointer __root,
                                                 __iter_pointer __result) const
{
    while (__root != nullptr)
    {
        if (!value_comp()(__root->__value_, __v))
        {
            __result = static_cast<__iter_pointer>(__root);
            __root = static_cast<__node_pointer>(__root->__left_);
        }
        else
            __root = static_cast<__node_pointer>(__root->__right_);
    }
    return const_iterator(__result);
}

template <class _Tp, class _Compare, class _Allocator>
template <class _Key>
typename __tree<_Tp, _Compare, _Allocator>::iterator
__tree<_Tp, _Compare, _Allocator>::__upper_bound(const _Key& __v,
                                                 __node_pointer __root,
                                                 __iter_pointer __result)
{
    while (__root != nullptr)
    {
        if (value_comp()(__v, __root->__value_))
        {
            __result = static_cast<__iter_pointer>(__root);
            __root = static_cast<__node_pointer>(__root->__left_);
        }
        else
            __root = static_cast<__node_pointer>(__root->__right_);
    }
    return iterator(__result);
}

template <class _Tp, class _Compare, class _Allocator>
template <class _Key>
typename __tree<_Tp, _Compare, _Allocator>::const_iterator
__tree<_Tp, _Compare, _Allocator>::__upper_bound(const _Key& __v,
                                                 __node_pointer __root,
                                                 __iter_pointer __result) const
{
    while (__root != nullptr)
    {
        if (value_comp()(__v, __root->__value_))
        {
            __result = static_cast<__iter_pointer>(__root);
            __root = static_cast<__node_pointer>(__root->__left_);
        }
        else
            __root = static_cast<__node_pointer>(__root->__right_);
    }
    return const_iterator(__result);
}

template <class _Tp, class _Compare, class _Allocator>
template <class _Key>
pair<typename __tree<_Tp, _Compare, _Allocator>::iterator,
     typename __tree<_Tp, _Compare, _Allocator>::iterator>
__tree<_Tp, _Compare, _Allocator>::__equal_range_unique(const _Key& __k)
{
    typedef pair<iterator, iterator> _Pp;
    __iter_pointer __result = __end_node();
    __node_pointer __rt = __root();
    while (__rt != nullptr)
    {
        if (value_comp()(__k, __rt->__value_))
        {
            __result = static_cast<__iter_pointer>(__rt);
            __rt = static_cast<__node_pointer>(__rt->__left_);
        }
        else if (value_comp()(__rt->__value_, __k))
            __rt = static_cast<__node_pointer>(__rt->__right_);
        else
            return _Pp(iterator(__rt),
                      iterator(
                          __rt->__right_ != nullptr ?
                              static_cast<__iter_pointer>(__tree_min(__rt->__right_))
                            : __result));
    }
    return _Pp(iterator(__result), iterator(__result));
}

template <class _Tp, class _Compare, class _Allocator>
template <class _Key>
pair<typename __tree<_Tp, _Compare, _Allocator>::const_iterator,
     typename __tree<_Tp, _Compare, _Allocator>::const_iterator>
__tree<_Tp, _Compare, _Allocator>::__equal_range_unique(const _Key& __k) const
{
    typedef pair<const_iterator, const_iterator> _Pp;
    __iter_pointer __result = __end_node();
    __node_pointer __rt = __root();
    while (__rt != nullptr)
    {
        if (value_comp()(__k, __rt->__value_))
        {
            __result = static_cast<__iter_pointer>(__rt);
            __rt = static_cast<__node_pointer>(__rt->__left_);
        }
        else if (value_comp()(__rt->__value_, __k))
            __rt = static_cast<__node_pointer>(__rt->__right_);
        else
            return _Pp(const_iterator(__rt),
                      const_iterator(
                          __rt->__right_ != nullptr ?
                              static_cast<__iter_pointer>(__tree_min(__rt->__right_))
                            : __result));
    }
    return _Pp(const_iterator(__result), const_iterator(__result));
}

template <class _Tp, class _Compare, class _Allocator>
template <class _Key>
pair<typename __tree<_Tp, _Compare, _Allocator>::iterator,
     typename __tree<_Tp, _Compare, _Allocator>::iterator>
__tree<_Tp, _Compare, _Allocator>::__equal_range_multi(const _Key& __k)
{
    typedef pair<iterator, iterator> _Pp;
    __iter_pointer __result = __end_node();
    __node_pointer __rt = __root();
    while (__rt != nullptr)
    {
        if (value_comp()(__k, __rt->__value_))
        {
            __result = static_cast<__iter_pointer>(__rt);
            __rt = static_cast<__node_pointer>(__rt->__left_);
        }
        else if (value_comp()(__rt->__value_, __k))
            __rt = static_cast<__node_pointer>(__rt->__right_);
        else
            return _Pp(__lower_bound(__k, static_cast<__node_pointer>(__rt->__left_), static_cast<__iter_pointer>(__rt)),
                      __upper_bound(__k, static_cast<__node_pointer>(__rt->__right_), __result));
    }
    return _Pp(iterator(__result), iterator(__result));
}

template <class _Tp, class _Compare, class _Allocator>
template <class _Key>
pair<typename __tree<_Tp, _Compare, _Allocator>::const_iterator,
     typename __tree<_Tp, _Compare, _Allocator>::const_iterator>
__tree<_Tp, _Compare, _Allocator>::__equal_range_multi(const _Key& __k) const
{
    typedef pair<const_iterator, const_iterator> _Pp;
    __iter_pointer __result = __end_node();
    __node_pointer __rt = __root();
    while (__rt != nullptr)
    {
        if (value_comp()(__k, __rt->__value_))
        {
            __result = static_cast<__iter_pointer>(__rt);
            __rt = static_cast<__node_pointer>(__rt->__left_);
        }
        else if (value_comp()(__rt->__value_, __k))
            __rt = static_cast<__node_pointer>(__rt->__right_);
        else
            return _Pp(__lower_bound(__k, static_cast<__node_pointer>(__rt->__left_), static_cast<__iter_pointer>(__rt)),
                      __upper_bound(__k, static_cast<__node_pointer>(__rt->__right_), __result));
    }
    return _Pp(const_iterator(__result), const_iterator(__result));
}

template <class _Tp, class _Compare, class _Allocator>
typename __tree<_Tp, _Compare, _Allocator>::__node_holder
__tree<_Tp, _Compare, _Allocator>::remove(const_iterator __p)
{
    __node_pointer __np = __p.__get_np();
    if (__begin_node() == __p.__ptr_)
    {
        if (__np->__right_ != nullptr)
            __begin_node() = static_cast<__iter_pointer>(__np->__right_);
        else
            __begin_node() = static_cast<__iter_pointer>(__np->__parent_);
    }
    --size();
    __tree_remove(__end_node()->__left_,
                  static_cast<__node_base_pointer>(__np));
    return __node_holder(__np, _Dp(__node_alloc(), true));
}

template <class _Tp, class _Compare, class _Allocator>
void
swap(__tree<_Tp, _Compare, _Allocator>& __x, __tree<_Tp, _Compare, _Allocator>& __y)
{
    __x.swap(__y);
}

#endif
