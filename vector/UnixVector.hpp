template <class _Tp, class _Allocator /* = allocator<_Tp> */>
class _LIBCPP_TEMPLATE_VIS vector
    : private __vector_base<_Tp, _Allocator>
{
    private:
        typedef __vector_base<_Tp, _Allocator>           __base;
        typedef allocator<_Tp>                           __default_allocator_type;
    
    public:
        
        typedef vector                                   __self;
        typedef _Tp                                      value_type;
        typedef _Allocator                               allocator_type;
        typedef typename __base::__alloc_traits          __alloc_traits;
        typedef typename __base::reference               reference;
        typedef typename __base::const_reference         const_reference;
        typedef typename __base::size_type               size_type;
        typedef typename __base::difference_type         difference_type;
        typedef typename __base::pointer                 pointer;
        typedef typename __base::const_pointer           const_pointer;
        typedef __wrap_iter<pointer>                     iterator;
        typedef __wrap_iter<const_pointer>               const_iterator;
        typedef _VSTD::reverse_iterator<iterator>         reverse_iterator;
        typedef _VSTD::reverse_iterator<const_iterator>   const_reverse_iterator;

    static_assert((is_same<typename allocator_type::value_type, value_type>::value),
                  "Allocator::value_type must be same type as value_type");

    _LIBCPP_INLINE_VISIBILITY
    vector() _NOEXCEPT_(is_nothrow_default_constructible<allocator_type>::value)
        {
            __get_db()->__insert_c(this);
        }
    _LIBCPP_INLINE_VISIBILITY explicit vector(const allocator_type& __a)
        _NOEXCEPT_(is_nothrow_copy_constructible<allocator_type>::value)
        : __base(__a)
    {
        __get_db()->__insert_c(this);
    }
    explicit vector(size_type __n);
    explicit vector(size_type __n, const allocator_type& __a);
    vector(size_type __n, const value_type& __x);
    vector(size_type __n, const value_type& __x, const allocator_type& __a);
    template <class _InputIterator>
        vector(_InputIterator __first,
               typename enable_if<__is_cpp17_input_iterator  <_InputIterator>::value &&
                                 !__is_cpp17_forward_iterator<_InputIterator>::value &&
                                 is_constructible<
                                    value_type,
                                    typename iterator_traits<_InputIterator>::reference>::value,
                                 _InputIterator>::type __last);
    template <class _InputIterator>
        vector(_InputIterator __first, _InputIterator __last, const allocator_type& __a,
               typename enable_if<__is_cpp17_input_iterator  <_InputIterator>::value &&
                                 !__is_cpp17_forward_iterator<_InputIterator>::value &&
                                 is_constructible<
                                    value_type,
                                    typename iterator_traits<_InputIterator>::reference>::value>::type* = 0);
    template <class _ForwardIterator>
        vector(_ForwardIterator __first,
               typename enable_if<__is_cpp17_forward_iterator<_ForwardIterator>::value &&
                                 is_constructible<
                                    value_type,
                                    typename iterator_traits<_ForwardIterator>::reference>::value,
                                 _ForwardIterator>::type __last);
    template <class _ForwardIterator>
        vector(_ForwardIterator __first, _ForwardIterator __last, const allocator_type& __a,
               typename enable_if<__is_cpp17_forward_iterator<_ForwardIterator>::value &&
                                 is_constructible<
                                    value_type,
                                    typename iterator_traits<_ForwardIterator>::reference>::value>::type* = 0);

    _LIBCPP_INLINE_VISIBILITY
    ~vector()
    {
        __annotate_delete();
        __get_db()->__erase_c(this);
    }

    vector(const vector& __x);
    vector(const vector& __x, const allocator_type& __a);
    _LIBCPP_INLINE_VISIBILITY
    vector& operator=(const vector& __x);

    _LIBCPP_INLINE_VISIBILITY
    vector(initializer_list<value_type> __il);

    _LIBCPP_INLINE_VISIBILITY
    vector(initializer_list<value_type> __il, const allocator_type& __a);

    _LIBCPP_INLINE_VISIBILITY
    vector(vector&& __x)
        _NOEXCEPT;

    _LIBCPP_INLINE_VISIBILITY
    vector(vector&& __x, const allocator_type& __a);
    _LIBCPP_INLINE_VISIBILITY
    vector& operator=(vector&& __x)
        _NOEXCEPT_((__noexcept_move_assign_container<_Allocator, __alloc_traits>::value));

    _LIBCPP_INLINE_VISIBILITY
    vector& operator=(initializer_list<value_type> __il)
        {assign(__il.begin(), __il.end()); return *this;}

    template <class _InputIterator>
        typename enable_if
        <
             __is_cpp17_input_iterator  <_InputIterator>::value &&
            !__is_cpp17_forward_iterator<_InputIterator>::value &&
            is_constructible<
                 value_type,
                 typename iterator_traits<_InputIterator>::reference>::value,
            void
        >::type
        assign(_InputIterator __first, _InputIterator __last);
    template <class _ForwardIterator>
        typename enable_if
        <
            __is_cpp17_forward_iterator<_ForwardIterator>::value &&
            is_constructible<
                 value_type,
                 typename iterator_traits<_ForwardIterator>::reference>::value,
            void
        >::type
        assign(_ForwardIterator __first, _ForwardIterator __last);

    void assign(size_type __n, const_reference __u);

    _LIBCPP_INLINE_VISIBILITY
    void assign(initializer_list<value_type> __il)
        {assign(__il.begin(), __il.end());}

    _LIBCPP_INLINE_VISIBILITY
    allocator_type get_allocator() const _NOEXCEPT
        {return this->__alloc();}

    _LIBCPP_INLINE_VISIBILITY iterator               begin() _NOEXCEPT;
    _LIBCPP_INLINE_VISIBILITY const_iterator         begin()   const _NOEXCEPT;
    _LIBCPP_INLINE_VISIBILITY iterator               end() _NOEXCEPT;
    _LIBCPP_INLINE_VISIBILITY const_iterator         end()     const _NOEXCEPT;

    _LIBCPP_INLINE_VISIBILITY
    reverse_iterator       rbegin() _NOEXCEPT
        {return       reverse_iterator(end());}
    _LIBCPP_INLINE_VISIBILITY
    const_reverse_iterator rbegin()  const _NOEXCEPT
        {return const_reverse_iterator(end());}
    _LIBCPP_INLINE_VISIBILITY
    reverse_iterator       rend() _NOEXCEPT
        {return       reverse_iterator(begin());}
    _LIBCPP_INLINE_VISIBILITY
    const_reverse_iterator rend()    const _NOEXCEPT
        {return const_reverse_iterator(begin());}

    _LIBCPP_INLINE_VISIBILITY
    const_iterator         cbegin()  const _NOEXCEPT
        {return begin();}
    _LIBCPP_INLINE_VISIBILITY
    const_iterator         cend()    const _NOEXCEPT
        {return end();}
    _LIBCPP_INLINE_VISIBILITY
    const_reverse_iterator crbegin() const _NOEXCEPT
        {return rbegin();}
    _LIBCPP_INLINE_VISIBILITY
    const_reverse_iterator crend()   const _NOEXCEPT
        {return rend();}

    _LIBCPP_INLINE_VISIBILITY
    size_type size() const _NOEXCEPT
        {return static_cast<size_type>(this->__end_ - this->__begin_);}
    _LIBCPP_INLINE_VISIBILITY
    size_type capacity() const _NOEXCEPT
        {return __base::capacity();}
    _LIBCPP_NODISCARD_AFTER_CXX17 _LIBCPP_INLINE_VISIBILITY
    bool empty() const _NOEXCEPT
        {return this->__begin_ == this->__end_;}
    size_type max_size() const _NOEXCEPT;
    void reserve(size_type __n);
    void shrink_to_fit() _NOEXCEPT;

    _LIBCPP_INLINE_VISIBILITY reference       operator[](size_type __n) _NOEXCEPT;
    _LIBCPP_INLINE_VISIBILITY const_reference operator[](size_type __n) const _NOEXCEPT;
    reference       at(size_type __n);
    const_reference at(size_type __n) const;

    _LIBCPP_INLINE_VISIBILITY reference       front() _NOEXCEPT
    {
        _LIBCPP_ASSERT(!empty(), "front() called for empty vector");
        return *this->__begin_;
    }
    _LIBCPP_INLINE_VISIBILITY const_reference front() const _NOEXCEPT
    {
        _LIBCPP_ASSERT(!empty(), "front() called for empty vector");
        return *this->__begin_;
    }
    _LIBCPP_INLINE_VISIBILITY reference       back() _NOEXCEPT
    {
        _LIBCPP_ASSERT(!empty(), "back() called for empty vector");
        return *(this->__end_ - 1);
    }
    _LIBCPP_INLINE_VISIBILITY const_reference back()  const _NOEXCEPT
    {
        _LIBCPP_ASSERT(!empty(), "back() called for empty vector");
        return *(this->__end_ - 1);
    }

    _LIBCPP_INLINE_VISIBILITY
    value_type*       data() _NOEXCEPT
        {return _VSTD::__to_address(this->__begin_);}
    _LIBCPP_INLINE_VISIBILITY
    const value_type* data() const _NOEXCEPT
        {return _VSTD::__to_address(this->__begin_);}

    template <class _Arg>
    _LIBCPP_INLINE_VISIBILITY
    void __emplace_back(_Arg&& __arg) {
      emplace_back(_VSTD::forward<_Arg>(__arg));
    }

    _LIBCPP_INLINE_VISIBILITY void push_back(const_reference __x);

    _LIBCPP_INLINE_VISIBILITY void push_back(value_type&& __x);

    template <class... _Args>
        _LIBCPP_INLINE_VISIBILITY
        reference emplace_back(_Args&&... __args);

    _LIBCPP_INLINE_VISIBILITY
    void pop_back();

    iterator insert(const_iterator __position, const_reference __x);

    iterator insert(const_iterator __position, value_type&& __x);
    template <class... _Args>
        iterator emplace(const_iterator __position, _Args&&... __args);

    iterator insert(const_iterator __position, size_type __n, const_reference __x);
    template <class _InputIterator>
        typename enable_if
        <
             __is_cpp17_input_iterator  <_InputIterator>::value &&
            !__is_cpp17_forward_iterator<_InputIterator>::value &&
            is_constructible<
                 value_type,
                 typename iterator_traits<_InputIterator>::reference>::value,
            iterator
        >::type
        insert(const_iterator __position, _InputIterator __first, _InputIterator __last);
    template <class _ForwardIterator>
        typename enable_if
        <
            __is_cpp17_forward_iterator<_ForwardIterator>::value &&
            is_constructible<
                 value_type,
                 typename iterator_traits<_ForwardIterator>::reference>::value,
            iterator
        >::type
        insert(const_iterator __position, _ForwardIterator __first, _ForwardIterator __last);

    _LIBCPP_INLINE_VISIBILITY
    iterator insert(const_iterator __position, initializer_list<value_type> __il)
        {return insert(__position, __il.begin(), __il.end());}

    _LIBCPP_INLINE_VISIBILITY iterator erase(const_iterator __position);
    iterator erase(const_iterator __first, const_iterator __last);

    _LIBCPP_INLINE_VISIBILITY
    void clear() _NOEXCEPT
    {
        size_type __old_size = size();
        __base::clear();
        __annotate_shrink(__old_size);
        __invalidate_all_iterators();
    }

    void resize(size_type __sz);
    void resize(size_type __sz, const_reference __x);

    void swap(vector&)
        _NOEXCEPT;
    bool __invariants() const;


    bool __dereferenceable(const const_iterator* __i) const;
    bool __decrementable(const const_iterator* __i) const;
    bool __addable(const const_iterator* __i, ptrdiff_t __n) const;
    bool __subscriptable(const const_iterator* __i, ptrdiff_t __n) const;


private:
    _LIBCPP_INLINE_VISIBILITY void __invalidate_all_iterators();
    _LIBCPP_INLINE_VISIBILITY void __invalidate_iterators_past(pointer __new_last);
    void __vallocate(size_type __n);
    void __vdeallocate() _NOEXCEPT;
    _LIBCPP_INLINE_VISIBILITY size_type __recommend(size_type __new_size) const;
    void __construct_at_end(size_type __n);
    _LIBCPP_INLINE_VISIBILITY
    void __construct_at_end(size_type __n, const_reference __x);
    template <class _ForwardIterator>
        typename enable_if
        <
            __is_cpp17_forward_iterator<_ForwardIterator>::value,
            void
        >::type
        __construct_at_end(_ForwardIterator __first, _ForwardIterator __last, size_type __n);
    void __append(size_type __n);
    void __append(size_type __n, const_reference __x);
    _LIBCPP_INLINE_VISIBILITY
    iterator       __make_iter(pointer __p) _NOEXCEPT;
    _LIBCPP_INLINE_VISIBILITY
    const_iterator __make_iter(const_pointer __p) const _NOEXCEPT;
    void __swap_out_circular_buffer(__split_buffer<value_type, allocator_type&>& __v);
    pointer __swap_out_circular_buffer(__split_buffer<value_type, allocator_type&>& __v, pointer __p);
    void __move_range(pointer __from_s, pointer __from_e, pointer __to);
    void __move_assign(vector& __c, true_type)
        _NOEXCEPT_(is_nothrow_move_assignable<allocator_type>::value);
    void __move_assign(vector& __c, false_type)
        _NOEXCEPT_(__alloc_traits::is_always_equal::value);
    _LIBCPP_INLINE_VISIBILITY
    void __destruct_at_end(pointer __new_last) _NOEXCEPT
    {
        __invalidate_iterators_past(__new_last);
        size_type __old_size = size();
        __base::__destruct_at_end(__new_last);
        __annotate_shrink(__old_size);
    }

    template <class _Up>
    _LIBCPP_INLINE_VISIBILITY
    inline void __push_back_slow_path(_Up&& __x);

    template <class... _Args>
    _LIBCPP_INLINE_VISIBILITY
    inline void __emplace_back_slow_path(_Args&&... __args);

    // The following functions are no-ops outside of AddressSanitizer mode.
    // We call annotatations only for the default Allocator because other allocators
    // may not meet the AddressSanitizer alignment constraints.
    // See the documentation for __sanitizer_annotate_contiguous_container for more details.
#ifndef _LIBCPP_HAS_NO_ASAN
    void __annotate_contiguous_container(const void *__beg, const void *__end,
                                         const void *__old_mid,
                                         const void *__new_mid) const
    {

      if (__beg && is_same<allocator_type, __default_allocator_type>::value)
        __sanitizer_annotate_contiguous_container(__beg, __end, __old_mid, __new_mid);
    }
#else
    _LIBCPP_INLINE_VISIBILITY
    void __annotate_contiguous_container(const void*, const void*, const void*,
                                         const void*) const _NOEXCEPT {}
#endif
    _LIBCPP_INLINE_VISIBILITY
    void __annotate_new(size_type __current_size) const _NOEXCEPT {
      __annotate_contiguous_container(data(), data() + capacity(),
                                      data() + capacity(), data() + __current_size);
    }

    _LIBCPP_INLINE_VISIBILITY
    void __annotate_delete() const _NOEXCEPT {
      __annotate_contiguous_container(data(), data() + capacity(),
                                      data() + size(), data() + capacity());
    }

    _LIBCPP_INLINE_VISIBILITY
    void __annotate_increase(size_type __n) const _NOEXCEPT
    {
      __annotate_contiguous_container(data(), data() + capacity(),
                                      data() + size(), data() + size() + __n);
    }

    _LIBCPP_INLINE_VISIBILITY
    void __annotate_shrink(size_type __old_size) const _NOEXCEPT
    {
      __annotate_contiguous_container(data(), data() + capacity(),
                                      data() + __old_size, data() + size());
    }

  struct _ConstructTransaction {
    explicit _ConstructTransaction(vector &__v, size_type __n)
      : __v_(__v),  __pos_(__v.__end_), __new_end_(__v.__end_ + __n) {
      __v_.__annotate_increase(__n);
    }
    ~_ConstructTransaction() {
      __v_.__end_ = __pos_;
      if (__pos_ != __new_end_) {
        __v_.__annotate_shrink(__new_end_ - __v_.__begin_);
      }
    }

    vector &__v_;
    pointer __pos_;
    const_pointer const __new_end_;

  private:
    _ConstructTransaction(_ConstructTransaction const&) = delete;
    _ConstructTransaction& operator=(_ConstructTransaction const&) = delete;
  };

  template <class ..._Args>
  _LIBCPP_INLINE_VISIBILITY
  void __construct_one_at_end(_Args&& ...__args) {
    _ConstructTransaction __tx(*this, 1);
    __alloc_traits::construct(this->__alloc(), _VSTD::__to_address(__tx.__pos_),
        _VSTD::forward<_Args>(__args)...);
    ++__tx.__pos_;
  }
};
