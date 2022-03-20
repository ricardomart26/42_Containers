#ifndef UNIXVECTORBASE_HPP
#define UNIXVECTORBASE_HPP


template <bool>
class __vector_base_common
{
protected:
    __v_ector_base_common() {}
    void __throw_length_error() const
    {
        _VSTD::__throw_length_error("vector");
    }
    void __throw_out_of_range() const
    {
        _VSTD::__throw_out_of_range("vector");
    } 
};

template <class _Tp, class _Allocator>
class __vector_base
    : protected __vector_base_common<true>
{
    public:
        typedef _Allocator                               allocator_type;
        typedef allocator_traits<allocator_type>         __alloc_traits;
        typedef typename __alloc_traits::size_type       size_type;
    
    protected:
        typedef _Tp                                      value_type;
        typedef value_type&                              reference;
        typedef const value_type&                        const_reference;
        typedef typename __alloc_traits::difference_type difference_type;
        typedef typename __alloc_traits::pointer         pointer;
        typedef typename __alloc_traits::const_pointer   const_pointer;
        typedef pointer                                  iterator;
        typedef const_pointer                            const_iterator;

        pointer                                         __begin_;
        pointer                                         __end_;
        __compressed_pair<pointer, allocator_type> __end_cap_;


        allocator_type& __alloc() _NOEXCEPT {return __end_cap_.second();}

        const allocator_type& __alloc() const _NOEXCEPT {return __end_cap_.second();}

        pointer& __end_cap() _NOEXCEPT {return __end_cap_.first();}

        const pointer& __end_cap() const _NOEXCEPT {return __end_cap_.first();}

        __vector_base()
            _NOEXCEPT_(is_nothrow_default_constructible<allocator_type>::value)
            : __begin_(nullptr), __end_(nullptr), __end_cap_(nullptr, __default_init_tag()) {}
        
        __vector_base(const allocator_type& __a)
        : __begin_(nullptr), __end_(nullptr), __end_cap_(nullptr, __a) {}
        
        __vector_base(allocator_type&& __a) _NOEXCEPT
            : __begin_(nullptr), __end_(nullptr), __end_cap_(nullptr, std::move(__a)) {}

        ~__vector_base()
        {
            if (__begin_ != nullptr)
            {
                clear();
                __alloc_traits::deallocate(__alloc(), __begin_, capacity());
            }
        }
        
        void clear() _NOEXCEPT {__destruct_at_end(__begin_);}
        
        size_type capacity() const _NOEXCEPT {return static_cast<size_type>(__end_cap() - __begin_);}

        void __destruct_at_end(pointer __new_last) _NOEXCEPT
        {
            pointer __soon_to_be_end = __end_;
            while (__new_last != __soon_to_be_end)
                __alloc_traits::destroy(__alloc(), _VSTD::__to_address(--__soon_to_be_end));
            __end_ = __new_last;
        }

        void __copy_assign_alloc(const __vector_base& __c)
            {__copy_assign_alloc(__c, integral_constant<bool,__alloc_traits::propagate_on_container_copy_assignment::value>());}

        void __move_assign_alloc(__vector_base& __c)
            _NOEXCEPT_(!__alloc_traits::propagate_on_container_move_assignment::value || is_nothrow_move_assignable<allocator_type>::value)
            {__move_assign_alloc(__c, integral_constant<bool, __alloc_traits::propagate_on_container_move_assignment::value>());}


    private:

        void __copy_assign_alloc(const __vector_base& __c, true_type)
        {
            if (__alloc() != __c.__alloc())
            {
                clear();
                __alloc_traits::deallocate(__alloc(), __begin_, capacity());
                __begin_ = __end_ = __end_cap() = nullptr;
            }
            __alloc() = __c.__alloc();
        }

        void __copy_assign_alloc(const __vector_base&, false_type) {}

        void __move_assign_alloc(__vector_base& __c, true_type) _NOEXCEPT_(is_nothrow_move_assignable<allocator_type>::value) {__alloc() = _VSTD::move(__c.__alloc());}

        void __move_assign_alloc(__vector_base&, false_type) _NOEXCEPT {}
};



template <class _Tp, class _Allocator /* = allocator<_Tp> */>
class vector
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

    vector() _NOEXCEPT_(is_nothrow_default_constructible<allocator_type>::value)
    {
        __get_db()->__insert_c(this);
    }

    explicit vector(const allocator_type& __a)
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

    ~vector()
    {
        __annotate_delete();
        __get_db()->__erase_c(this);
    }

    vector(const vector& __x);
    vector(const vector& __x, const allocator_type& __a);
    vector& operator=(const vector& __x);

    vector(initializer_list<value_type> __il);

    vector(initializer_list<value_type> __il, const allocator_type& __a);

    vector(vector&& __x) _NOEXCEPT;

    vector(vector&& __x, const allocator_type& __a);
    vector& operator=(vector&& __x)
        _NOEXCEPT_((__noexcept_move_assign_container<_Allocator, __alloc_traits>::value));

    vector& operator=(initializer_list<value_type> __il)
        {assign(__il.begin(), __il.end()); return *this;}

    template <class _InputIterator>
        typename enable_if
        <__is_cpp17_input_iterator  <_InputIterator>::value && !__is_cpp17_forward_iterator<_InputIterator>::value &&
        is_constructible<value_type, typename iterator_traits<_InputIterator>::reference>::value, void>::type
        assign(_InputIterator __first, _InputIterator __last);
    
    template <class _ForwardIterator>
        typename enable_if
        <__is_cpp17_forward_iterator<_ForwardIterator>::value && is_constructible<value_type, typename iterator_traits<_ForwardIterator>::reference>::value, void>::type
        assign(_ForwardIterator __first, _ForwardIterator __last);

    void assign(size_type __n, const_reference __u);

    void assign(initializer_list<value_type> __il)
        {assign(__il.begin(), __il.end());}

    allocator_type get_allocator() const _NOEXCEPT
        {return this->__alloc();}

    iterator               begin() _NOEXCEPT;
    const_iterator         begin()   const _NOEXCEPT;
    iterator               end() _NOEXCEPT;
    const_iterator         end()     const _NOEXCEPT;

    reverse_iterator       rbegin() _NOEXCEPT
        {return       reverse_iterator(end());}
    
    const_reverse_iterator rbegin()  const _NOEXCEPT
        {return const_reverse_iterator(end());}
    
    reverse_iterator       rend() _NOEXCEPT
        {return       reverse_iterator(begin());}
    
    const_reverse_iterator rend()    const _NOEXCEPT
        {return const_reverse_iterator(begin());}

    
    const_iterator         cbegin()  const _NOEXCEPT
        {return begin();}
    
    const_iterator         cend()    const _NOEXCEPT
        {return end();}
    
    const_reverse_iterator crbegin() const _NOEXCEPT
        {return rbegin();}
    
    const_reverse_iterator crend()   const _NOEXCEPT
        {return rend();}

    size_type size() const _NOEXCEPT
        {return static_cast<size_type>(this->__end_ - this->__begin_);}
    
    size_type capacity() const _NOEXCEPT
        {return __base::capacity();}
    bool empty() const _NOEXCEPT
        {return this->__begin_ == this->__end_;}
    size_type max_size() const _NOEXCEPT;
    void reserve(size_type __n);
    void shrink_to_fit() _NOEXCEPT;

    reference       operator[](size_type __n) _NOEXCEPT;
    const_reference operator[](size_type __n) const _NOEXCEPT;
    reference       at(size_type __n);
    const_reference at(size_type __n) const;

    reference       front() _NOEXCEPT
    {
        _LIBCPP_ASSERT(!empty(), "front() called for empty vector");
        return *this->__begin_;
    }
    const_reference front() const _NOEXCEPT
    {
        _LIBCPP_ASSERT(!empty(), "front() called for empty vector");
        return *this->__begin_;
    }
    reference       back() _NOEXCEPT
    {
        _LIBCPP_ASSERT(!empty(), "back() called for empty vector");
        return *(this->__end_ - 1);
    }
    const_reference back()  const _NOEXCEPT
    {
        _LIBCPP_ASSERT(!empty(), "back() called for empty vector");
        return *(this->__end_ - 1);
    }

    value_type*       data() _NOEXCEPT
        {return _VSTD::__to_address(this->__begin_);}

    const value_type* data() const _NOEXCEPT
        {return _VSTD::__to_address(this->__begin_);}

    template <class _Arg>

    void __emplace_back(_Arg&& __arg) {
      emplace_back(_VSTD::forward<_Arg>(__arg));
    }

    void push_back(const_reference __x);

    void push_back(value_type&& __x);

    template <class... _Args>
        reference emplace_back(_Args&&... __args);

    void pop_back();

    iterator insert(const_iterator __position, const_reference __x);

    iterator insert(const_iterator __position, value_type&& __x);
    template <class... _Args>
        iterator emplace(const_iterator __position, _Args&&... __args);

    iterator insert(const_iterator __position, size_type __n, const_reference __x);
    template <class _InputIterator>
        typename enable_if
        <  __is_cpp17_input_iterator  <_InputIterator>::value && !__is_cpp17_forward_iterator<_InputIterator>::value &&
            is_constructible< value_type, typename iterator_traits<_InputIterator>::reference>::value, iterator>::type
        insert(const_iterator __position, _InputIterator __first, _InputIterator __last);
    template <class _ForwardIterator>
        typename enable_if <__is_cpp17_forward_iterator<_ForwardIterator>::value &&
            is_constructible<value_type, typename iterator_traits<_ForwardIterator>::reference>::value, iterator>::type
        insert(const_iterator __position, _ForwardIterator __first, _ForwardIterator __last);

    iterator insert(const_iterator __position, initializer_list<value_type> __il)
        {return insert(__position, __il.begin(), __il.end());}

    iterator erase(const_iterator __position);
    iterator erase(const_iterator __first, const_iterator __last);

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
    void __invalidate_all_iterators();
    void __invalidate_iterators_past(pointer __new_last);
    void __vallocate(size_type __n);
    void __vdeallocate() _NOEXCEPT;
    size_type __recommend(size_type __new_size) const;
    void __construct_at_end(size_type __n);
    void __construct_at_end(size_type __n, const_reference __x);
    template <class _ForwardIterator>
        typename enable_if <__is_cpp17_forward_iterator<_ForwardIterator>::value, void>::type
        __construct_at_end(_ForwardIterator __first, _ForwardIterator __last, size_type __n);
    void __append(size_type __n);
    void __append(size_type __n, const_reference __x);
    iterator       __make_iter(pointer __p) _NOEXCEPT;
    const_iterator __make_iter(const_pointer __p) const _NOEXCEPT;
    void __swap_out_circular_buffer(__split_buffer<value_type, allocator_type&>& __v);
    pointer __swap_out_circular_buffer(__split_buffer<value_type, allocator_type&>& __v, pointer __p);
    void __move_range(pointer __from_s, pointer __from_e, pointer __to);
    void __move_assign(vector& __c, true_type)
        _NOEXCEPT_(is_nothrow_move_assignable<allocator_type>::value);
    void __move_assign(vector& __c, false_type)
        _NOEXCEPT_(__alloc_traits::is_always_equal::value);
    void __destruct_at_end(pointer __new_last) _NOEXCEPT
    {
        __invalidate_iterators_past(__new_last);
        size_type __old_size = size();
        __base::__destruct_at_end(__new_last);
        __annotate_shrink(__old_size);
    }

    template <class _Up>
    inline void __push_back_slow_path(_Up&& __x);

    template <class... _Args>
    inline void __emplace_back_slow_path(_Args&&... __args);

    // The following functions are no-ops outside of AddressSanitizer mode.
    // We call annotatations only for the default Allocator because other allocators
    // may not meet the AddressSanitizer alignment constraints.
    // See the documentation for __sanitizer_annotate_contiguous_container for more details.
    void __annotate_contiguous_container(const void *__beg, const void *__end, const void *__old_mid, const void *__new_mid) const
    {
      if (__beg && is_same<allocator_type, __default_allocator_type>::value)
        __sanitizer_annotate_contiguous_container(__beg, __end, __old_mid, __new_mid);
    }

    void __annotate_new(size_type __current_size) const _NOEXCEPT 
    {
      __annotate_contiguous_container(data(), data() + capacity(), data() + capacity(), data() + __current_size);
    }

    void __annotate_delete() const _NOEXCEPT 
    {
      __annotate_contiguous_container(data(), data() + capacity(), data() + size(), data() + capacity());
    }

    void __annotate_increase(size_type __n) const _NOEXCEPT
    {
      __annotate_contiguous_container(data(), data() + capacity(), data() + size(), data() + size() + __n);
    }

    void __annotate_shrink(size_type __old_size) const _NOEXCEPT
    {
      __annotate_contiguous_container(data(), data() + capacity(), data() + __old_size, data() + size());
    }

  struct _ConstructTransaction 
  {
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
  void __construct_one_at_end(_Args&& ...__args) {
    _ConstructTransaction __tx(*this, 1);
    __alloc_traits::construct(this->__alloc(), _VSTD::__to_address(__tx.__pos_),
        _VSTD::forward<_Args>(__args)...);
    ++__tx.__pos_;
  }
};


template <class _Tp, class _Allocator>
void    vector<_Tp, _Allocator>::__swap_out_circular_buffer(__split_buffer<value_type, allocator_type&>& __v)
{

    __annotate_delete();
    __alloc_traits::__construct_backward_with_exception_guarantees(
        this->__alloc(), this->__begin_, this->__end_, __v.__begin_);
    _VSTD::swap(this->__begin_, __v.__begin_);
    _VSTD::swap(this->__end_, __v.__end_);
    _VSTD::swap(this->__end_cap(), __v.__end_cap());
    __v.__first_ = __v.__begin_;
    __annotate_new(size());
    __invalidate_all_iterators();
}

template <class _Tp, class _Allocator>
typename vector<_Tp, _Allocator>::pointer   vector<_Tp, _Allocator>::__swap_out_circular_buffer(__split_buffer<value_type, allocator_type&>& __v, pointer __p)
{
    __annotate_delete();
    pointer __r = __v.__begin_;
    __alloc_traits::__construct_backward_with_exception_guarantees(
        this->__alloc(), this->__begin_, __p, __v.__begin_);
    __alloc_traits::__construct_forward_with_exception_guarantees(
        this->__alloc(), __p, this->__end_, __v.__end_);
    _VSTD::swap(this->__begin_, __v.__begin_);
    _VSTD::swap(this->__end_, __v.__end_);
    _VSTD::swap(this->__end_cap(), __v.__end_cap());
    __v.__first_ = __v.__begin_;
    __annotate_new(size());
    __invalidate_all_iterators();
    return __r;
}

//  Allocate space for __n objects
//  throws length_error if __n > max_size()
//  throws (probably bad_alloc) if memory run out
//  Precondition:  __begin_ == __end_ == __end_cap() == 0
//  Precondition:  __n > 0
//  Postcondition:  capacity() == __n
//  Postcondition:  size() == 0
template <class _Tp, class _Allocator>
void    vector<_Tp, _Allocator>::__vallocate(size_type __n)
{
    if (__n > max_size())
        this->__throw_length_error();
    this->__begin_ = this->__end_ = __alloc_traits::allocate(this->__alloc(), __n);
    this->__end_cap() = this->__begin_ + __n;
    __annotate_new(0);
}

template <class _Tp, class _Allocator>
void    vector<_Tp, _Allocator>::__vdeallocate() _NOEXCEPT
{
    if (this->__begin_ != nullptr)
    {
        clear();
        __alloc_traits::deallocate(this->__alloc(), this->__begin_, capacity());
        this->__begin_ = this->__end_ = this->__end_cap() = nullptr;
    }
}

template <class _Tp, class _Allocator>
typename vector<_Tp, _Allocator>::size_type vector<_Tp, _Allocator>::max_size() const _NOEXCEPT
{
    return _VSTD::min<size_type>(__alloc_traits::max_size(this->__alloc()),
                                 numeric_limits<difference_type>::max());
}

//  Precondition:  __new_size > capacity()
template <class _Tp, class _Allocator>
typename vector<_Tp, _Allocator>::size_type vector<_Tp, _Allocator>::__recommend(size_type __new_size) const
{
    const size_type __ms = max_size();
    if (__new_size > __ms)
        this->__throw_length_error();
    const size_type __cap = capacity();
    if (__cap >= __ms / 2)
        return __ms;
    return _VSTD::max<size_type>(2*__cap, __new_size);
}

//  Default constructs __n objects starting at __end_
//  throws if construction throws
//  Precondition:  __n > 0
//  Precondition:  size() + __n <= capacity()
//  Postcondition:  size() == size() + __n
template <class _Tp, class _Allocator>
void
vector<_Tp, _Allocator>::__construct_at_end(size_type __n)
{
    _ConstructTransaction __tx(*this, __n);
    for (; __tx.__pos_ != __tx.__new_end_; ++__tx.__pos_) {
      __alloc_traits::construct(this->__alloc(), _VSTD::__to_address(__tx.__pos_));
    }
}

//  Copy constructs __n objects starting at __end_ from __x
//  throws if construction throws
//  Precondition:  __n > 0
//  Precondition:  size() + __n <= capacity()
//  Postcondition:  size() == old size() + __n
//  Postcondition:  [i] == __x for all i in [size() - __n, __n)
template <class _Tp, class _Allocator>
void vector<_Tp, _Allocator>::__construct_at_end(size_type __n, const_reference __x)
{
    _ConstructTransaction __tx(*this, __n);
    for (; __tx.__pos_ != __tx.__new_end_; ++__tx.__pos_) {
        __alloc_traits::construct(this->__alloc(), _VSTD::__to_address(__tx.__pos_), __x);
    }
}

template <class _Tp, class _Allocator>
template <class _ForwardIterator>
typename enable_if<__is_cpp17_forward_iterator<_ForwardIterator>::value, void>::type
vector<_Tp, _Allocator>::__construct_at_end(_ForwardIterator __first, _ForwardIterator __last, size_type __n)
{
    _ConstructTransaction __tx(*this, __n);
    __alloc_traits::__construct_range_forward(this->__alloc(), __first, __last, __tx.__pos_);
}

//  Default constructs __n objects starting at __end_
//  throws if construction throws
//  Postcondition:  size() == size() + __n
//  Exception safety: strong.
template <class _Tp, class _Allocator>
void
vector<_Tp, _Allocator>::__append(size_type __n)
{
    if (static_cast<size_type>(this->__end_cap() - this->__end_) >= __n)
        this->__construct_at_end(__n);
    else
    {
        allocator_type& __a = this->__alloc();
        __split_buffer<value_type, allocator_type&> __v(__recommend(size() + __n), size(), __a);
        __v.__construct_at_end(__n);
        __swap_out_circular_buffer(__v);
    }
}

//  Default constructs __n objects starting at __end_
//  throws if construction throws
//  Postcondition:  size() == size() + __n
//  Exception safety: strong.
template <class _Tp, class _Allocator>
void    vector<_Tp, _Allocator>::__append(size_type __n, const_reference __x)
{
    if (static_cast<size_type>(this->__end_cap() - this->__end_) >= __n)
        this->__construct_at_end(__n, __x);
    else
    {
        allocator_type& __a = this->__alloc();
        __split_buffer<value_type, allocator_type&> __v(__recommend(size() + __n), size(), __a);
        __v.__construct_at_end(__n, __x);
        __swap_out_circular_buffer(__v);
    }
}

template <class _Tp, class _Allocator>
vector<_Tp, _Allocator>::vector(size_type __n)
{
    if (__n > 0)
    {
        __vallocate(__n);
        __construct_at_end(__n);
    }
}

template <class _Tp, class _Allocator>
vector<_Tp, _Allocator>::vector(size_type __n, const value_type& __x)
{
    if (__n > 0)
    {
        __vallocate(__n);
        __construct_at_end(__n, __x);
    }
}

template <class _Tp, class _Allocator>
vector<_Tp, _Allocator>::vector(size_type __n, const value_type& __x, const allocator_type& __a)
    : __base(__a)
{
    if (__n > 0)
    {
        __vallocate(__n);
        __construct_at_end(__n, __x);
    }
}

template <class _Tp, class _Allocator>
template <class _InputIterator>
vector<_Tp, _Allocator>::vector(_InputIterator __first, typename enable_if<__is_cpp17_input_iterator  <_InputIterator>::value && !__is_cpp17_forward_iterator<_InputIterator>::value &&
                         is_constructible< value_type, typename iterator_traits<_InputIterator>::reference>::value, _InputIterator>::type __last)
{
    for (; __first != __last; ++__first)
        __emplace_back(*__first);
}

template <class _Tp, class _Allocator>
template <class _InputIterator>
vector<_Tp, _Allocator>::vector(_InputIterator __first, _InputIterator __last, const allocator_type& __a,
       typename enable_if<__is_cpp17_input_iterator  <_InputIterator>::value && !__is_cpp17_forward_iterator<_InputIterator>::value &&
                         is_constructible<value_type, typename iterator_traits<_InputIterator>::reference>::value>::type*)
    : __base(__a)
{
    for (; __first != __last; ++__first)
        __emplace_back(*__first);
}

template <class _Tp, class _Allocator>
template <class _ForwardIterator>
vector<_Tp, _Allocator>::vector(_ForwardIterator __first, typename enable_if<__is_cpp17_forward_iterator<_ForwardIterator>::value &&
                                is_constructible< value_type, typename iterator_traits<_ForwardIterator>::reference>::value, _ForwardIterator>::type __last)
{
    size_type __n = static_cast<size_type>(_VSTD::distance(__first, __last));
    if (__n > 0)
    {
        __vallocate(__n);
        __construct_at_end(__first, __last, __n);
    }
}

template <class _Tp, class _Allocator>
template <class _ForwardIterator>
vector<_Tp, _Allocator>::vector(_ForwardIterator __first, _ForwardIterator __last, const allocator_type& __a, typename enable_if<__is_cpp17_forward_iterator<_ForwardIterator>::value &&
                                is_constructible<value_type, typename iterator_traits<_ForwardIterator>::reference>::value>::type*)
    : __base(__a)
{
    size_type __n = static_cast<size_type>(_VSTD::distance(__first, __last));
    if (__n > 0)
    {
        __vallocate(__n);
        __construct_at_end(__first, __last, __n);
    }
}

template <class _Tp, class _Allocator>
vector<_Tp, _Allocator>::vector(const vector& __x)
    : __base(__alloc_traits::select_on_container_copy_construction(__x.__alloc()))
{
    size_type __n = __x.size();
    if (__n > 0)
    {
        __vallocate(__n);
        __construct_at_end(__x.__begin_, __x.__end_, __n);
    }
}

template <class _Tp, class _Allocator>
vector<_Tp, _Allocator>::vector(const vector& __x, const allocator_type& __a)
    : __base(__a)
{
    size_type __n = __x.size();
    if (__n > 0)
    {
        __vallocate(__n);
        __construct_at_end(__x.__begin_, __x.__end_, __n);
    }
}


template <class _Tp, class _Allocator>
vector<_Tp, _Allocator>::vector(vector&& __x) _NOEXCEPT_(is_nothrow_move_constructible<allocator_type>::value)
    : __base(_VSTD::move(__x.__alloc()))
{
    this->__begin_ = __x.__begin_;
    this->__end_ = __x.__end_;
    this->__end_cap() = __x.__end_cap();
    __x.__begin_ = __x.__end_ = __x.__end_cap() = nullptr;
}

template <class _Tp, class _Allocator>
vector<_Tp, _Allocator>::vector(vector&& __x, const allocator_type& __a)
    : __base(__a)
{
    if (__a == __x.__alloc())
    {
        this->__begin_ = __x.__begin_;
        this->__end_ = __x.__end_;
        this->__end_cap() = __x.__end_cap();
        __x.__begin_ = __x.__end_ = __x.__end_cap() = nullptr;
    }
    else
    {
        typedef move_iterator<iterator> _Ip;
        assign(_Ip(__x.begin()), _Ip(__x.end()));
    }
}

template <class _Tp, class _Allocator>
inline _LIBCPP_INLINE_VISIBILITY
vector<_Tp, _Allocator>::vector(initializer_list<value_type> __il)
{
    if (__il.size() > 0)
    {
        __vallocate(__il.size());
        __construct_at_end(__il.begin(), __il.end(), __il.size());
    }
}

template <class _Tp, class _Allocator>
vector<_Tp, _Allocator>::vector(initializer_list<value_type> __il, const allocator_type& __a)
    : __base(__a)
{
    if (__il.size() > 0)
    {
        __vallocate(__il.size());
        __construct_at_end(__il.begin(), __il.end(), __il.size());
    }
}

template <class _Tp, class _Allocator>
vector<_Tp, _Allocator>& vector<_Tp, _Allocator>::operator=(vector&& __x) _NOEXCEPT_((__noexcept_move_assign_container<_Allocator, __alloc_traits>::value))
{
    __move_assign(__x, integral_constant<bool,
          __alloc_traits::propagate_on_container_move_assignment::value>());
    return *this;
}

template <class _Tp, class _Allocator>
void vector<_Tp, _Allocator>::__move_assign(vector& __c, false_type) _NOEXCEPT_(__alloc_traits::is_always_equal::value)
{
    if (__base::__alloc() != __c.__alloc())
    {
        typedef move_iterator<iterator> _Ip;
        assign(_Ip(__c.begin()), _Ip(__c.end()));
    }
    else
        __move_assign(__c, true_type());
}

template <class _Tp, class _Allocator>
void vector<_Tp, _Allocator>::__move_assign(vector& __c, true_type) _NOEXCEPT_(is_nothrow_move_assignable<allocator_type>::value)
{
    __vdeallocate();
    __base::__move_assign_alloc(__c); // this can throw
    this->__begin_ = __c.__begin_;
    this->__end_ = __c.__end_;
    this->__end_cap() = __c.__end_cap();
    __c.__begin_ = __c.__end_ = __c.__end_cap() = nullptr;
}

template <class _Tp, class _Allocator>
vector<_Tp, _Allocator>& vector<_Tp, _Allocator>::operator=(const vector& __x)
{
    if (this != &__x)
    {
        __base::__copy_assign_alloc(__x);
        assign(__x.__begin_, __x.__end_);
    }
    return *this;
}

template <class _Tp, class _Allocator>
template <class _InputIterator>
typename enable_if < __is_cpp17_input_iterator  <_InputIterator>::value && !__is_cpp17_forward_iterator<_InputIterator>::value && is_constructible<_Tp, typenamE iterator_traits<_InputIterator>::reference>::value, void>::type
vector<_Tp, _Allocator>::assign(_InputIterator __first, _InputIterator __last)
{
    clear();
    for (; __first != __last; ++__first)
        __emplace_back(*__first);
}

template <class _Tp, class _Allocator>
template <class _ForwardIterator>
typename enable_if <__is_cpp17_forward_iterator<_ForwardIterator>::value && is_constructible<_Tp, typename iterator_traits<_ForwardIterator>::reference>::value, void>::type
vector<_Tp, _Allocator>::assign(_ForwardIterator __first, _ForwardIterator __last)
{
    size_type __new_size = static_cast<size_type>(_VSTD::distance(__first, __last));
    if (__new_size <= capacity())
    {
        _ForwardIterator __mid = __last;
        bool __growing = false;
        if (__new_size > size())
        {
            __growing = true;
            __mid =  __first;
            _VSTD::advance(__mid, size());
        }
        pointer __m = _VSTD::copy(__first, __mid, this->__begin_);
        if (__growing)
            __construct_at_end(__mid, __last, __new_size - size());
        else
            this->__destruct_at_end(__m);
    }
    else
    {
        __vdeallocate();
        __vallocate(__recommend(__new_size));
        __construct_at_end(__first, __last, __new_size);
    }
    __invalidate_all_iterators();
}

template <class _Tp, class _Allocator>
void vector<_Tp, _Allocator>::assign(size_type __n, const_reference __u)
{
    if (__n <= capacity())
    {
        size_type __s = size();
        _VSTD::fill_n(this->__begin_, _VSTD::min(__n, __s), __u);
        if (__n > __s)
            __construct_at_end(__n - __s, __u);
        else
            this->__destruct_at_end(this->__begin_ + __n);
    }
    else
    {
        __vdeallocate();
        __vallocate(__recommend(static_cast<size_type>(__n)));
        __construct_at_end(__n, __u);
    }
    __invalidate_all_iterators();
}

template <class _Tp, class _Allocator>
typename vector<_Tp, _Allocator>::iterator vector<_Tp, _Allocator>::__make_iter(pointer __p) _NOEXCEPT {return iterator(__p);}

template <class _Tp, class _Allocator>
typename vector<_Tp, _Allocator>::const_iterator    vector<_Tp, _Allocator>::__make_iter(const_pointer __p) const _NOEXCEPT {return const_iterator(__p);}

template <class _Tp, class _Allocator>
typename vector<_Tp, _Allocator>::iterator vector<_Tp, _Allocator>::begin() _NOEXCEPT {return __make_iter(this->__begin_);}

template <class _Tp, class _Allocator>
typename vector<_Tp, _Allocator>::const_iterator vector<_Tp, _Allocator>::begin() const _NOEXCEPT {return __make_iter(this->__begin_);}

template <class _Tp, class _Allocator>
typename vector<_Tp, _Allocator>::iterator vector<_Tp, _Allocator>::end() _NOEXCEPT {return __make_iter(this->__end_);}

template <class _Tp, class _Allocator>
typename vector<_Tp, _Allocator>::const_iterator    vector<_Tp, _Allocator>::end() const _NOEXCEPT {return __make_iter(this->__end_);}

template <class _Tp, class _Allocator>
typename vector<_Tp, _Allocator>::reference
vector<_Tp, _Allocator>::operator[](size_type __n) _NOEXCEPT
{
    _LIBCPP_ASSERT(__n < size(), "vector[] index out of bounds");
    return this->__begin_[__n];
}

template <class _Tp, class _Allocator>
typename vector<_Tp, _Allocator>::const_reference   vector<_Tp, _Allocator>::operator[](size_type __n) const _NOEXCEPT
{
    _LIBCPP_ASSERT(__n < size(), "vector[] index out of bounds");
    return this->__begin_[__n];
}

template <class _Tp, class _Allocator>
typename vector<_Tp, _Allocator>::reference vector<_Tp, _Allocator>::at(size_type __n)
{
    if (__n >= size())
        this->__throw_out_of_range();
    return this->__begin_[__n];
}

template <class _Tp, class _Allocator>
typename vector<_Tp, _Allocator>::const_reference   vector<_Tp, _Allocator>::at(size_type __n) const
{
    if (__n >= size())
        this->__throw_out_of_range();
    return this->__begin_[__n];
}

template <class _Tp, class _Allocator>
void    vector<_Tp, _Allocator>::reserve(size_type __n)
{
    if (__n > capacity())
    {
        allocator_type& __a = this->__alloc();
        __split_buffer<value_type, allocator_type&> __v(__n, size(), __a);
        __swap_out_circular_buffer(__v);
    }
}

template <class _Tp, class _Allocator>
void    vector<_Tp, _Allocator>::shrink_to_fit() _NOEXCEPT
{
    if (capacity() > size())
    {
        try
        {
            allocator_type& __a = this->__alloc();
            __split_buffer<value_type, allocator_type&> __v(size(), size(), __a);
            __swap_out_circular_buffer(__v);
        }
        catch (...)
        {}
    }
}

template <class _Tp, class _Allocator>
template <class _Up>
void vector<_Tp, _Allocator>::__push_back_slow_path(_Up&& __x)
{
    allocator_type& __a = this->__alloc();
    __split_buffer<value_type, allocator_type&> __v(__recommend(size() + 1), size(), __a);
    // __v.push_back(_VSTD::forward<_Up>(__x));
    __alloc_traits::construct(__a, _VSTD::__to_address(__v.__end_), _VSTD::forward<_Up>(__x));
    __v.__end_++;
    __swap_out_circular_buffer(__v);
}

template <class _Tp, class _Allocator>
void
vector<_Tp, _Allocator>::push_back(const_reference __x)
{
    if (this->__end_ != this->__end_cap())
    {
        __construct_one_at_end(__x);
    }
    else
        __push_back_slow_path(__x);
}


template <class _Tp, class _Allocator>
void vector<_Tp, _Allocator>::push_back(value_type&& __x)
{
    if (this->__end_ < this->__end_cap())
        __construct_one_at_end(_VSTD::move(__x));
    else
        __push_back_slow_path(_VSTD::move(__x));
}

template <class _Tp, class _Allocator>
template <class... _Args>
void vector<_Tp, _Allocator>::__emplace_back_slow_path(_Args&&... __args)
{
    allocator_type& __a = this->__alloc();
    __split_buffer<value_type, allocator_type&> __v(__recommend(size() + 1), size(), __a);
//    __v.emplace_back(_VSTD::forward<_Args>(__args)...);
    __alloc_traits::construct(__a, _VSTD::__to_address(__v.__end_), _VSTD::forward<_Args>(__args)...);
    __v.__end_++;
    __swap_out_circular_buffer(__v);
}

template <class _Tp, class _Allocator>
template <class... _Args>
void
vector<_Tp, _Allocator>::emplace_back(_Args&&... __args)
{
    if (this->__end_ < this->__end_cap())
    {
        __construct_one_at_end(_VSTD::forward<_Args>(__args)...);
    }
    else
        __emplace_back_slow_path(_VSTD::forward<_Args>(__args)...);
}

template <class _Tp, class _Allocator>
void
vector<_Tp, _Allocator>::pop_back()
{
    _LIBCPP_ASSERT(!empty(), "vector::pop_back called for empty vector");
    this->__destruct_at_end(this->__end_ - 1);
}

template <class _Tp, class _Allocator>
typename vector<_Tp, _Allocator>::iterator
vector<_Tp, _Allocator>::erase(const_iterator __position)
{
    _LIBCPP_ASSERT(__position != end(),
        "vector::erase(iterator) called with a non-dereferenceable iterator");
    difference_type __ps = __position - cbegin();
    pointer __p = this->__begin_ + __ps;
    this->__destruct_at_end(_VSTD::move(__p + 1, this->__end_, __p));
    this->__invalidate_iterators_past(__p-1);
    iterator __r = __make_iter(__p);
    return __r;
}

template <class _Tp, class _Allocator>
typename vector<_Tp, _Allocator>::iterator
vector<_Tp, _Allocator>::erase(const_iterator __first, const_iterator __last)
{
#if _LIBCPP_DEBUG_LEVEL >= 2
    _LIBCPP_ASSERT(__get_const_db()->__find_c_from_i(&__first) == this,
        "vector::erase(iterator,  iterator) called with an iterator not"
        " referring to this vector");
    _LIBCPP_ASSERT(__get_const_db()->__find_c_from_i(&__last) == this,
        "vector::erase(iterator,  iterator) called with an iterator not"
        " referring to this vector");
#endif
    _LIBCPP_ASSERT(__first <= __last, "vector::erase(first, last) called with invalid range");
    pointer __p = this->__begin_ + (__first - begin());
    if (__first != __last) {
        this->__destruct_at_end(_VSTD::move(__p + (__last - __first), this->__end_, __p));
        this->__invalidate_iterators_past(__p - 1);
    }
    iterator __r = __make_iter(__p);
    return __r;
}

template <class _Tp, class _Allocator>
void
vector<_Tp, _Allocator>::__move_range(pointer __from_s, pointer __from_e, pointer __to)
{
    pointer __old_last = this->__end_;
    difference_type __n = __old_last - __to;
    {
      pointer __i = __from_s + __n;
      _ConstructTransaction __tx(*this, __from_e - __i);
      for (; __i < __from_e; ++__i, ++__tx.__pos_) {
          __alloc_traits::construct(this->__alloc(),
                                    _VSTD::__to_address(__tx.__pos_),
                                    _VSTD::move(*__i));
      }
    }
    _VSTD::move_backward(__from_s, __from_s + __n, __old_last);
}

template <class _Tp, class _Allocator>
typename vector<_Tp, _Allocator>::iterator
vector<_Tp, _Allocator>::insert(const_iterator __position, const_reference __x)
{
#if _LIBCPP_DEBUG_LEVEL >= 2
    _LIBCPP_ASSERT(__get_const_db()->__find_c_from_i(&__position) == this,
        "vector::insert(iterator, x) called with an iterator not"
        " referring to this vector");
#endif
    pointer __p = this->__begin_ + (__position - begin());
    if (this->__end_ < this->__end_cap())
    {
        if (__p == this->__end_)
        {
            __construct_one_at_end(__x);
        }
        else
        {
            __move_range(__p, this->__end_, __p + 1);
            const_pointer __xr = pointer_traits<const_pointer>::pointer_to(__x);
            if (__p <= __xr && __xr < this->__end_)
                ++__xr;
            *__p = *__xr;
        }
    }
    else
    {
        allocator_type& __a = this->__alloc();
        __split_buffer<value_type, allocator_type&> __v(__recommend(size() + 1), __p - this->__begin_, __a);
        __v.push_back(__x);
        __p = __swap_out_circular_buffer(__v, __p);
    }
    return __make_iter(__p);
}

#ifndef _LIBCPP_CXX03_LANG

template <class _Tp, class _Allocator>
typename vector<_Tp, _Allocator>::iterator
vector<_Tp, _Allocator>::insert(const_iterator __position, value_type&& __x)
{
#if _LIBCPP_DEBUG_LEVEL >= 2
    _LIBCPP_ASSERT(__get_const_db()->__find_c_from_i(&__position) == this,
        "vector::insert(iterator, x) called with an iterator not"
        " referring to this vector");
#endif
    pointer __p = this->__begin_ + (__position - begin());
    if (this->__end_ < this->__end_cap())
    {
        if (__p == this->__end_)
        {
            __construct_one_at_end(_VSTD::move(__x));
        }
        else
        {
            __move_range(__p, this->__end_, __p + 1);
            *__p = _VSTD::move(__x);
        }
    }
    else
    {
        allocator_type& __a = this->__alloc();
        __split_buffer<value_type, allocator_type&> __v(__recommend(size() + 1), __p - this->__begin_, __a);
        __v.push_back(_VSTD::move(__x));
        __p = __swap_out_circular_buffer(__v, __p);
    }
    return __make_iter(__p);
}

template <class _Tp, class _Allocator>
template <class... _Args>
typename vector<_Tp, _Allocator>::iterator
vector<_Tp, _Allocator>::emplace(const_iterator __position, _Args&&... __args)
{
#if _LIBCPP_DEBUG_LEVEL >= 2
    _LIBCPP_ASSERT(__get_const_db()->__find_c_from_i(&__position) == this,
        "vector::emplace(iterator, x) called with an iterator not"
        " referring to this vector");
#endif
    pointer __p = this->__begin_ + (__position - begin());
    if (this->__end_ < this->__end_cap())
    {
        if (__p == this->__end_)
        {
            __construct_one_at_end(_VSTD::forward<_Args>(__args)...);
        }
        else
        {
            __temp_value<value_type, _Allocator> __tmp(this->__alloc(), _VSTD::forward<_Args>(__args)...);
            __move_range(__p, this->__end_, __p + 1);
            *__p = _VSTD::move(__tmp.get());
        }
    }
    else
    {
        allocator_type& __a = this->__alloc();
        __split_buffer<value_type, allocator_type&> __v(__recommend(size() + 1), __p - this->__begin_, __a);
        __v.emplace_back(_VSTD::forward<_Args>(__args)...);
        __p = __swap_out_circular_buffer(__v, __p);
    }
    return __make_iter(__p);
}

#endif  // !_LIBCPP_CXX03_LANG

template <class _Tp, class _Allocator>
typename vector<_Tp, _Allocator>::iterator
vector<_Tp, _Allocator>::insert(const_iterator __position, size_type __n, const_reference __x)
{
#if _LIBCPP_DEBUG_LEVEL >= 2
    _LIBCPP_ASSERT(__get_const_db()->__find_c_from_i(&__position) == this,
        "vector::insert(iterator, n, x) called with an iterator not"
        " referring to this vector");
#endif
    pointer __p = this->__begin_ + (__position - begin());
    if (__n > 0)
    {
        if (__n <= static_cast<size_type>(this->__end_cap() - this->__end_))
        {
            size_type __old_n = __n;
            pointer __old_last = this->__end_;
            if (__n > static_cast<size_type>(this->__end_ - __p))
            {
                size_type __cx = __n - (this->__end_ - __p);
                __construct_at_end(__cx, __x);
                __n -= __cx;
            }
            if (__n > 0)
            {
                __move_range(__p, __old_last, __p + __old_n);
                const_pointer __xr = pointer_traits<const_pointer>::pointer_to(__x);
                if (__p <= __xr && __xr < this->__end_)
                    __xr += __old_n;
                _VSTD::fill_n(__p, __n, *__xr);
            }
        }
        else
        {
            allocator_type& __a = this->__alloc();
            __split_buffer<value_type, allocator_type&> __v(__recommend(size() + __n), __p - this->__begin_, __a);
            __v.__construct_at_end(__n, __x);
            __p = __swap_out_circular_buffer(__v, __p);
        }
    }
    return __make_iter(__p);
}

template <class _Tp, class _Allocator>
template <class _InputIterator>
typename enable_if
<
     __is_cpp17_input_iterator  <_InputIterator>::value &&
    !__is_cpp17_forward_iterator<_InputIterator>::value &&
    is_constructible<
       _Tp,
       typename iterator_traits<_InputIterator>::reference>::value,
    typename vector<_Tp, _Allocator>::iterator
>::type
vector<_Tp, _Allocator>::insert(const_iterator __position, _InputIterator __first, _InputIterator __last)
{
#if _LIBCPP_DEBUG_LEVEL >= 2
    _LIBCPP_ASSERT(__get_const_db()->__find_c_from_i(&__position) == this,
        "vector::insert(iterator, range) called with an iterator not"
        " referring to this vector");
#endif
    difference_type __off = __position - begin();
    pointer __p = this->__begin_ + __off;
    allocator_type& __a = this->__alloc();
    pointer __old_last = this->__end_;
    for (; this->__end_ != this->__end_cap() && __first != __last; ++__first)
    {
        __construct_one_at_end(*__first);
    }
    __split_buffer<value_type, allocator_type&> __v(__a);
    if (__first != __last)
    {
#ifndef _LIBCPP_NO_EXCEPTIONS
        try
        {
#endif  // _LIBCPP_NO_EXCEPTIONS
            __v.__construct_at_end(__first, __last);
            difference_type __old_size = __old_last - this->__begin_;
            difference_type __old_p = __p - this->__begin_;
            reserve(__recommend(size() + __v.size()));
            __p = this->__begin_ + __old_p;
            __old_last = this->__begin_ + __old_size;
#ifndef _LIBCPP_NO_EXCEPTIONS
        }
        catch (...)
        {
            erase(__make_iter(__old_last), end());
            throw;
        }
#endif  // _LIBCPP_NO_EXCEPTIONS
    }
    __p = _VSTD::rotate(__p, __old_last, this->__end_);
    insert(__make_iter(__p), make_move_iterator(__v.begin()),
                                    make_move_iterator(__v.end()));
    return begin() + __off;
}

template <class _Tp, class _Allocator>
template <class _ForwardIterator>
typename enable_if
<
    __is_cpp17_forward_iterator<_ForwardIterator>::value &&
    is_constructible<
       _Tp,
       typename iterator_traits<_ForwardIterator>::reference>::value,
    typename vector<_Tp, _Allocator>::iterator
>::type
vector<_Tp, _Allocator>::insert(const_iterator __position, _ForwardIterator __first, _ForwardIterator __last)
{
#if _LIBCPP_DEBUG_LEVEL >= 2
    _LIBCPP_ASSERT(__get_const_db()->__find_c_from_i(&__position) == this,
        "vector::insert(iterator, range) called with an iterator not"
        " referring to this vector");
#endif
    pointer __p = this->__begin_ + (__position - begin());
    difference_type __n = _VSTD::distance(__first, __last);
    if (__n > 0)
    {
        if (__n <= this->__end_cap() - this->__end_)
        {
            size_type __old_n = __n;
            pointer __old_last = this->__end_;
            _ForwardIterator __m = __last;
            difference_type __dx = this->__end_ - __p;
            if (__n > __dx)
            {
                __m = __first;
                difference_type __diff = this->__end_ - __p;
                _VSTD::advance(__m, __diff);
                __construct_at_end(__m, __last, __n - __diff);
                __n = __dx;
            }
            if (__n > 0)
            {
                __move_range(__p, __old_last, __p + __old_n);
                _VSTD::copy(__first, __m, __p);
            }
        }
        else
        {
            allocator_type& __a = this->__alloc();
            __split_buffer<value_type, allocator_type&> __v(__recommend(size() + __n), __p - this->__begin_, __a);
            __v.__construct_at_end(__first, __last);
            __p = __swap_out_circular_buffer(__v, __p);
        }
    }
    return __make_iter(__p);
}

template <class _Tp, class _Allocator>
void
vector<_Tp, _Allocator>::resize(size_type __sz)
{
    size_type __cs = size();
    if (__cs < __sz)
        this->__append(__sz - __cs);
    else if (__cs > __sz)
        this->__destruct_at_end(this->__begin_ + __sz);
}

template <class _Tp, class _Allocator>
void
vector<_Tp, _Allocator>::resize(size_type __sz, const_reference __x)
{
    size_type __cs = size();
    if (__cs < __sz)
        this->__append(__sz - __cs, __x);
    else if (__cs > __sz)
        this->__destruct_at_end(this->__begin_ + __sz);
}

template <class _Tp, class _Allocator>
void
vector<_Tp, _Allocator>::swap(vector& __x)
#if _LIBCPP_STD_VER >= 14
    _NOEXCEPT
#else
    _NOEXCEPT_(!__alloc_traits::propagate_on_container_swap::value ||
                __is_nothrow_swappable<allocator_type>::value)
#endif
{
    _LIBCPP_ASSERT(__alloc_traits::propagate_on_container_swap::value ||
                   this->__alloc() == __x.__alloc(),
                   "vector::swap: Either propagate_on_container_swap must be true"
                   " or the allocators must compare equal");
    _VSTD::swap(this->__begin_, __x.__begin_);
    _VSTD::swap(this->__end_, __x.__end_);
    _VSTD::swap(this->__end_cap(), __x.__end_cap());
    __swap_allocator(this->__alloc(), __x.__alloc(),
        integral_constant<bool,__alloc_traits::propagate_on_container_swap::value>());
#if _LIBCPP_DEBUG_LEVEL >= 2
    __get_db()->swap(this, &__x);
#endif  // _LIBCPP_DEBUG_LEVEL >= 2
}

template <class _Tp, class _Allocator>
bool
vector<_Tp, _Allocator>::__invariants() const
{
    if (this->__begin_ == nullptr)
    {
        if (this->__end_ != nullptr || this->__end_cap() != nullptr)
            return false;
    }
    else
    {
        if (this->__begin_ > this->__end_)
            return false;
        if (this->__begin_ == this->__end_cap())
            return false;
        if (this->__end_ > this->__end_cap())
            return false;
    }
    return true;
}

#if _LIBCPP_DEBUG_LEVEL >= 2

template <class _Tp, class _Allocator>
bool
vector<_Tp, _Allocator>::__dereferenceable(const const_iterator* __i) const
{
    return this->__begin_ <= __i->base() && __i->base() < this->__end_;
}

template <class _Tp, class _Allocator>
bool
vector<_Tp, _Allocator>::__decrementable(const const_iterator* __i) const
{
    return this->__begin_ < __i->base() && __i->base() <= this->__end_;
}

template <class _Tp, class _Allocator>
bool
vector<_Tp, _Allocator>::__addable(const const_iterator* __i, ptrdiff_t __n) const
{
    const_pointer __p = __i->base() + __n;
    return this->__begin_ <= __p && __p <= this->__end_;
}

template <class _Tp, class _Allocator>
bool
vector<_Tp, _Allocator>::__subscriptable(const const_iterator* __i, ptrdiff_t __n) const
{
    const_pointer __p = __i->base() + __n;
    return this->__begin_ <= __p && __p < this->__end_;
}

#endif  // _LIBCPP_DEBUG_LEVEL >= 2

template <class _Tp, class _Allocator>
inline _LIBCPP_INLINE_VISIBILITY
void
vector<_Tp, _Allocator>::__invalidate_all_iterators()
{
#if _LIBCPP_DEBUG_LEVEL >= 2
    __get_db()->__invalidate_all(this);
#endif  // _LIBCPP_DEBUG_LEVEL >= 2
}


template <class _Tp, class _Allocator>
inline _LIBCPP_INLINE_VISIBILITY
void
vector<_Tp, _Allocator>::__invalidate_iterators_past(pointer __new_last) {
#if _LIBCPP_DEBUG_LEVEL >= 2
  __c_node* __c = __get_db()->__find_c_and_lock(this);
  for (__i_node** __p = __c->end_; __p != __c->beg_; ) {
    --__p;
    const_iterator* __i = static_cast<const_iterator*>((*__p)->__i_);
    if (__i->base() > __new_last) {
      (*__p)->__c_ = nullptr;
      if (--__c->end_ != __p)
        memmove(__p, __p+1, (__c->end_ - __p)*sizeof(__i_node*));
    }
  }
  __get_db()->unlock();
#else
  ((void)__new_last);
#endif
}

// vector<bool>

template <class _Allocator> class vector<bool, _Allocator>;

template <class _Allocator> struct hash<vector<bool, _Allocator> >;

template <class _Allocator>
struct __has_storage_type<vector<bool, _Allocator> >
{
    static const bool value = true;
};

template <class _Allocator>
class vector<bool, _Allocator>
    : private __vector_base_common<true>
{
public:
    typedef vector                                   __self;
    typedef bool                                     value_type;
    typedef _Allocator                               allocator_type;
    typedef allocator_traits<allocator_type>         __alloc_traits;
    typedef typename __alloc_traits::size_type       size_type;
    typedef typename __alloc_traits::difference_type difference_type;
    typedef size_type __storage_type;
    typedef __bit_iterator<vector, false>            pointer;
    typedef __bit_iterator<vector, true>             const_pointer;
    typedef pointer                                  iterator;
    typedef const_pointer                            const_iterator;
    typedef _VSTD::reverse_iterator<iterator>         reverse_iterator;
    typedef _VSTD::reverse_iterator<const_iterator>   const_reverse_iterator;

private:
    typedef typename __rebind_alloc_helper<__alloc_traits, __storage_type>::type __storage_allocator;
    typedef allocator_traits<__storage_allocator>    __storage_traits;
    typedef typename __storage_traits::pointer       __storage_pointer;
    typedef typename __storage_traits::const_pointer __const_storage_pointer;

    __storage_pointer                                      __begin_;
    size_type                                              __size_;
    __compressed_pair<size_type, __storage_allocator> __cap_alloc_;
public:
    typedef __bit_reference<vector>                  reference;
    typedef __bit_const_reference<vector>            const_reference;
private:
    _LIBCPP_INLINE_VISIBILITY
    size_type& __cap() _NOEXCEPT
        {return __cap_alloc_.first();}
    _LIBCPP_INLINE_VISIBILITY
    const size_type& __cap() const _NOEXCEPT
        {return __cap_alloc_.first();}
    _LIBCPP_INLINE_VISIBILITY
    __storage_allocator& __alloc() _NOEXCEPT
        {return __cap_alloc_.second();}
    _LIBCPP_INLINE_VISIBILITY
    const __storage_allocator& __alloc() const _NOEXCEPT
        {return __cap_alloc_.second();}

    static const unsigned __bits_per_word = static_cast<unsigned>(sizeof(__storage_type) * CHAR_BIT);

    _LIBCPP_INLINE_VISIBILITY
    static size_type __internal_cap_to_external(size_type __n) _NOEXCEPT
        {return __n * __bits_per_word;}
    _LIBCPP_INLINE_VISIBILITY
    static size_type __external_cap_to_internal(size_type __n) _NOEXCEPT
        {return (__n - 1) / __bits_per_word + 1;}

public:
    _LIBCPP_INLINE_VISIBILITY
    vector() _NOEXCEPT_(is_nothrow_default_constructible<allocator_type>::value);

    _LIBCPP_INLINE_VISIBILITY explicit vector(const allocator_type& __a)
#if _LIBCPP_STD_VER <= 14
        _NOEXCEPT_(is_nothrow_copy_constructible<allocator_type>::value);
#else
        _NOEXCEPT;
#endif
    ~vector();
    explicit vector(size_type __n);
#if _LIBCPP_STD_VER > 11
    explicit vector(size_type __n, const allocator_type& __a);
#endif
    vector(size_type __n, const value_type& __v);
    vector(size_type __n, const value_type& __v, const allocator_type& __a);
    template <class _InputIterator>
        vector(_InputIterator __first, _InputIterator __last,
               typename enable_if<__is_cpp17_input_iterator  <_InputIterator>::value &&
                                 !__is_cpp17_forward_iterator<_InputIterator>::value>::type* = 0);
    template <class _InputIterator>
        vector(_InputIterator __first, _InputIterator __last, const allocator_type& __a,
               typename enable_if<__is_cpp17_input_iterator  <_InputIterator>::value &&
                                 !__is_cpp17_forward_iterator<_InputIterator>::value>::type* = 0);
    template <class _ForwardIterator>
        vector(_ForwardIterator __first, _ForwardIterator __last,
               typename enable_if<__is_cpp17_forward_iterator<_ForwardIterator>::value>::type* = 0);
    template <class _ForwardIterator>
        vector(_ForwardIterator __first, _ForwardIterator __last, const allocator_type& __a,
               typename enable_if<__is_cpp17_forward_iterator<_ForwardIterator>::value>::type* = 0);

    vector(const vector& __v);
    vector(const vector& __v, const allocator_type& __a);
    vector& operator=(const vector& __v);

#ifndef _LIBCPP_CXX03_LANG
    vector(initializer_list<value_type> __il);
    vector(initializer_list<value_type> __il, const allocator_type& __a);

    _LIBCPP_INLINE_VISIBILITY
    vector(vector&& __v)
#if _LIBCPP_STD_VER > 14
        _NOEXCEPT;
#else
        _NOEXCEPT_(is_nothrow_move_constructible<allocator_type>::value);
#endif
    vector(vector&& __v, const allocator_type& __a);
    _LIBCPP_INLINE_VISIBILITY
    vector& operator=(vector&& __v)
        _NOEXCEPT_((__noexcept_move_assign_container<_Allocator, __alloc_traits>::value));

    _LIBCPP_INLINE_VISIBILITY
    vector& operator=(initializer_list<value_type> __il)
        {assign(__il.begin(), __il.end()); return *this;}

#endif  // !_LIBCPP_CXX03_LANG

    template <class _InputIterator>
        typename enable_if
        <
            __is_cpp17_input_iterator<_InputIterator>::value &&
           !__is_cpp17_forward_iterator<_InputIterator>::value,
           void
        >::type
        assign(_InputIterator __first, _InputIterator __last);
    template <class _ForwardIterator>
        typename enable_if
        <
            __is_cpp17_forward_iterator<_ForwardIterator>::value,
           void
        >::type
        assign(_ForwardIterator __first, _ForwardIterator __last);

    void assign(size_type __n, const value_type& __x);

#ifndef _LIBCPP_CXX03_LANG
    _LIBCPP_INLINE_VISIBILITY
    void assign(initializer_list<value_type> __il)
        {assign(__il.begin(), __il.end());}
#endif

    _LIBCPP_INLINE_VISIBILITY allocator_type get_allocator() const _NOEXCEPT
        {return allocator_type(this->__alloc());}

    size_type max_size() const _NOEXCEPT;
    _LIBCPP_INLINE_VISIBILITY
    size_type capacity() const _NOEXCEPT
        {return __internal_cap_to_external(__cap());}
    _LIBCPP_INLINE_VISIBILITY
    size_type size() const _NOEXCEPT
        {return __size_;}
    _LIBCPP_NODISCARD_AFTER_CXX17 _LIBCPP_INLINE_VISIBILITY
    bool empty() const _NOEXCEPT
        {return __size_ == 0;}
    void reserve(size_type __n);
    void shrink_to_fit() _NOEXCEPT;

    _LIBCPP_INLINE_VISIBILITY
    iterator begin() _NOEXCEPT
        {return __make_iter(0);}
    _LIBCPP_INLINE_VISIBILITY
    const_iterator begin() const _NOEXCEPT
        {return __make_iter(0);}
    _LIBCPP_INLINE_VISIBILITY
    iterator end() _NOEXCEPT
        {return __make_iter(__size_);}
    _LIBCPP_INLINE_VISIBILITY
    const_iterator end()   const _NOEXCEPT
        {return __make_iter(__size_);}

    _LIBCPP_INLINE_VISIBILITY
    reverse_iterator rbegin() _NOEXCEPT
        {return       reverse_iterator(end());}
    _LIBCPP_INLINE_VISIBILITY
    const_reverse_iterator rbegin() const _NOEXCEPT
        {return const_reverse_iterator(end());}
    _LIBCPP_INLINE_VISIBILITY
    reverse_iterator rend() _NOEXCEPT
        {return       reverse_iterator(begin());}
    _LIBCPP_INLINE_VISIBILITY
    const_reverse_iterator rend()   const _NOEXCEPT
        {return const_reverse_iterator(begin());}

    _LIBCPP_INLINE_VISIBILITY
    const_iterator         cbegin()  const _NOEXCEPT
        {return __make_iter(0);}
    _LIBCPP_INLINE_VISIBILITY
    const_iterator         cend()    const _NOEXCEPT
        {return __make_iter(__size_);}
    _LIBCPP_INLINE_VISIBILITY
    const_reverse_iterator crbegin() const _NOEXCEPT
        {return rbegin();}
    _LIBCPP_INLINE_VISIBILITY
    const_reverse_iterator crend()   const _NOEXCEPT
        {return rend();}

    _LIBCPP_INLINE_VISIBILITY reference       operator[](size_type __n)       {return __make_ref(__n);}
    _LIBCPP_INLINE_VISIBILITY const_reference operator[](size_type __n) const {return __make_ref(__n);}
    reference       at(size_type __n);
    const_reference at(size_type __n) const;

    _LIBCPP_INLINE_VISIBILITY reference       front()       {return __make_ref(0);}
    _LIBCPP_INLINE_VISIBILITY const_reference front() const {return __make_ref(0);}
    _LIBCPP_INLINE_VISIBILITY reference       back()        {return __make_ref(__size_ - 1);}
    _LIBCPP_INLINE_VISIBILITY const_reference back()  const {return __make_ref(__size_ - 1);}

    void push_back(const value_type& __x);
#if _LIBCPP_STD_VER > 11
    template <class... _Args>
#if _LIBCPP_STD_VER > 14
    _LIBCPP_INLINE_VISIBILITY reference emplace_back(_Args&&... __args)
#else
    _LIBCPP_INLINE_VISIBILITY void      emplace_back(_Args&&... __args)
#endif
    {
        push_back ( value_type ( _VSTD::forward<_Args>(__args)... ));
#if _LIBCPP_STD_VER > 14
        return this->back();
#endif
    }
#endif

    _LIBCPP_INLINE_VISIBILITY void pop_back() {--__size_;}

#if _LIBCPP_STD_VER > 11
    template <class... _Args>
   _LIBCPP_INLINE_VISIBILITY iterator emplace(const_iterator position, _Args&&... __args)
        { return insert ( position, value_type ( _VSTD::forward<_Args>(__args)... )); }
#endif

    iterator insert(const_iterator __position, const value_type& __x);
    iterator insert(const_iterator __position, size_type __n, const value_type& __x);
    iterator insert(const_iterator __position, size_type __n, const_reference __x);
    template <class _InputIterator>
        typename enable_if
        <
             __is_cpp17_input_iterator  <_InputIterator>::value &&
            !__is_cpp17_forward_iterator<_InputIterator>::value,
            iterator
        >::type
        insert(const_iterator __position, _InputIterator __first, _InputIterator __last);
    template <class _ForwardIterator>
        typename enable_if
        <
            __is_cpp17_forward_iterator<_ForwardIterator>::value,
            iterator
        >::type
        insert(const_iterator __position, _ForwardIterator __first, _ForwardIterator __last);

#ifndef _LIBCPP_CXX03_LANG
    _LIBCPP_INLINE_VISIBILITY
    iterator insert(const_iterator __position, initializer_list<value_type> __il)
        {return insert(__position, __il.begin(), __il.end());}
#endif

    _LIBCPP_INLINE_VISIBILITY iterator erase(const_iterator __position);
    iterator erase(const_iterator __first, const_iterator __last);

    _LIBCPP_INLINE_VISIBILITY
    void clear() _NOEXCEPT {__size_ = 0;}

    void swap(vector&)
#if _LIBCPP_STD_VER >= 14
        _NOEXCEPT;
#else
        _NOEXCEPT_(!__alloc_traits::propagate_on_container_swap::value ||
                    __is_nothrow_swappable<allocator_type>::value);
#endif
    static void swap(reference __x, reference __y) _NOEXCEPT { _VSTD::swap(__x, __y); }

    void resize(size_type __sz, value_type __x = false);
    void flip() _NOEXCEPT;

    bool __invariants() const;

private:
    _LIBCPP_INLINE_VISIBILITY void __invalidate_all_iterators();
    void __vallocate(size_type __n);
    void __vdeallocate() _NOEXCEPT;
    _LIBCPP_INLINE_VISIBILITY
    static size_type __align_it(size_type __new_size) _NOEXCEPT
        {return __new_size + (__bits_per_word-1) & ~((size_type)__bits_per_word-1);}
    _LIBCPP_INLINE_VISIBILITY  size_type __recommend(size_type __new_size) const;
    _LIBCPP_INLINE_VISIBILITY void __construct_at_end(size_type __n, bool __x);
    template <class _ForwardIterator>
        typename enable_if
        <
            __is_cpp17_forward_iterator<_ForwardIterator>::value,
            void
        >::type
        __construct_at_end(_ForwardIterator __first, _ForwardIterator __last);
    void __append(size_type __n, const_reference __x);
    _LIBCPP_INLINE_VISIBILITY
    reference __make_ref(size_type __pos) _NOEXCEPT
        {return reference(__begin_ + __pos / __bits_per_word, __storage_type(1) << __pos % __bits_per_word);}
    _LIBCPP_INLINE_VISIBILITY
    const_reference __make_ref(size_type __pos) const _NOEXCEPT
        {return const_reference(__begin_ + __pos / __bits_per_word, __storage_type(1) << __pos % __bits_per_word);}
    _LIBCPP_INLINE_VISIBILITY
    iterator __make_iter(size_type __pos) _NOEXCEPT
        {return iterator(__begin_ + __pos / __bits_per_word, static_cast<unsigned>(__pos % __bits_per_word));}
    _LIBCPP_INLINE_VISIBILITY
    const_iterator __make_iter(size_type __pos) const _NOEXCEPT
        {return const_iterator(__begin_ + __pos / __bits_per_word, static_cast<unsigned>(__pos % __bits_per_word));}
    _LIBCPP_INLINE_VISIBILITY
    iterator __const_iterator_cast(const_iterator __p) _NOEXCEPT
        {return begin() + (__p - cbegin());}

    _LIBCPP_INLINE_VISIBILITY
    void __copy_assign_alloc(const vector& __v)
        {__copy_assign_alloc(__v, integral_constant<bool,
                      __storage_traits::propagate_on_container_copy_assignment::value>());}
    _LIBCPP_INLINE_VISIBILITY
    void __copy_assign_alloc(const vector& __c, true_type)
        {
            if (__alloc() != __c.__alloc())
                __vdeallocate();
            __alloc() = __c.__alloc();
        }

    _LIBCPP_INLINE_VISIBILITY
    void __copy_assign_alloc(const vector&, false_type)
        {}

    void __move_assign(vector& __c, false_type);
    void __move_assign(vector& __c, true_type)
        _NOEXCEPT_(is_nothrow_move_assignable<allocator_type>::value);
    _LIBCPP_INLINE_VISIBILITY
    void __move_assign_alloc(vector& __c)
        _NOEXCEPT_(
            !__storage_traits::propagate_on_container_move_assignment::value ||
            is_nothrow_move_assignable<allocator_type>::value)
        {__move_assign_alloc(__c, integral_constant<bool,
                      __storage_traits::propagate_on_container_move_assignment::value>());}
    _LIBCPP_INLINE_VISIBILITY
    void __move_assign_alloc(vector& __c, true_type)
        _NOEXCEPT_(is_nothrow_move_assignable<allocator_type>::value)
        {
            __alloc() = _VSTD::move(__c.__alloc());
        }

    _LIBCPP_INLINE_VISIBILITY
    void __move_assign_alloc(vector&, false_type)
        _NOEXCEPT
        {}

    size_t __hash_code() const _NOEXCEPT;

    friend class __bit_reference<vector>;
    friend class __bit_const_reference<vector>;
    friend class __bit_iterator<vector, false>;
    friend class __bit_iterator<vector, true>;
    friend struct __bit_array<vector>;
    friend struct _LIBCPP_TEMPLATE_VIS hash<vector>;
};

template <class _Allocator>
void vector<bool, _Allocator>::__invalidate_all_iterators() {}

//  Allocate space for __n objects
//  throws length_error if __n > max_size()
//  throws (probably bad_alloc) if memory run out
//  Precondition:  __begin_ == __end_ == __cap() == 0
//  Precondition:  __n > 0
//  Postcondition:  capacity() == __n
//  Postcondition:  size() == 0
template <class _Allocator>
void vector<bool, _Allocator>::__vallocate(size_type __n)
{
    if (__n > max_size())
        this->__throw_length_error();
    __n = __external_cap_to_internal(__n);
    this->__begin_ = __storage_traits::allocate(this->__alloc(), __n);
    this->__size_ = 0;
    this->__cap() = __n;
}

template <class _Allocator>
void vector<bool, _Allocator>::__vdeallocate() _NOEXCEPT
{
    if (this->__begin_ != nullptr)
    {
        __storage_traits::deallocate(this->__alloc(), this->__begin_, __cap());
        __invalidate_all_iterators();
        this->__begin_ = nullptr;
        this->__size_ = this->__cap() = 0;
    }
}

template <class _Allocator>
typename vector<bool, _Allocator>::size_type vector<bool, _Allocator>::max_size() const _NOEXCEPT
{
    size_type __amax = __storage_traits::max_size(__alloc());
    size_type __nmax = numeric_limits<size_type>::max() / 2;  // end() >= begin(), always
    if (__nmax / __bits_per_word <= __amax)
        return __nmax;
    return __internal_cap_to_external(__amax);
}

//  Precondition:  __new_size > capacity()
template <class _Allocator>
typename vector<bool, _Allocator>::size_type vector<bool, _Allocator>::__recommend(size_type __new_size) const
{
    const size_type __ms = max_size();
    if (__new_size > __ms)
        this->__throw_length_error();
    const size_type __cap = capacity();
    if (__cap >= __ms / 2)
        return __ms;
    return _VSTD::max(2*__cap, __align_it(__new_size));
}

//  Default constructs __n objects starting at __end_
//  Precondition:  __n > 0
//  Precondition:  size() + __n <= capacity()
//  Postcondition:  size() == size() + __n
template <class _Allocator>
void vector<bool, _Allocator>::__construct_at_end(size_type __n, bool __x)
{
    size_type __old_size = this->__size_;
    this->__size_ += __n;
    if (__old_size == 0 || ((__old_size - 1) / __bits_per_word) != ((this->__size_ - 1) / __bits_per_word))
    {
        if (this->__size_ <= __bits_per_word)
            this->__begin_[0] = __storage_type(0);
        else
            this->__begin_[(this->__size_ - 1) / __bits_per_word] = __storage_type(0);
    }
    _VSTD::fill_n(__make_iter(__old_size), __n, __x);
}

template <class _Allocator>
template <class _ForwardIterator>
typename enable_if <__is_cpp17_forward_iterator<_ForwardIterator>::value, void>::type
vector<bool, _Allocator>::__construct_at_end(_ForwardIterator __first, _ForwardIterator __last)
{
    size_type __old_size = this->__size_;
    this->__size_ += _VSTD::distance(__first, __last);
    if (__old_size == 0 || ((__old_size - 1) / __bits_per_word) != ((this->__size_ - 1) / __bits_per_word))
    {
        if (this->__size_ <= __bits_per_word)
            this->__begin_[0] = __storage_type(0);
        else
            this->__begin_[(this->__size_ - 1) / __bits_per_word] = __storage_type(0);
    }
    _VSTD::copy(__first, __last, __make_iter(__old_size));
}

template <class _Allocator>
vector<bool, _Allocator>::vector()
    _NOEXCEPT_(is_nothrow_default_constructible<allocator_type>::value)
    : __begin_(nullptr), __size_(0), __cap_alloc_(0, __default_init_tag()) {}

template <class _Allocator>
vector<bool, _Allocator>::vector(const allocator_type& __a) _NOEXCEPT_(is_nothrow_copy_constructible<allocator_type>::value)
    : __begin_(nullptr), __size_(0), __cap_alloc_(0, static_cast<__storage_allocator>(__a)) {}

template <class _Allocator>
vector<bool, _Allocator>::vector(size_type __n)
    : __begin_(nullptr), __size_(0), __cap_alloc_(0, __default_init_tag())
{
    if (__n > 0)
    {
        __vallocate(__n);
        __construct_at_end(__n, false);
    }
}

template <class _Allocator>
vector<bool, _Allocator>::vector(size_type __n, const value_type& __x)
    : __begin_(nullptr), __size_(0), __cap_alloc_(0, __default_init_tag())
{
    if (__n > 0)
    {
        __vallocate(__n);
        __construct_at_end(__n, __x);
    }
}

template <class _Allocator>
vector<bool, _Allocator>::vector(size_type __n, const value_type& __x, const allocator_type& __a)
    : __begin_(nullptr), __size_(0), __cap_alloc_(0, static_cast<__storage_allocator>(__a))
{
    if (__n > 0)
    {
        __vallocate(__n);
        __construct_at_end(__n, __x);
    }
}

template <class _Allocator>
template <class _InputIterator>
vector<bool, _Allocator>::vector(_InputIterator __first, _InputIterator __last,
       typename enable_if<__is_cpp17_input_iterator  <_InputIterator>::value && !__is_cpp17_forward_iterator<_InputIterator>::value>::type*)
    : __begin_(nullptr), __size_(0), __cap_alloc_(0, __default_init_tag())
{
    try
    {
        for (; __first != __last; ++__first)
            push_back(*__first);
    }
    catch (...)
    {
        if (__begin_ != nullptr)
            __storage_traits::deallocate(__alloc(), __begin_, __cap());
        __invalidate_all_iterators();
        throw;
    }
}

template <class _Allocator>
template <class _InputIterator>
vector<bool, _Allocator>::vector(_InputIterator __first, _InputIterator __last, const allocator_type& __a,
       typename enable_if<__is_cpp17_input_iterator  <_InputIterator>::value && !__is_cpp17_forward_iterator<_InputIterator>::value>::type*)
    : __begin_(nullptr), __size_(0), __cap_alloc_(0, static_cast<__storage_allocator>(__a))
{
    try
    {
        for (; __first != __last; ++__first)
            push_back(*__first);
    }
    catch (...)
    {
        if (__begin_ != nullptr)
            __storage_traits::deallocate(__alloc(), __begin_, __cap());
        __invalidate_all_iterators();
        throw;
    }
}

template <class _Allocator>
template <class _ForwardIterator>
vector<bool, _Allocator>::vector(_ForwardIterator __first, _ForwardIterator __last,
                                typename enable_if<__is_cpp17_forward_iterator<_ForwardIterator>::value>::type*)
    : __begin_(nullptr), __size_(0), __cap_alloc_(0, __default_init_tag())
{
    size_type __n = static_cast<size_type>(_VSTD::distance(__first, __last));
    if (__n > 0)
    {
        __vallocate(__n);
        __construct_at_end(__first, __last);
    }
}

template <class _Allocator>
template <class _ForwardIterator>
vector<bool, _Allocator>::vector(_ForwardIterator __first, _ForwardIterator __last, const allocator_type& __a, typename enable_if<__is_cpp17_forward_iterator<_ForwardIterator>::value>::type*)
    : __begin_(nullptr), __size_(0), __cap_alloc_(0, static_cast<__storage_allocator>(__a))
{
    size_type __n = static_cast<size_type>(_VSTD::distance(__first, __last));
    if (__n > 0)
    {
        __vallocate(__n);
        __construct_at_end(__first, __last);
    }
}


template <class _Allocator>
vector<bool, _Allocator>::vector(initializer_list<value_type> __il)
    : __begin_(nullptr), __size_(0), __cap_alloc_(0, __default_init_tag())
{
    size_type __n = static_cast<size_type>(__il.size());
    if (__n > 0)
    {
        __vallocate(__n);
        __construct_at_end(__il.begin(), __il.end());
    }
}

template <class _Allocator>
vector<bool, _Allocator>::vector(initializer_list<value_type> __il, const allocator_type& __a)
    : __begin_(nullptr), __size_(0), __cap_alloc_(0, static_cast<__storage_allocator>(__a))
{
    size_type __n = static_cast<size_type>(__il.size());
    if (__n > 0)
    {
        __vallocate(__n);
        __construct_at_end(__il.begin(), __il.end());
    }
}

template <class _Allocator>
vector<bool, _Allocator>::~vector()
{
    if (__begin_ != nullptr)
        __storage_traits::deallocate(__alloc(), __begin_, __cap());
    __invalidate_all_iterators();
}

template <class _Allocator>
vector<bool, _Allocator>::vector(const vector& __v)
    : __begin_(nullptr), __size_(0), __cap_alloc_(0, __storage_traits::select_on_container_copy_construction(__v.__alloc()))
{
    if (__v.size() > 0)
    {
        __vallocate(__v.size());
        __construct_at_end(__v.begin(), __v.end());
    }
}

template <class _Allocator>
vector<bool, _Allocator>::vector(const vector& __v, const allocator_type& __a)
    : __begin_(nullptr), __size_(0), __cap_alloc_(0, __a)
{
    if (__v.size() > 0)
    {
        __vallocate(__v.size());
        __construct_at_end(__v.begin(), __v.end());
    }
}

template <class _Allocator>
vector<bool, _Allocator>& vector<bool, _Allocator>::operator=(const vector& __v)
{
    if (this != &__v)
    {
        __copy_assign_alloc(__v);
        if (__v.__size_)
        {
            if (__v.__size_ > capacity())
            {
                __vdeallocate();
                __vallocate(__v.__size_);
            }
            _VSTD::copy(__v.__begin_, __v.__begin_ + __external_cap_to_internal(__v.__size_), __begin_);
        }
        __size_ = __v.__size_;
    }
    return *this;
}

template <class _Allocator>
vector<bool, _Allocator>::vector(vector&& __v) _NOEXCEPT_(is_nothrow_move_constructible<allocator_type>::value)
    : __begin_(__v.__begin_), __size_(__v.__size_), __cap_alloc_(std::move(__v.__cap_alloc_)) 
{
    __v.__begin_ = nullptr;
    __v.__size_ = 0;
    __v.__cap() = 0;
}

template <class _Allocator>
vector<bool, _Allocator>::vector(vector&& __v, const allocator_type& __a)
    : __begin_(nullptr),
      __size_(0),
      __cap_alloc_(0, __a)
{
    if (__a == allocator_type(__v.__alloc()))
    {
        this->__begin_ = __v.__begin_;
        this->__size_ = __v.__size_;
        this->__cap() = __v.__cap();
        __v.__begin_ = nullptr;
        __v.__cap() = __v.__size_ = 0;
    }
    else if (__v.size() > 0)
    {
        __vallocate(__v.size());
        __construct_at_end(__v.begin(), __v.end());
    }
}

template <class _Allocator>
vector<bool, _Allocator>& vector<bool, _Allocator>::operator=(vector&& __v)
    _NOEXCEPT_((__noexcept_move_assign_container<_Allocator, __alloc_traits>::value))
{
    __move_assign(__v, integral_constant<bool,
          __storage_traits::propagate_on_container_move_assignment::value>());
    return *this;
}

template <class _Allocator>
void vector<bool, _Allocator>::__move_assign(vector& __c, false_type)
{
    if (__alloc() != __c.__alloc())
        assign(__c.begin(), __c.end());
    else
        __move_assign(__c, true_type());
}

template <class _Allocator>
void vector<bool, _Allocator>::__move_assign(vector& __c, true_type)
    _NOEXCEPT_(is_nothrow_move_assignable<allocator_type>::value)
{
    __vdeallocate();
    __move_assign_alloc(__c);
    this->__begin_ = __c.__begin_;
    this->__size_ = __c.__size_;
    this->__cap() = __c.__cap();
    __c.__begin_ = nullptr;
    __c.__cap() = __c.__size_ = 0;
}


template <class _Allocator>
void vector<bool, _Allocator>::assign(size_type __n, const value_type& __x)
{
    __size_ = 0;
    if (__n > 0)
    {
        size_type __c = capacity();
        if (__n <= __c)
            __size_ = __n;
        else
        {
            vector __v(__alloc());
            __v.reserve(__recommend(__n));
            __v.__size_ = __n;
            swap(__v);
        }
        _VSTD::fill_n(begin(), __n, __x);
    }
  __invalidate_all_iterators();
}

template <class _Allocator>
template <class _InputIterator>
typename enable_if<__is_cpp17_input_iterator<_InputIterator>::value && !__is_cpp17_forward_iterator<_InputIterator>::value, void>::type
vector<bool, _Allocator>::assign(_InputIterator __first, _InputIterator __last)
{
    clear();
    for (; __first != __last; ++__first)
        push_back(*__first);
}

template <class _Allocator>
template <class _ForwardIterator>
typename enable_if < __is_cpp17_forward_iterator<_ForwardIterator>::value, void>::type
vector<bool, _Allocator>::assign(_ForwardIterator __first, _ForwardIterator __last)
{
    clear();
    difference_type __ns = _VSTD::distance(__first, __last);
    _LIBCPP_ASSERT(__ns >= 0, "invalid range specified");
    const size_t __n = static_cast<size_type>(__ns);
    if (__n)
    {
        if (__n > capacity())
        {
            __vdeallocate();
            __vallocate(__n);
        }
        __construct_at_end(__first, __last);
    }
}

template <class _Allocator>
void
vector<bool, _Allocator>::reserve(size_type __n)
{
    if (__n > capacity())
    {
        vector __v(this->__alloc());
        __v.__vallocate(__n);
        __v.__construct_at_end(this->begin(), this->end());
        swap(__v);
        __invalidate_all_iterators();
    }
}

template <class _Allocator>
void
vector<bool, _Allocator>::shrink_to_fit() _NOEXCEPT
{
    if (__external_cap_to_internal(size()) > __cap())
    {
#ifndef _LIBCPP_NO_EXCEPTIONS
        try
        {
#endif  // _LIBCPP_NO_EXCEPTIONS
            vector(*this, allocator_type(__alloc())).swap(*this);
#ifndef _LIBCPP_NO_EXCEPTIONS
        }
        catch (...)
        {
        }
#endif  // _LIBCPP_NO_EXCEPTIONS
    }
}

template <class _Allocator>
typename vector<bool, _Allocator>::reference
vector<bool, _Allocator>::at(size_type __n)
{
    if (__n >= size())
        this->__throw_out_of_range();
    return (*this)[__n];
}

template <class _Allocator>
typename vector<bool, _Allocator>::const_reference
vector<bool, _Allocator>::at(size_type __n) const
{
    if (__n >= size())
        this->__throw_out_of_range();
    return (*this)[__n];
}

template <class _Allocator>
void
vector<bool, _Allocator>::push_back(const value_type& __x)
{
    if (this->__size_ == this->capacity())
        reserve(__recommend(this->__size_ + 1));
    ++this->__size_;
    back() = __x;
}

template <class _Allocator>
typename vector<bool, _Allocator>::iterator
vector<bool, _Allocator>::insert(const_iterator __position, const value_type& __x)
{
    iterator __r;
    if (size() < capacity())
    {
        const_iterator __old_end = end();
        ++__size_;
        _VSTD::copy_backward(__position, __old_end, end());
        __r = __const_iterator_cast(__position);
    }
    else
    {
        vector __v(__alloc());
        __v.reserve(__recommend(__size_ + 1));
        __v.__size_ = __size_ + 1;
        __r = _VSTD::copy(cbegin(), __position, __v.begin());
        _VSTD::copy_backward(__position, cend(), __v.end());
        swap(__v);
    }
    *__r = __x;
    return __r;
}

template <class _Allocator>
typename vector<bool, _Allocator>::iterator
vector<bool, _Allocator>::insert(const_iterator __position, size_type __n, const value_type& __x)
{
    iterator __r;
    size_type __c = capacity();
    if (__n <= __c && size() <= __c - __n)
    {
        const_iterator __old_end = end();
        __size_ += __n;
        _VSTD::copy_backward(__position, __old_end, end());
        __r = __const_iterator_cast(__position);
    }
    else
    {
        vector __v(__alloc());
        __v.reserve(__recommend(__size_ + __n));
        __v.__size_ = __size_ + __n;
        __r = _VSTD::copy(cbegin(), __position, __v.begin());
        _VSTD::copy_backward(__position, cend(), __v.end());
        swap(__v);
    }
    _VSTD::fill_n(__r, __n, __x);
    return __r;
}

template <class _Allocator>
template <class _InputIterator>
typename enable_if
<
     __is_cpp17_input_iterator  <_InputIterator>::value &&
    !__is_cpp17_forward_iterator<_InputIterator>::value,
    typename vector<bool, _Allocator>::iterator
>::type
vector<bool, _Allocator>::insert(const_iterator __position, _InputIterator __first, _InputIterator __last)
{
    difference_type __off = __position - begin();
    iterator __p = __const_iterator_cast(__position);
    iterator __old_end = end();
    for (; size() != capacity() && __first != __last; ++__first)
    {
        ++this->__size_;
        back() = *__first;
    }
    vector __v(__alloc());
    if (__first != __last)
    {
#ifndef _LIBCPP_NO_EXCEPTIONS
        try
        {
#endif  // _LIBCPP_NO_EXCEPTIONS
            __v.assign(__first, __last);
            difference_type __old_size = static_cast<difference_type>(__old_end - begin());
            difference_type __old_p = __p - begin();
            reserve(__recommend(size() + __v.size()));
            __p = begin() + __old_p;
            __old_end = begin() + __old_size;
#ifndef _LIBCPP_NO_EXCEPTIONS
        }
        catch (...)
        {
            erase(__old_end, end());
            throw;
        }
#endif  // _LIBCPP_NO_EXCEPTIONS
    }
    __p = _VSTD::rotate(__p, __old_end, end());
    insert(__p, __v.begin(), __v.end());
    return begin() + __off;
}

template <class _Allocator>
template <class _ForwardIterator>
typename enable_if < __is_cpp17_forward_iterator<_ForwardIterator>::value, typename vector<bool, _Allocator>::iterator>::type
vector<bool, _Allocator>::insert(const_iterator __position, _ForwardIterator __first, _ForwardIterator __last)
{
    const difference_type __n_signed = _VSTD::distance(__first, __last);
    _LIBCPP_ASSERT(__n_signed >= 0, "invalid range specified");
    const size_type __n = static_cast<size_type>(__n_signed);
    iterator __r;
    size_type __c = capacity();
    if (__n <= __c && size() <= __c - __n)
    {
        const_iterator __old_end = end();
        __size_ += __n;
        _VSTD::copy_backward(__position, __old_end, end());
        __r = __const_iterator_cast(__position);
    }
    else
    {
        vector __v(__alloc());
        __v.reserve(__recommend(__size_ + __n));
        __v.__size_ = __size_ + __n;
        __r = _VSTD::copy(cbegin(), __position, __v.begin());
        _VSTD::copy_backward(__position, cend(), __v.end());
        swap(__v);
    }
    _VSTD::copy(__first, __last, __r);
    return __r;
}

template <class _Allocator>
typename vector<bool, _Allocator>::iterator vector<bool, _Allocator>::erase(const_iterator __position)
{
    iterator __r = __const_iterator_cast(__position);
    _VSTD::copy(__position + 1, this->cend(), __r);
    --__size_;
    return __r;
}

template <class _Allocator>
typename vector<bool, _Allocator>::iterator vector<bool, _Allocator>::erase(const_iterator __first, const_iterator __last)
{
    iterator __r = __const_iterator_cast(__first);
    difference_type __d = __last - __first;
    _VSTD::copy(__last, this->cend(), __r);
    __size_ -= __d;
    return __r;
}

template <class _Allocator>
void vector<bool, _Allocator>::swap(vector& __x)
    _NOEXCEPT_(!__alloc_traits::propagate_on_container_swap::value || __is_nothrow_swappable<allocator_type>::value)
{
    _VSTD::swap(this->__begin_, __x.__begin_);
    _VSTD::swap(this->__size_, __x.__size_);
    _VSTD::swap(this->__cap(), __x.__cap());
    __swap_allocator(this->__alloc(), __x.__alloc(),
        integral_constant<bool, __alloc_traits::propagate_on_container_swap::value>());
}

template <class _Allocator>
void vector<bool, _Allocator>::resize(size_type __sz, value_type __x)
{
    size_type __cs = size();
    if (__cs < __sz)
    {
        iterator __r;
        size_type __c = capacity();
        size_type __n = __sz - __cs;
        if (__n <= __c && __cs <= __c - __n)
        {
            __r = end();
            __size_ += __n;
        }
        else
        {
            vector __v(__alloc());
            __v.reserve(__recommend(__size_ + __n));
            __v.__size_ = __size_ + __n;
            __r = _VSTD::copy(cbegin(), cend(), __v.begin());
            swap(__v);
        }
        _VSTD::fill_n(__r, __n, __x);
    }
    else
        __size_ = __sz;
}

template <class _Allocator>
void vector<bool, _Allocator>::flip() _NOEXCEPT
{
    // do middle whole words
    size_type __n = __size_;
    __storage_pointer __p = __begin_;
    for (; __n >= __bits_per_word; ++__p, __n -= __bits_per_word)
        *__p = ~*__p;
    // do last partial word
    if (__n > 0)
    {
        __storage_type __m = ~__storage_type(0) >> (__bits_per_word - __n);
        __storage_type __b = *__p & __m;
        *__p &= ~__m;
        *__p |= ~__b & __m;
    }
}

template <class _Allocator>
bool vector<bool, _Allocator>::__invariants() const
{
    if (this->__begin_ == nullptr)
    {
        if (this->__size_ != 0 || this->__cap() != 0)
            return false;
    }
    else
    {
        if (this->__cap() == 0)
            return false;
        if (this->__size_ > this->capacity())
            return false;
    }
    return true;
}

template <class _Allocator>
size_t vector<bool, _Allocator>::__hash_code() const _NOEXCEPT
{
    size_t __h = 0;
    // do middle whole words
    size_type __n = __size_;
    __storage_pointer __p = __begin_;
    for (; __n >= __bits_per_word; ++__p, __n -= __bits_per_word)
        __h ^= *__p;
    // do last partial word
    if (__n > 0)
    {
        const __storage_type __m = ~__storage_type(0) >> (__bits_per_word - __n);
        __h ^= *__p & __m;
    }
    return __h;
}

template <class _Allocator>
struct _LIBCPP_TEMPLATE_VIS hash<vector<bool, _Allocator> >
    : public unary_function<vector<bool, _Allocator>, size_t>
{
    size_t operator()(const vector<bool, _Allocator>& __vec) const _NOEXCEPT
        {return __vec.__hash_code();}
};

template <class _Tp, class _Allocator>
bool
operator==(const vector<_Tp, _Allocator>& __x, const vector<_Tp, _Allocator>& __y)
{
    const typename vector<_Tp, _Allocator>::size_type __sz = __x.size();
    return __sz == __y.size() && _VSTD::equal(__x.begin(), __x.end(), __y.begin());
}

template <class _Tp, class _Allocator>
bool
operator!=(const vector<_Tp, _Allocator>& __x, const vector<_Tp, _Allocator>& __y)
{
    return !(__x == __y);
}

template <class _Tp, class _Allocator>
bool
operator< (const vector<_Tp, _Allocator>& __x, const vector<_Tp, _Allocator>& __y)
{
    return _VSTD::lexicographical_compare(__x.begin(), __x.end(), __y.begin(), __y.end());
}

template <class _Tp, class _Allocator>
bool    operator> (const vector<_Tp, _Allocator>& __x, const vector<_Tp, _Allocator>& __y)
{
    return __y < __x;
}

template <class _Tp, class _Allocator>
bool    operator>=(const vector<_Tp, _Allocator>& __x, const vector<_Tp, _Allocator>& __y)
{
    return !(__x < __y);
}

template <class _Tp, class _Allocator>
bool    operator<=(const vector<_Tp, _Allocator>& __x, const vector<_Tp, _Allocator>& __y)
{
    return !(__y < __x);
}

template <class _Tp, class _Allocator>
void swap(vector<_Tp, _Allocator>& __x, vector<_Tp, _Allocator>& __y) _NOEXCEPT_(_NOEXCEPT_(__x.swap(__y)))
{
    __x.swap(__y);
}

#endif