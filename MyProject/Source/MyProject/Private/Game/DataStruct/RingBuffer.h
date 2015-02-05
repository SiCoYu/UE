#ifndef __CIRCULARBUFFER_H
#define __CIRCULARBUFFER_H

class RingBuffer
{
//private:
//	//! The internal buffer used for storing elements in the circular buffer.
//	pointer m_buff;
//
//	//! The virtual beginning of the circular buffer.
//	pointer m_first;
//
//	//! The virtual end of the circular buffer (one behind the last element).
//	pointer m_last;
//
//	//! The number of items currently stored in the circular buffer.
//	size_type m_size;
//public:
//	//! Linearize the internal buffer into a continuous array.
//	/*!
//	This method can be useful when passing the stored data into a legacy C API as an array.
//	\post <code>\&(*this)[0] \< \&(*this)[1] \< ... \< \&(*this)[size() - 1]</code>
//	\return A pointer to the beginning of the array or <code>0</code> if empty.
//	\throws <a href="circular_buffer/implementation.html#circular_buffer.implementation.exceptions_of_move_if_noexcept_t">Exceptions of move_if_noexcept(T&)</a>.
//	\par Exception Safety
//	Basic; no-throw if the operations in the <i>Throws</i> section do not throw anything.
//	\par Iterator Invalidation
//	Invalidates all iterators pointing to the <code>circular_buffer</code> (except iterators equal to
//	<code>end()</code>); does not invalidate any iterators if the postcondition (the <i>Effect</i>) is already
//	met prior calling this method.
//	\par Complexity
//	Linear (in the size of the <code>circular_buffer</code>); constant if the postcondition (the
//	<i>Effect</i>) is already met.
//	\warning In general invoking any method which modifies the internal state of the <code>circular_buffer</code>
//	may delinearize the internal buffer and invalidate the returned pointer.
//	\sa <code>array_one()</code> and <code>array_two()</code> for the other option how to pass data into a legacy
//	C API; <code>is_linearized()</code>, <code>rotate(const_iterator)</code>
//	*/
//	pointer linearize() {
//		if (empty())
//			return 0;
//		if (m_first < m_last || m_last == m_buff)
//			return m_first;
//		pointer src = m_first;
//		pointer dest = m_buff;
//		size_type moved = 0;
//		size_type constructed = 0;
//		BOOST_TRY{
//			for (pointer first = m_first; dest < src; src = first) {
//				for (size_type ii = 0; src < m_end; ++src, ++dest, ++moved, ++ii) {
//					if (moved == size()) {
//						first = dest;
//						break;
//					}
//					if (dest == first) {
//						first += ii;
//						break;
//					}
//					if (is_uninitialized(dest)) {
//						boost::container::allocator_traits<Alloc>::construct(m_alloc, boost::addressof(*dest), this_type::move_if_noexcept(*src));
//						++constructed;
//					}
//					else {
//						value_type tmp = this_type::move_if_noexcept(*src);
//						replace(src, this_type::move_if_noexcept(*dest));
//						replace(dest, boost::move(tmp));
//					}
//				}
//			}
//		} BOOST_CATCH(...) {
//			m_last += constructed;
//			m_size += constructed;
//			BOOST_RETHROW
//		}
//		BOOST_CATCH_END
//			for (src = m_end - constructed; src < m_end; ++src)
//				destroy_item(src);
//		m_first = m_buff;
//		m_last = add(m_buff, size());
//#if BOOST_CB_ENABLE_DEBUG
//		invalidate_iterators_except(end());
//#endif
//		return m_buff;
//	}
//
//	//! Is the <code>circular_buffer</code> linearized?
//	/*!
//	\return <code>true</code> if the internal buffer is linearized into a continuous array (i.e. the
//	<code>circular_buffer</code> meets a condition
//	<code>\&(*this)[0] \< \&(*this)[1] \< ... \< \&(*this)[size() - 1]</code>);
//	<code>false</code> otherwise.
//	\throws Nothing.
//	\par Exception Safety
//	No-throw.
//	\par Iterator Invalidation
//	Does not invalidate any iterators.
//	\par Complexity
//	Constant (in the size of the <code>circular_buffer</code>).
//	\sa <code>linearize()</code>, <code>array_one()</code>, <code>array_two()</code>
//	*/
//	bool is_linearized() const BOOST_NOEXCEPT{ return m_first < m_last || m_last == m_buff; }
//
//		//! Rotate elements in the <code>circular_buffer</code>.
//		/*!
//		A more effective implementation of
//		<code><a href="http://www.sgi.com/tech/stl/rotate.html">std::rotate</a></code>.
//		\pre <code>new_begin</code> is a valid iterator pointing to the <code>circular_buffer</code> <b>except</b> its
//		end.
//		\post Before calling the method suppose:<br><br>
//		<code>m == std::distance(new_begin, end())</code><br><code>n == std::distance(begin(), new_begin)</code>
//		<br><code>val_0 == *new_begin, val_1 == *(new_begin + 1), ... val_m == *(new_begin + m)</code><br>
//		<code>val_r1 == *(new_begin - 1), val_r2 == *(new_begin - 2), ... val_rn == *(new_begin - n)</code><br>
//		<br>then after call to the method:<br><br>
//		<code>val_0 == (*this)[0] \&\& val_1 == (*this)[1] \&\& ... \&\& val_m == (*this)[m - 1] \&\& val_r1 ==
//		(*this)[m + n - 1] \&\& val_r2 == (*this)[m + n - 2] \&\& ... \&\& val_rn == (*this)[m]</code>
//		\param new_begin The new beginning.
//		\throws See <a href="circular_buffer/implementation.html#circular_buffer.implementation.exceptions_of_move_if_noexcept_t">Exceptions of move_if_noexcept(T&)</a>.
//		\par Exception Safety
//		Basic; no-throw if the <code>circular_buffer</code> is full or <code>new_begin</code> points to
//		<code>begin()</code> or if the operations in the <i>Throws</i> section do not throw anything.
//		\par Iterator Invalidation
//		If <code>m \< n</code> invalidates iterators pointing to the last <code>m</code> elements
//		(<b>including</b> <code>new_begin</code>, but not iterators equal to <code>end()</code>) else invalidates
//		iterators pointing to the first <code>n</code> elements; does not invalidate any iterators if the
//		<code>circular_buffer</code> is full.
//		\par Complexity
//		Linear (in <code>(std::min)(m, n)</code>); constant if the <code>circular_buffer</code> is full.
//		\sa <code><a href="http://www.sgi.com/tech/stl/rotate.html">std::rotate</a></code>
//		*/
//		void rotate(const_iterator new_begin) {
//		BOOST_CB_ASSERT(new_begin.is_valid(this)); // check for uninitialized or invalidated iterator
//		BOOST_CB_ASSERT(new_begin.m_it != 0);      // check for iterator pointing to end()
//		if (full()) {
//			m_first = m_last = const_cast<pointer>(new_begin.m_it);
//		}
//		else {
//			difference_type m = end() - new_begin;
//			difference_type n = new_begin - begin();
//			if (m < n) {
//				for (; m > 0; --m) {
//					push_front(this_type::move_if_noexcept(back()));
//					pop_back();
//				}
//			}
//			else {
//				for (; n > 0; --n) {
//					push_back(this_type::move_if_noexcept(front()));
//					pop_front();
//				}
//			}
//		}
//	}
//
//	// Size and capacity
//
//	//! Get the number of elements currently stored in the <code>circular_buffer</code>.
//	/*!
//	\return The number of elements stored in the <code>circular_buffer</code>.
//	\throws Nothing.
//	\par Exception Safety
//	No-throw.
//	\par Iterator Invalidation
//	Does not invalidate any iterators.
//	\par Complexity
//	Constant (in the size of the <code>circular_buffer</code>).
//	\sa <code>capacity()</code>, <code>max_size()</code>, <code>reserve()</code>,
//	<code>\link resize() resize(size_type, const_reference)\endlink</code>
//	*/
//	size_type size() const BOOST_NOEXCEPT{ return m_size; }
//
//		//! Is the <code>circular_buffer</code> empty?
//		/*!
//		\return <code>true</code> if there are no elements stored in the <code>circular_buffer</code>;
//		<code>false</code> otherwise.
//		\throws Nothing.
//		\par Exception Safety
//		No-throw.
//		\par Iterator Invalidation
//		Does not invalidate any iterators.
//		\par Complexity
//		Constant (in the size of the <code>circular_buffer</code>).
//		\sa <code>full()</code>
//		*/
//	bool empty() const BOOST_NOEXCEPT{ return size() == 0; }
//
//		//! Is the <code>circular_buffer</code> full?
//		/*!
//		\return <code>true</code> if the number of elements stored in the <code>circular_buffer</code>
//		equals the capacity of the <code>circular_buffer</code>; <code>false</code> otherwise.
//		\throws Nothing.
//		\par Exception Safety
//		No-throw.
//		\par Iterator Invalidation
//		Does not invalidate any iterators.
//		\par Complexity
//		Constant (in the size of the <code>circular_buffer</code>).
//		\sa <code>empty()</code>
//		*/
//	bool full() const BOOST_NOEXCEPT{ return capacity() == size(); }
//
//		/*! \brief Get the maximum number of elements which can be inserted into the <code>circular_buffer</code> without
//		overwriting any of already stored elements.
//		\return <code>capacity() - size()</code>
//		\throws Nothing.
//		\par Exception Safety
//		No-throw.
//		\par Iterator Invalidation
//		Does not invalidate any iterators.
//		\par Complexity
//		Constant (in the size of the <code>circular_buffer</code>).
//		\sa <code>capacity()</code>, <code>size()</code>, <code>max_size()</code>
//		*/
//	size_type reserve() const BOOST_NOEXCEPT{ return capacity() - size(); }
//
//		//! Get the capacity of the <code>circular_buffer</code>.
//		/*!
//		\return The maximum number of elements which can be stored in the <code>circular_buffer</code>.
//		\throws Nothing.
//		\par Exception Safety
//		No-throw.
//		\par Iterator Invalidation
//		Does not invalidate any iterators.
//		\par Complexity
//		Constant (in the size of the <code>circular_buffer</code>).
//		\sa <code>reserve()</code>, <code>size()</code>, <code>max_size()</code>,
//		<code>set_capacity(capacity_type)</code>
//		*/
//	capacity_type capacity() const BOOST_NOEXCEPT{ return m_end - m_buff; }
//
//		//! Change the capacity of the <code>circular_buffer</code>.
//		/*!
//		\pre If <code>T</code> is a move only type, then compiler shall support <code>noexcept</code> modifiers
//		and move constructor of <code>T</code> must be marked with it (must not throw exceptions).
//		\post <code>capacity() == new_capacity \&\& size() \<= new_capacity</code><br><br>
//		If the current number of elements stored in the <code>circular_buffer</code> is greater than the desired
//		new capacity then number of <code>[size() - new_capacity]</code> <b>last</b> elements will be removed and
//		the new size will be equal to <code>new_capacity</code>.
//		\param new_capacity The new capacity.
//		\throws "An allocation error" if memory is exhausted, (<code>std::bad_alloc</code> if the standard allocator is
//		used).
//		Whatever <code>T::T(const T&)</code> throws or nothing if <code>T::T(T&&)</code> is noexcept.
//		\par Exception Safety
//		Strong.
//		\par Iterator Invalidation
//		Invalidates all iterators pointing to the <code>circular_buffer</code> (except iterators equal to
//		<code>end()</code>) if the new capacity is different from the original.
//		\par Complexity
//		Linear (in <code>min[size(), new_capacity]</code>).
//		\sa <code>rset_capacity(capacity_type)</code>,
//		<code>\link resize() resize(size_type, const_reference)\endlink</code>
//		*/
//		void set_capacity(capacity_type new_capacity) {
//		if (new_capacity == capacity())
//			return;
//		pointer buff = allocate(new_capacity);
//		iterator b = begin();
//		BOOST_TRY{
//			reset(buff,
//			cb_details::uninitialized_move_if_noexcept(b, b + (std::min)(new_capacity, size()), buff, m_alloc),
//			new_capacity);
//		} BOOST_CATCH(...) {
//			deallocate(buff, new_capacity);
//			BOOST_RETHROW
//		}
//		BOOST_CATCH_END
//	}
//
//	//! Change the size of the <code>circular_buffer</code>.
//	/*!
//	\post <code>size() == new_size \&\& capacity() >= new_size</code><br><br>
//	If the new size is greater than the current size, copies of <code>item</code> will be inserted at the
//	<b>back</b> of the of the <code>circular_buffer</code> in order to achieve the desired size. In the case
//	the resulting size exceeds the current capacity the capacity will be set to <code>new_size</code>.<br>
//	If the current number of elements stored in the <code>circular_buffer</code> is greater than the desired
//	new size then number of <code>[size() - new_size]</code> <b>last</b> elements will be removed. (The
//	capacity will remain unchanged.)
//	\param new_size The new size.
//	\param item The element the <code>circular_buffer</code> will be filled with in order to gain the requested
//	size. (See the <i>Effect</i>.)
//	\throws "An allocation error" if memory is exhausted (<code>std::bad_alloc</code> if the standard allocator is
//	used).
//	Whatever <code>T::T(const T&)</code> throws or nothing if <code>T::T(T&&)</code> is noexcept.
//	\par Exception Safety
//	Basic.
//	\par Iterator Invalidation
//	Invalidates all iterators pointing to the <code>circular_buffer</code> (except iterators equal to
//	<code>end()</code>) if the new size is greater than the current capacity. Invalidates iterators pointing
//	to the removed elements if the new size is lower that the original size. Otherwise it does not invalidate
//	any iterator.
//	\par Complexity
//	Linear (in the new size of the <code>circular_buffer</code>).
//	\sa <code>\link rresize() rresize(size_type, const_reference)\endlink</code>,
//	<code>set_capacity(capacity_type)</code>
//	*/
//	void resize(size_type new_size, param_value_type item = value_type()) {
//		if (new_size > size()) {
//			if (new_size > capacity())
//				set_capacity(new_size);
//			insert(end(), new_size - size(), item);
//		}
//		else {
//			iterator e = end();
//			erase(e - (size() - new_size), e);
//		}
//	}
//
//	//! Change the capacity of the <code>circular_buffer</code>.
//	/*!
//	\pre If <code>T</code> is a move only type, then compiler shall support <code>noexcept</code> modifiers
//	and move constructor of <code>T</code> must be marked with it (must not throw exceptions).
//	\post <code>capacity() == new_capacity \&\& size() \<= new_capacity</code><br><br>
//	If the current number of elements stored in the <code>circular_buffer</code> is greater than the desired
//	new capacity then number of <code>[size() - new_capacity]</code> <b>first</b> elements will be removed
//	and the new size will be equal to <code>new_capacity</code>.
//	\param new_capacity The new capacity.
//	\throws "An allocation error" if memory is exhausted (<code>std::bad_alloc</code> if the standard allocator is
//	used).
//	Whatever <code>T::T(const T&)</code> throws or nothing if <code>T::T(T&&)</code> is noexcept.
//	\par Exception Safety
//	Strong.
//	\par Iterator Invalidation
//	Invalidates all iterators pointing to the <code>circular_buffer</code> (except iterators equal to
//	<code>end()</code>) if the new capacity is different from the original.
//	\par Complexity
//	Linear (in <code>min[size(), new_capacity]</code>).
//	\sa <code>set_capacity(capacity_type)</code>,
//	<code>\link rresize() rresize(size_type, const_reference)\endlink</code>
//	*/
//	void rset_capacity(capacity_type new_capacity) {
//		if (new_capacity == capacity())
//			return;
//		pointer buff = allocate(new_capacity);
//		iterator e = end();
//		BOOST_TRY{
//			reset(buff, cb_details::uninitialized_move_if_noexcept(e - (std::min)(new_capacity, size()),
//			e, buff, m_alloc), new_capacity);
//		} BOOST_CATCH(...) {
//			deallocate(buff, new_capacity);
//			BOOST_RETHROW
//		}
//		BOOST_CATCH_END
//	}
//
//	//! Change the size of the <code>circular_buffer</code>.
//	/*!
//	\post <code>size() == new_size \&\& capacity() >= new_size</code><br><br>
//	If the new size is greater than the current size, copies of <code>item</code> will be inserted at the
//	<b>front</b> of the of the <code>circular_buffer</code> in order to achieve the desired size. In the case
//	the resulting size exceeds the current capacity the capacity will be set to <code>new_size</code>.<br>
//	If the current number of elements stored in the <code>circular_buffer</code> is greater than the desired
//	new size then number of <code>[size() - new_size]</code> <b>first</b> elements will be removed. (The
//	capacity will remain unchanged.)
//	\param new_size The new size.
//	\param item The element the <code>circular_buffer</code> will be filled with in order to gain the requested
//	size. (See the <i>Effect</i>.)
//	\throws "An allocation error" if memory is exhausted (<code>std::bad_alloc</code> if the standard allocator is
//	used).
//	Whatever <code>T::T(const T&)</code> throws or nothing if <code>T::T(T&&)</code> is noexcept.
//	\par Exception Safety
//	Basic.
//	\par Iterator Invalidation
//	Invalidates all iterators pointing to the <code>circular_buffer</code> (except iterators equal to
//	<code>end()</code>) if the new size is greater than the current capacity. Invalidates iterators pointing
//	to the removed elements if the new size is lower that the original size. Otherwise it does not invalidate
//	any iterator.
//	\par Complexity
//	Linear (in the new size of the <code>circular_buffer</code>).
//	\sa <code>\link resize() resize(size_type, const_reference)\endlink</code>,
//	<code>rset_capacity(capacity_type)</code>
//	*/
//	void rresize(size_type new_size, param_value_type item = value_type()) {
//		if (new_size > size()) {
//			if (new_size > capacity())
//				set_capacity(new_size);
//			rinsert(begin(), new_size - size(), item);
//		}
//		else {
//			rerase(begin(), end() - new_size);
//		}
//	}
//
//	// Construction/Destruction
//
//	//! Create an empty <code>circular_buffer</code> with zero capacity.
//	/*!
//	\post <code>capacity() == 0 \&\& size() == 0</code>
//	\param alloc The allocator.
//	\throws Nothing.
//	\par Complexity
//	Constant.
//	\warning Since Boost version 1.36 the behaviour of this constructor has changed. Now the constructor does not
//	allocate any memory and both capacity and size are set to zero. Also note when inserting an element
//	into a <code>circular_buffer</code> with zero capacity (e.g. by
//	<code>\link push_back() push_back(const_reference)\endlink</code> or
//	<code>\link insert(iterator, param_value_type) insert(iterator, value_type)\endlink</code>) nothing
//	will be inserted and the size (as well as capacity) remains zero.
//	\note You can explicitly set the capacity by calling the <code>set_capacity(capacity_type)</code> method or you
//	can use the other constructor with the capacity specified.
//	\sa <code>circular_buffer(capacity_type, const allocator_type& alloc)</code>,
//	<code>set_capacity(capacity_type)</code>
//	*/
//	explicit circular_buffer(const allocator_type& alloc = allocator_type()) BOOST_NOEXCEPT
//		: m_buff(0), m_end(0), m_first(0), m_last(0), m_size(0), m_alloc(alloc) {}
//
//	//! Create an empty <code>circular_buffer</code> with the specified capacity.
//	/*!
//	\post <code>capacity() == buffer_capacity \&\& size() == 0</code>
//	\param buffer_capacity The maximum number of elements which can be stored in the <code>circular_buffer</code>.
//	\param alloc The allocator.
//	\throws "An allocation error" if memory is exhausted (<code>std::bad_alloc</code> if the standard allocator is
//	used).
//	\par Complexity
//	Constant.
//	*/
//	explicit circular_buffer(capacity_type buffer_capacity, const allocator_type& alloc = allocator_type())
//		: m_size(0), m_alloc(alloc) {
//		initialize_buffer(buffer_capacity);
//		m_first = m_last = m_buff;
//	}
//
//	/*! \brief Create a full <code>circular_buffer</code> with the specified capacity and filled with <code>n</code>
//	copies of <code>item</code>.
//	\post <code>capacity() == n \&\& full() \&\& (*this)[0] == item \&\& (*this)[1] == item \&\& ... \&\&
//	(*this)[n - 1] == item </code>
//	\param n The number of elements the created <code>circular_buffer</code> will be filled with.
//	\param item The element the created <code>circular_buffer</code> will be filled with.
//	\param alloc The allocator.
//	\throws "An allocation error" if memory is exhausted (<code>std::bad_alloc</code> if the standard allocator is
//	used).
//	Whatever <code>T::T(const T&)</code> throws.
//	\par Complexity
//	Linear (in the <code>n</code>).
//	*/
//	circular_buffer(size_type n, param_value_type item, const allocator_type& alloc = allocator_type())
//		: m_size(n), m_alloc(alloc) {
//		initialize_buffer(n, item);
//		m_first = m_last = m_buff;
//	}
//
//	/*! \brief Create a <code>circular_buffer</code> with the specified capacity and filled with <code>n</code>
//	copies of <code>item</code>.
//	\pre <code>buffer_capacity >= n</code>
//	\post <code>capacity() == buffer_capacity \&\& size() == n \&\& (*this)[0] == item \&\& (*this)[1] == item
//	\&\& ... \&\& (*this)[n - 1] == item</code>
//	\param buffer_capacity The capacity of the created <code>circular_buffer</code>.
//	\param n The number of elements the created <code>circular_buffer</code> will be filled with.
//	\param item The element the created <code>circular_buffer</code> will be filled with.
//	\param alloc The allocator.
//	\throws "An allocation error" if memory is exhausted (<code>std::bad_alloc</code> if the standard allocator is
//	used).
//	Whatever <code>T::T(const T&)</code> throws.
//	\par Complexity
//	Linear (in the <code>n</code>).
//	*/
//	circular_buffer(capacity_type buffer_capacity, size_type n, param_value_type item,
//		const allocator_type& alloc = allocator_type())
//		: m_size(n), m_alloc(alloc) {
//		BOOST_CB_ASSERT(buffer_capacity >= size()); // check for capacity lower than size
//		initialize_buffer(buffer_capacity, item);
//		m_first = m_buff;
//		m_last = buffer_capacity == n ? m_buff : m_buff + n;
//	}
//
//	//! The copy constructor.
//	/*!
//	Creates a copy of the specified <code>circular_buffer</code>.
//	\post <code>*this == cb</code>
//	\param cb The <code>circular_buffer</code> to be copied.
//	\throws "An allocation error" if memory is exhausted (<code>std::bad_alloc</code> if the standard allocator is
//	used).
//	Whatever <code>T::T(const T&)</code> throws.
//	\par Complexity
//	Linear (in the size of <code>cb</code>).
//	*/
//	circular_buffer(const circular_buffer<T, Alloc>& cb)
//		:
//#if BOOST_CB_ENABLE_DEBUG
//		debug_iterator_registry(),
//#endif
//		m_size(cb.size()), m_alloc(cb.get_allocator()) {
//		initialize_buffer(cb.capacity());
//		m_first = m_buff;
//		BOOST_TRY{
//			m_last = cb_details::uninitialized_copy(cb.begin(), cb.end(), m_buff, m_alloc);
//		} BOOST_CATCH(...) {
//			deallocate(m_buff, cb.capacity());
//			BOOST_RETHROW
//		}
//		BOOST_CATCH_END
//			if (m_last == m_end)
//				m_last = m_buff;
//	}
//
//#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
//	//! The move constructor.
//	/*! \brief Move constructs a <code>circular_buffer</code> from <code>cb</code>, leaving <code>cb</code> empty.
//	\pre C++ compiler with rvalue references support.
//	\post <code>cb.empty()</code>
//	\param cb <code>circular_buffer</code> to 'steal' value from.
//	\throws Nothing.
//	\par Constant.
//	*/
//	circular_buffer(circular_buffer<T, Alloc>&& cb) BOOST_NOEXCEPT
//		: m_buff(0), m_end(0), m_first(0), m_last(0), m_size(0), m_alloc(cb.get_allocator()) {
//		cb.swap(*this);
//	}
//#endif // BOOST_NO_CXX11_RVALUE_REFERENCES
//
//	//! Create a full <code>circular_buffer</code> filled with a copy of the range.
//	/*!
//	\pre Valid range <code>[first, last)</code>.<br>
//	<code>first</code> and <code>last</code> have to meet the requirements of
//	<a href="http://www.sgi.com/tech/stl/InputIterator.html">InputIterator</a>.
//	\post <code>capacity() == std::distance(first, last) \&\& full() \&\& (*this)[0]== *first \&\&
//	(*this)[1] == *(first + 1) \&\& ... \&\& (*this)[std::distance(first, last) - 1] == *(last - 1)</code>
//	\param first The beginning of the range to be copied.
//	\param last The end of the range to be copied.
//	\param alloc The allocator.
//	\throws "An allocation error" if memory is exhausted (<code>std::bad_alloc</code> if the standard allocator is
//	used).
//	Whatever <code>T::T(const T&)</code> throws.
//	\par Complexity
//	Linear (in the <code>std::distance(first, last)</code>).
//	*/
//	template <class InputIterator>
//	circular_buffer(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type())
//		: m_alloc(alloc) {
//		initialize(first, last, is_integral<InputIterator>());
//	}
//
//	//! Create a <code>circular_buffer</code> with the specified capacity and filled with a copy of the range.
//	/*!
//	\pre Valid range <code>[first, last)</code>.<br>
//	<code>first</code> and <code>last</code> have to meet the requirements of
//	<a href="http://www.sgi.com/tech/stl/InputIterator.html">InputIterator</a>.
//	\post <code>capacity() == buffer_capacity \&\& size() \<= std::distance(first, last) \&\&
//	(*this)[0]== *(last - buffer_capacity) \&\& (*this)[1] == *(last - buffer_capacity + 1) \&\& ... \&\&
//	(*this)[buffer_capacity - 1] == *(last - 1)</code><br><br>
//	If the number of items to be copied from the range <code>[first, last)</code> is greater than the
//	specified <code>buffer_capacity</code> then only elements from the range
//	<code>[last - buffer_capacity, last)</code> will be copied.
//	\param buffer_capacity The capacity of the created <code>circular_buffer</code>.
//	\param first The beginning of the range to be copied.
//	\param last The end of the range to be copied.
//	\param alloc The allocator.
//	\throws "An allocation error" if memory is exhausted (<code>std::bad_alloc</code> if the standard allocator is
//	used).
//	Whatever <code>T::T(const T&)</code> throws.
//	\par Complexity
//	Linear (in <code>std::distance(first, last)</code>; in
//	<code>min[capacity, std::distance(first, last)]</code> if the <code>InputIterator</code> is a
//	<a href="http://www.sgi.com/tech/stl/RandomAccessIterator.html">RandomAccessIterator</a>).
//	*/
//	template <class InputIterator>
//	circular_buffer(capacity_type buffer_capacity, InputIterator first, InputIterator last,
//		const allocator_type& alloc = allocator_type())
//		: m_alloc(alloc) {
//		initialize(buffer_capacity, first, last, is_integral<InputIterator>());
//	}
//
//	//! The destructor.
//	/*!
//	Destroys the <code>circular_buffer</code>.
//	\throws Nothing.
//	\par Iterator Invalidation
//	Invalidates all iterators pointing to the <code>circular_buffer</code> (including iterators equal to
//	<code>end()</code>).
//	\par Complexity
//	Constant (in the size of the <code>circular_buffer</code>) for scalar types; linear for other types.
//	\sa <code>clear()</code>
//	*/
//	~circular_buffer() BOOST_NOEXCEPT{
//		destroy();
//#if BOOST_CB_ENABLE_DEBUG
//		invalidate_all_iterators();
//#endif
//	}
//
//public:
//	// Assign methods
//
//	//! The assign operator.
//	/*!
//	Makes this <code>circular_buffer</code> to become a copy of the specified <code>circular_buffer</code>.
//	\post <code>*this == cb</code>
//	\param cb The <code>circular_buffer</code> to be copied.
//	\throws "An allocation error" if memory is exhausted (<code>std::bad_alloc</code> if the standard allocator is
//	used).
//	Whatever <code>T::T(const T&)</code> throws.
//	\par Exception Safety
//	Strong.
//	\par Iterator Invalidation
//	Invalidates all iterators pointing to this <code>circular_buffer</code> (except iterators equal to
//	<code>end()</code>).
//	\par Complexity
//	Linear (in the size of <code>cb</code>).
//	\sa <code>\link assign(size_type, param_value_type) assign(size_type, const_reference)\endlink</code>,
//	<code>\link assign(capacity_type, size_type, param_value_type)
//	assign(capacity_type, size_type, const_reference)\endlink</code>,
//	<code>assign(InputIterator, InputIterator)</code>,
//	<code>assign(capacity_type, InputIterator, InputIterator)</code>
//	*/
//	circular_buffer<T, Alloc>& operator = (const circular_buffer<T, Alloc>& cb) {
//		if (this == &cb)
//			return *this;
//		pointer buff = allocate(cb.capacity());
//		BOOST_TRY{
//			reset(buff, cb_details::uninitialized_copy(cb.begin(), cb.end(), buff, m_alloc), cb.capacity());
//		} BOOST_CATCH(...) {
//			deallocate(buff, cb.capacity());
//			BOOST_RETHROW
//		}
//		BOOST_CATCH_END
//			return *this;
//	}
//
//#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
//	/*! \brief Move assigns content of <code>cb</code> to <code>*this</code>, leaving <code>cb</code> empty.
//	\pre C++ compiler with rvalue references support.
//	\post <code>cb.empty()</code>
//	\param cb <code>circular_buffer</code> to 'steal' value from.
//	\throws Nothing.
//	\par Complexity
//	Constant.
//	*/
//	circular_buffer<T, Alloc>& operator = (circular_buffer<T, Alloc>&& cb) BOOST_NOEXCEPT{
//		cb.swap(*this); // now `this` holds `cb`
//		circular_buffer<T, Alloc>(get_allocator()) // temprary that holds initial `cb` allocator
//			.swap(cb); // makes `cb` empty
//		return *this;
//	}
//#endif // BOOST_NO_CXX11_RVALUE_REFERENCES
//
//		//! Assign <code>n</code> items into the <code>circular_buffer</code>.
//		/*!
//		The content of the <code>circular_buffer</code> will be removed and replaced with <code>n</code> copies of the
//		<code>item</code>.
//		\post <code>capacity() == n \&\& size() == n \&\& (*this)[0] == item \&\& (*this)[1] == item \&\& ... \&\&
//		(*this) [n - 1] == item</code>
//		\param n The number of elements the <code>circular_buffer</code> will be filled with.
//		\param item The element the <code>circular_buffer</code> will be filled with.
//		\throws "An allocation error" if memory is exhausted (<code>std::bad_alloc</code> if the standard allocator is
//		used).
//		Whatever <code>T::T(const T&)</code> throws.
//		\par Exception Safety
//		Basic.
//		\par Iterator Invalidation
//		Invalidates all iterators pointing to the <code>circular_buffer</code> (except iterators equal to
//		<code>end()</code>).
//		\par Complexity
//		Linear (in the <code>n</code>).
//		\sa <code>\link operator=(const circular_buffer&) operator=\endlink</code>,
//		<code>\link assign(capacity_type, size_type, param_value_type)
//		assign(capacity_type, size_type, const_reference)\endlink</code>,
//		<code>assign(InputIterator, InputIterator)</code>,
//		<code>assign(capacity_type, InputIterator, InputIterator)</code>
//		*/
//		void assign(size_type n, param_value_type item) {
//		assign_n(n, n, cb_details::assign_n<param_value_type, allocator_type>(n, item, m_alloc));
//	}
//
//	//! Assign <code>n</code> items into the <code>circular_buffer</code> specifying the capacity.
//	/*!
//	The capacity of the <code>circular_buffer</code> will be set to the specified value and the content of the
//	<code>circular_buffer</code> will be removed and replaced with <code>n</code> copies of the <code>item</code>.
//	\pre <code>capacity >= n</code>
//	\post <code>capacity() == buffer_capacity \&\& size() == n \&\& (*this)[0] == item \&\& (*this)[1] == item
//	\&\& ... \&\& (*this) [n - 1] == item </code>
//	\param buffer_capacity The new capacity.
//	\param n The number of elements the <code>circular_buffer</code> will be filled with.
//	\param item The element the <code>circular_buffer</code> will be filled with.
//	\throws "An allocation error" if memory is exhausted (<code>std::bad_alloc</code> if the standard allocator is
//	used).
//	Whatever <code>T::T(const T&)</code> throws.
//	\par Exception Safety
//	Basic.
//	\par Iterator Invalidation
//	Invalidates all iterators pointing to the <code>circular_buffer</code> (except iterators equal to
//	<code>end()</code>).
//	\par Complexity
//	Linear (in the <code>n</code>).
//	\sa <code>\link operator=(const circular_buffer&) operator=\endlink</code>,
//	<code>\link assign(size_type, param_value_type) assign(size_type, const_reference)\endlink</code>,
//	<code>assign(InputIterator, InputIterator)</code>,
//	<code>assign(capacity_type, InputIterator, InputIterator)</code>
//	*/
//	void assign(capacity_type buffer_capacity, size_type n, param_value_type item) {
//		BOOST_CB_ASSERT(buffer_capacity >= n); // check for new capacity lower than n
//		assign_n(buffer_capacity, n, cb_details::assign_n<param_value_type, allocator_type>(n, item, m_alloc));
//	}
//
//	//! Assign a copy of the range into the <code>circular_buffer</code>.
//	/*!
//	The content of the <code>circular_buffer</code> will be removed and replaced with copies of elements from the
//	specified range.
//	\pre Valid range <code>[first, last)</code>.<br>
//	<code>first</code> and <code>last</code> have to meet the requirements of
//	<a href="http://www.sgi.com/tech/stl/InputIterator.html">InputIterator</a>.
//	\post <code>capacity() == std::distance(first, last) \&\& size() == std::distance(first, last) \&\&
//	(*this)[0]== *first \&\& (*this)[1] == *(first + 1) \&\& ... \&\& (*this)[std::distance(first, last) - 1]
//	== *(last - 1)</code>
//	\param first The beginning of the range to be copied.
//	\param last The end of the range to be copied.
//	\throws "An allocation error" if memory is exhausted (<code>std::bad_alloc</code> if the standard allocator is
//	used).
//	Whatever <code>T::T(const T&)</code> throws.
//	\par Exception Safety
//	Basic.
//	\par Iterator Invalidation
//	Invalidates all iterators pointing to the <code>circular_buffer</code> (except iterators equal to
//	<code>end()</code>).
//	\par Complexity
//	Linear (in the <code>std::distance(first, last)</code>).
//	\sa <code>\link operator=(const circular_buffer&) operator=\endlink</code>,
//	<code>\link assign(size_type, param_value_type) assign(size_type, const_reference)\endlink</code>,
//	<code>\link assign(capacity_type, size_type, param_value_type)
//	assign(capacity_type, size_type, const_reference)\endlink</code>,
//	<code>assign(capacity_type, InputIterator, InputIterator)</code>
//	*/
//	template <class InputIterator>
//	void assign(InputIterator first, InputIterator last) {
//		assign(first, last, is_integral<InputIterator>());
//	}
//
//	//! Assign a copy of the range into the <code>circular_buffer</code> specifying the capacity.
//	/*!
//	The capacity of the <code>circular_buffer</code> will be set to the specified value and the content of the
//	<code>circular_buffer</code> will be removed and replaced with copies of elements from the specified range.
//	\pre Valid range <code>[first, last)</code>.<br>
//	<code>first</code> and <code>last</code> have to meet the requirements of
//	<a href="http://www.sgi.com/tech/stl/InputIterator.html">InputIterator</a>.
//	\post <code>capacity() == buffer_capacity \&\& size() \<= std::distance(first, last) \&\&
//	(*this)[0]== *(last - buffer_capacity) \&\& (*this)[1] == *(last - buffer_capacity + 1) \&\& ... \&\&
//	(*this)[buffer_capacity - 1] == *(last - 1)</code><br><br>
//	If the number of items to be copied from the range <code>[first, last)</code> is greater than the
//	specified <code>buffer_capacity</code> then only elements from the range
//	<code>[last - buffer_capacity, last)</code> will be copied.
//	\param buffer_capacity The new capacity.
//	\param first The beginning of the range to be copied.
//	\param last The end of the range to be copied.
//	\throws "An allocation error" if memory is exhausted (<code>std::bad_alloc</code> if the standard allocator is
//	used).
//	Whatever <code>T::T(const T&)</code> throws.
//	\par Exception Safety
//	Basic.
//	\par Iterator Invalidation
//	Invalidates all iterators pointing to the <code>circular_buffer</code> (except iterators equal to
//	<code>end()</code>).
//	\par Complexity
//	Linear (in <code>std::distance(first, last)</code>; in
//	<code>min[capacity, std::distance(first, last)]</code> if the <code>InputIterator</code> is a
//	<a href="http://www.sgi.com/tech/stl/RandomAccessIterator.html">RandomAccessIterator</a>).
//	\sa <code>\link operator=(const circular_buffer&) operator=\endlink</code>,
//	<code>\link assign(size_type, param_value_type) assign(size_type, const_reference)\endlink</code>,
//	<code>\link assign(capacity_type, size_type, param_value_type)
//	assign(capacity_type, size_type, const_reference)\endlink</code>,
//	<code>assign(InputIterator, InputIterator)</code>
//	*/
//	template <class InputIterator>
//	void assign(capacity_type buffer_capacity, InputIterator first, InputIterator last) {
//		assign(buffer_capacity, first, last, is_integral<InputIterator>());
//	}
//
//	//! Swap the contents of two <code>circular_buffer</code>s.
//	/*!
//	\post <code>this</code> contains elements of <code>cb</code> and vice versa; the capacity of <code>this</code>
//	equals to the capacity of <code>cb</code> and vice versa.
//	\param cb The <code>circular_buffer</code> whose content will be swapped.
//	\throws Nothing.
//	\par Exception Safety
//	No-throw.
//	\par Iterator Invalidation
//	Invalidates all iterators of both <code>circular_buffer</code>s. (On the other hand the iterators still
//	point to the same elements but within another container. If you want to rely on this feature you have to
//	turn the <a href="#debug">Debug Support</a> off otherwise an assertion will report an error if such
//	invalidated iterator is used.)
//	\par Complexity
//	Constant (in the size of the <code>circular_buffer</code>).
//	\sa <code>swap(circular_buffer<T, Alloc>&, circular_buffer<T, Alloc>&)</code>
//	*/
//	void swap(circular_buffer<T, Alloc>& cb) BOOST_NOEXCEPT{
//		swap_allocator(cb, is_stateless<allocator_type>());
//		std::swap(m_buff, cb.m_buff);
//		std::swap(m_end, cb.m_end);
//		std::swap(m_first, cb.m_first);
//		std::swap(m_last, cb.m_last);
//		std::swap(m_size, cb.m_size);
//#if BOOST_CB_ENABLE_DEBUG
//		invalidate_all_iterators();
//		cb.invalidate_all_iterators();
//#endif
//	}
//
//		// push and pop
//private:
//	template <class ValT>
//	void push_back_impl(ValT item) {
//		if (full()) {
//			if (empty())
//				return;
//			replace(m_last, static_cast<ValT>(item));
//			increment(m_last);
//			m_first = m_last;
//		}
//		else {
//			boost::container::allocator_traits<Alloc>::construct(m_alloc, boost::addressof(*m_last), static_cast<ValT>(item));
//			increment(m_last);
//			++m_size;
//		}
//	}
//
//	template <class ValT>
//	void push_front_impl(ValT item) {
//		BOOST_TRY{
//			if (full()) {
//				if (empty())
//					return;
//				decrement(m_first);
//				replace(m_first, static_cast<ValT>(item));
//				m_last = m_first;
//			}
//			else {
//				decrement(m_first);
//				boost::container::allocator_traits<Alloc>::construct(m_alloc, boost::addressof(*m_first), static_cast<ValT>(item));
//				++m_size;
//			}
//		} BOOST_CATCH(...) {
//			increment(m_first);
//			BOOST_RETHROW
//		}
//		BOOST_CATCH_END
//	}
//
//public:
//	//! Insert a new element at the end of the <code>circular_buffer</code>.
//	/*!
//	\post if <code>capacity() > 0</code> then <code>back() == item</code><br>
//	If the <code>circular_buffer</code> is full, the first element will be removed. If the capacity is
//	<code>0</code>, nothing will be inserted.
//	\param item The element to be inserted.
//	\throws Whatever <code>T::T(const T&)</code> throws.
//	Whatever <code>T::operator = (const T&)</code> throws.
//	\par Exception Safety
//	Basic; no-throw if the operation in the <i>Throws</i> section does not throw anything.
//	\par Iterator Invalidation
//	Does not invalidate any iterators with the exception of iterators pointing to the overwritten element.
//	\par Complexity
//	Constant (in the size of the <code>circular_buffer</code>).
//	\sa <code>\link push_front() push_front(const_reference)\endlink</code>,
//	<code>pop_back()</code>, <code>pop_front()</code>
//	*/
//	void push_back(param_value_type item) {
//		push_back_impl<param_value_type>(item);
//	}
//
//	//! Insert a new element at the end of the <code>circular_buffer</code> using rvalue references or rvalues references emulation.
//	/*!
//	\post if <code>capacity() > 0</code> then <code>back() == item</code><br>
//	If the <code>circular_buffer</code> is full, the first element will be removed. If the capacity is
//	<code>0</code>, nothing will be inserted.
//	\param item The element to be inserted.
//	\throws Whatever <code>T::T(T&&)</code> throws.
//	Whatever <code>T::operator = (T&&)</code> throws.
//	\par Exception Safety
//	Basic; no-throw if the operation in the <i>Throws</i> section does not throw anything.
//	\par Iterator Invalidation
//	Does not invalidate any iterators with the exception of iterators pointing to the overwritten element.
//	\par Complexity
//	Constant (in the size of the <code>circular_buffer</code>).
//	\sa <code>\link push_front() push_front(const_reference)\endlink</code>,
//	<code>pop_back()</code>, <code>pop_front()</code>
//	*/
//	void push_back(rvalue_type item) {
//		push_back_impl<rvalue_type>(boost::move(item));
//	}
//
//	//! Insert a new default-constructed element at the end of the <code>circular_buffer</code>.
//	/*!
//	\post if <code>capacity() > 0</code> then <code>back() == item</code><br>
//	If the <code>circular_buffer</code> is full, the first element will be removed. If the capacity is
//	<code>0</code>, nothing will be inserted.
//	\throws Whatever <code>T::T()</code> throws.
//	Whatever <code>T::T(T&&)</code> throws.
//	Whatever <code>T::operator = (T&&)</code> throws.
//	\par Exception Safety
//	Basic; no-throw if the operation in the <i>Throws</i> section does not throw anything.
//	\par Iterator Invalidation
//	Does not invalidate any iterators with the exception of iterators pointing to the overwritten element.
//	\par Complexity
//	Constant (in the size of the <code>circular_buffer</code>).
//	\sa <code>\link push_front() push_front(const_reference)\endlink</code>,
//	<code>pop_back()</code>, <code>pop_front()</code>
//	*/
//	void push_back() {
//		value_type temp;
//		push_back(boost::move(temp));
//	}
//
//	//! Insert a new element at the beginning of the <code>circular_buffer</code>.
//	/*!
//	\post if <code>capacity() > 0</code> then <code>front() == item</code><br>
//	If the <code>circular_buffer</code> is full, the last element will be removed. If the capacity is
//	<code>0</code>, nothing will be inserted.
//	\param item The element to be inserted.
//	\throws Whatever <code>T::T(const T&)</code> throws.
//	Whatever <code>T::operator = (const T&)</code> throws.
//	\par Exception Safety
//	Basic; no-throw if the operation in the <i>Throws</i> section does not throw anything.
//	\par Iterator Invalidation
//	Does not invalidate any iterators with the exception of iterators pointing to the overwritten element.
//	\par Complexity
//	Constant (in the size of the <code>circular_buffer</code>).
//	\sa <code>\link push_back() push_back(const_reference)\endlink</code>,
//	<code>pop_back()</code>, <code>pop_front()</code>
//	*/
//	void push_front(param_value_type item) {
//		push_front_impl<param_value_type>(item);
//	}
//
//	//! Insert a new element at the beginning of the <code>circular_buffer</code> using rvalue references or rvalues references emulation.
//	/*!
//	\post if <code>capacity() > 0</code> then <code>front() == item</code><br>
//	If the <code>circular_buffer</code> is full, the last element will be removed. If the capacity is
//	<code>0</code>, nothing will be inserted.
//	\param item The element to be inserted.
//	\throws Whatever <code>T::T(T&&)</code> throws.
//	Whatever <code>T::operator = (T&&)</code> throws.
//	\par Exception Safety
//	Basic; no-throw if the operation in the <i>Throws</i> section does not throw anything.
//	\par Iterator Invalidation
//	Does not invalidate any iterators with the exception of iterators pointing to the overwritten element.
//	\par Complexity
//	Constant (in the size of the <code>circular_buffer</code>).
//	\sa <code>\link push_back() push_back(const_reference)\endlink</code>,
//	<code>pop_back()</code>, <code>pop_front()</code>
//	*/
//	void push_front(rvalue_type item) {
//		push_front_impl<rvalue_type>(boost::move(item));
//	}
//
//	//! Insert a new default-constructed element at the beginning of the <code>circular_buffer</code>.
//	/*!
//	\post if <code>capacity() > 0</code> then <code>front() == item</code><br>
//	If the <code>circular_buffer</code> is full, the last element will be removed. If the capacity is
//	<code>0</code>, nothing will be inserted.
//	\throws Whatever <code>T::T()</code> throws.
//	Whatever <code>T::T(T&&)</code> throws.
//	Whatever <code>T::operator = (T&&)</code> throws.
//	\par Exception Safety
//	Basic; no-throw if the operation in the <i>Throws</i> section does not throw anything.
//	\par Iterator Invalidation
//	Does not invalidate any iterators with the exception of iterators pointing to the overwritten element.
//	\par Complexity
//	Constant (in the size of the <code>circular_buffer</code>).
//	\sa <code>\link push_back() push_back(const_reference)\endlink</code>,
//	<code>pop_back()</code>, <code>pop_front()</code>
//	*/
//	void push_front() {
//		value_type temp;
//		push_front(boost::move(temp));
//	}
//
//	//! Remove the last element from the <code>circular_buffer</code>.
//	/*!
//	\pre <code>!empty()</code>
//	\post The last element is removed from the <code>circular_buffer</code>.
//	\throws Nothing.
//	\par Exception Safety
//	No-throw.
//	\par Iterator Invalidation
//	Invalidates only iterators pointing to the removed element.
//	\par Complexity
//	Constant (in the size of the <code>circular_buffer</code>).
//	\sa <code>pop_front()</code>, <code>\link push_back() push_back(const_reference)\endlink</code>,
//	<code>\link push_front() push_front(const_reference)\endlink</code>
//	*/
//	void pop_back() {
//		BOOST_CB_ASSERT(!empty()); // check for empty buffer (back element not available)
//		decrement(m_last);
//		destroy_item(m_last);
//		--m_size;
//	}
//
//	//! Remove the first element from the <code>circular_buffer</code>.
//	/*!
//	\pre <code>!empty()</code>
//	\post The first element is removed from the <code>circular_buffer</code>.
//	\throws Nothing.
//	\par Exception Safety
//	No-throw.
//	\par Iterator Invalidation
//	Invalidates only iterators pointing to the removed element.
//	\par Complexity
//	Constant (in the size of the <code>circular_buffer</code>).
//	\sa <code>pop_back()</code>, <code>\link push_back() push_back(const_reference)\endlink</code>,
//	<code>\link push_front() push_front(const_reference)\endlink</code>
//	*/
//	void pop_front() {
//		BOOST_CB_ASSERT(!empty()); // check for empty buffer (front element not available)
//		destroy_item(m_first);
//		increment(m_first);
//		--m_size;
//	}
};

#endif				// __CIRCULARBUFFER_H