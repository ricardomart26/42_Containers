
template <class _Tp, class _NodePtr, class _DiffType>
class __tree_iterator
{
    typedef __tree_node_types<_NodePtr>                     _NodeTypes;
    typedef _NodePtr                                        __node_pointer;
    typedef typename _NodeTypes::__node_base_pointer        __node_base_pointer;
    typedef typename _NodeTypes::__end_node_pointer         __end_node_pointer;
    typedef typename _NodeTypes::__iter_pointer             __iter_pointer;
    typedef pointer_traits<__node_pointer> __pointer_traits;

    __iter_pointer __ptr_;

public:
    typedef bidirectional_iterator_tag                     iterator_category;
    typedef _Tp                                            value_type;
    typedef _DiffType                                      difference_type;
    typedef value_type&                                    reference;
    typedef typename _NodeTypes::__node_value_type_pointer pointer;

    __tree_iterator() {}

    reference operator*() const {return __get_np()->__value_;}
    
    pointer operator->() const
        {return pointer_traits<pointer>::pointer_to(__get_np()->__value_);}

    __tree_iterator& operator++() {
      __ptr_ = static_cast<__iter_pointer>(
          __tree_next_iter<__end_node_pointer>(static_cast<__node_base_pointer>(__ptr_)));
      return *this;
    }

    __tree_iterator operator++(int) {__tree_iterator __t(*this); ++(*this); return __t;}

    __tree_iterator& operator--() {
      __ptr_ = static_cast<__iter_pointer>(__tree_prev_iter<__node_base_pointer>(
          static_cast<__end_node_pointer>(__ptr_)));
      return *this;
    }

    __tree_iterator operator--(int)
        {__tree_iterator __t(*this); --(*this); return __t;}

    friend bool operator==(const __tree_iterator& __x, const __tree_iterator& __y)
        {return __x.__ptr_ == __y.__ptr_;}
    friend  bool operator!=(const __tree_iterator& __x, const __tree_iterator& __y)
        {return !(__x == __y);}

private:

    explicit __tree_iterator(__node_pointer __p) : __ptr_(__p) {}
    explicit __tree_iterator(__end_node_pointer __p) : __ptr_(__p) {}
    __node_pointer __get_np() const { return static_cast<__node_pointer>(__ptr_); }
    template <class, class, class> friend class __tree;
    template <class, class, class> friend class __tree_const_iterator;
    template <class> friend class __map_iterator;
    template <class, class, class, class> friend class map;
    template <class, class, class, class> friend class multimap;
    template <class, class, class> friend class set;
    template <class, class, class> friend class multiset;
};
