#ifndef __MySmDelegateInstance_H
#define __MySmDelegateInstance_H

using namespace MyNS;

namespace MyNS
{
	/**
	 * @brief ��ƫ�ػ�
	 */
	template <typename T>
	class MySmDelegate;

	/**
	 * ƫ�ػ�
	 *
	 * \tparam T            ������
	 * \tparam R            ��������ֵ����
	 * \tparam params       ���������б�
	 */
	template <typename T, typename R, typename... Params>
	class MySmDelegate<R (T::*)(Params...)>
	{
	public:
		typedef R (T::*MethodPtrType)(Params...);

		MySmDelegate(MethodPtrType func, T& callee)
			: mUserObject(callee)
			, mMethodPtr(func)
		{}

		R operator()(Params... args) const
		{
			return (mUserObject.*mMethodPtr)(args...);
		}

		bool operator==(const delegate& other) const
		{
			return (&mUserObject == &other.mUserObject) && (mMethodPtr == other.mMethodPtr);
		}
		bool operator!= (const delegate& other) const
		{
			return !((*this) == other);
		}

	private:
		T& mUserObject;
		MethodPtrType mMethodPtr;
	};

	/**
	 * ƫ�ػ�
	 */
	template <typename T, typename R, typename... Params>
	class MySmDelegate<R (T::*)(Params...) const>
	{
	public:
		typedef R (T::*MethodPtrType)(Params...) const;

		MySmDelegate(MethodPtrType func, const T& callee)
			: mUserObject(callee)
			, mMethodPtr(func)
		{}

		R operator()(Params... args) const
		{
			return (mUserObject.*mMethodPtr)(args...);
		}

		bool operator==(const delegate& other) const
		{
			return (&mUserObject == &other.mUserObject) && (mMethodPtr == other.mMethodPtr);
		}
		bool operator!= (const delegate& other) const
		{
			return !(*this == other);
		}

	private:
		const T& mUserObject;
		MethodPtrType mMethodPtr;
	};

	/**
	 * ƫ�ػ�
	 *
	 * \tparam R            ������������
	 * \tparam params       ���������б�
	 */
	template <typename R, typename... Params>
	class MySmDelegate<R (*)(Params...)>
	{
	public:
		typedef R (*MethodPtrType)(Params...);

		MySmDelegate(MethodPtrType func)
			: mMethodPtr(func)
		{}

		R operator()(Params... args) const
		{
			return (*mMethodPtr)(args...);
		}

		bool operator==(const delegate& other) const
		{
			return mMethodPtr == other.mMethodPtr;
		}
		bool operator!= (const delegate& other) const
		{
			return !((*this) == other);
		}

	private:
		MethodPtrType mMethodPtr;
	};

	/**
	 * �򻯽ӿ�
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
	 * �򻯽ӿ�
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
}

#endif