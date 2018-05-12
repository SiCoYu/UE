#ifndef __MySmDelegate_H
#define __MySmDelegate_H

namespace MyNS
{
	/**
	 * non specialized template declaration for delegate
	 */
	template <typename T>
	class MySmDelegate;

	/**
	 * specialization for member functions
	 *
	 * \tparam T            class-type of the object who's member function to call
	 * \tparam R            return type of the function that gets captured
	 * \tparam params       variadic template list for possible arguments
	 *                      of the captured function
	 */
	template <typename T, typename R, typename... Params>
	class MySmDelegate<R (T::*)(Params...)>
	{
	public:
		typedef R (T::*func_type)(Params...);

		MySmDelegate(func_type func, T& callee)
			: callee_(callee)
			, func_(func)
		{}

		R operator()(Params... args) const
		{
			return (callee_.*func_)(args...);
		}

		bool operator==(const delegate& other) const
		{
			return (&callee_ == &other.callee_) && (func_ == other.func_);
		}
		bool operator!= (const delegate& other) const
		{
			return !((*this) == other);
		}

	private:
		T& callee_;
		func_type func_;
	};

	/**
	 * specialization for const member functions
	 */
	template <typename T, typename R, typename... Params>
	class MySmDelegate<R (T::*)(Params...) const>
	{
	public:
		typedef R (T::*func_type)(Params...) const;

		MySmDelegate(func_type func, const T& callee)
			: callee_(callee)
			, func_(func)
		{}

		R operator()(Params... args) const
		{
			return (callee_.*func_)(args...);
		}

		bool operator==(const delegate& other) const
		{
			return (&callee_ == &other.callee_) && (func_ == other.func_);
		}
		bool operator!= (const delegate& other) const
		{
			return !(*this == other);
		}

	private:
		const T& callee_;
		func_type func_;
	};

	/**
	 * specialization for free functions
	 *
	 * \tparam R            return type of the function that gets captured
	 * \tparam params       variadic template list for possible arguments
	 *                      of the captured function
	 */
	template <typename R, typename... Params>
	class MySmDelegate<R (*)(Params...)>
	{
	public:
		typedef R (*func_type)(Params...);

		MySmDelegate(func_type func)
			: func_(func)
		{}

		R operator()(Params... args) const
		{
			return (*func_)(args...);
		}

		bool operator==(const delegate& other) const
		{
			return func_ == other.func_;
		}
		bool operator!= (const delegate& other) const
		{
			return !((*this) == other);
		}

	private:
		func_type func_;
	};

	/**
	 * function to deduce template parameters from call-context
	 */
	template <typename F, typename T>
	MySmDelegate<F> make_delegate(F func, T& obj)
	{
		return MySmDelegate<F>(func, obj);
	}

	template <typename T>
	MySmDelegate<T> make_delegate(T func)
	{
		return MySmDelegate<T>(func);
	}

	/**
	 * function to deduce template parameters from call-context
	 */
	template <typename F, typename T>
	delegate<F> make_delegate(F func, T& obj)
	{
		return MySmDelegate<F>(func, obj);
	}

	// TODO:
	template <typename F, typename T>
	delegate<F> make_delegate(T& obj, F func)
	{
		return MySmDelegate<F>(func, obj);
	}

	template <typename T>
	delegate<T> make_delegate(T func)
	{
		return MySmDelegate<T>(func);
	}

	#endif

}

#endif