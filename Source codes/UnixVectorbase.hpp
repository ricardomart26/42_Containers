template <class _Tp, class _Allocator>
class __vector_base : protected __vector_base_common<true>
{
	public:
		typedef _Allocator									allocator_type;
		typedef allocator_traits<allocator_type>			__alloc_traits;
		typedef typename __alloc_traits::size_type			size_type;
	
	protected:
		typedef _Tp											value_type;
		typedef value_type&									reference;
		typedef const value_type&							const_reference;
		typedef typename __alloc_traits::difference_type	difference_type;
		typedef typename __alloc_traits::pointer			pointer;
		typedef typename __alloc_traits::const_pointer		const_pointer;
		typedef pointer										iterator;
		typedef const_pointer								const_iterator;

		pointer												__begin_;
		pointer												__end_;
		__compressed_pair<pointer, allocator_type>			__end_cap_;

		allocator_type& __alloc() _NOEXCEPT
			{return __end_cap_.second();}

		const allocator_type& __alloc() const _NOEXCEPT
			{return __end_cap_.second();}

		pointer& __end_cap() _NOEXCEPT
			{return __end_cap_.first();}

		const pointer& __end_cap() const _NOEXCEPT
			{return __end_cap_.first();}

		__vector_base()
			_NOEXCEPT_(is_nothrow_default_constructible<allocator_type>::value);
		_LIBCPP_INLINE_VISIBILITY __vector_base(const allocator_type& __a);
		_LIBCPP_INLINE_VISIBILITY __vector_base(allocator_type&& __a) _NOEXCEPT;
		~__vector_base();

		void clear() _NOEXCEPT {__destruct_at_end(__begin_);}

		size_type capacity() const _NOEXCEPT
			{return static_cast<size_type>(__end_cap() - __begin_);}

		void __destruct_at_end(pointer __new_last) _NOEXCEPT;

		void __copy_assign_alloc(const __vector_base& __c)
			{__copy_assign_alloc(__c, integral_constant<bool,
						  __alloc_traits::propagate_on_container_copy_assignment::value>());}

		void __move_assign_alloc(__vector_base& __c)
			_NOEXCEPT_(
				!__alloc_traits::propagate_on_container_move_assignment::value ||
				is_nothrow_move_assignable<allocator_type>::value)
			{__move_assign_alloc(__c, integral_constant<bool,
						  __alloc_traits::propagate_on_container_move_assignment::value>());}


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

		void __move_assign_alloc(__vector_base& __c, true_type)
			_NOEXCEPT_(is_nothrow_move_assignable<allocator_type>::value)
			{__alloc() = _VSTD::move(__c.__alloc());}

		void __move_assign_alloc(__vector_base&, false_type)
			_NOEXCEPT {}
};  
