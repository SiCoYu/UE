#ifndef __MySmClosure_H
#define __MySmClosure_H

namespace MyNS
{
	template <typename T>
	class MySmClosure;

	template <typename T, typename R, typename B, typename... Params>
	class MySmClosure<R (T::*)(B, Params...)>
	{
	public:
		typedef R (T::*MethodPtrType)(B, Params...);

		MySmClosure(MethodPtrType func, T &callee, B bound)
			: mUserObject(&callee)
			, mMethodPtr(func)
			, mBound(bound)
		{
		}

		R operator()(Params... args) const
		{
			return (mUserObject->*mMethodPtr)(mBound, args...);
		}

		bool operator==(const closure &other) const
		{
			return (mUserObject == other.mUserObject) && (mMethodPtr == other.mMethodPtr) &&
				   (mBound == other.mBound);
		}

	private:
		T *mUserObject;
		MethodPtrType mMethodPtr;
		B mBound;
	};

	template <typename T>
	class MySmClosure2;

	template <typename T, typename R, typename B1, typename B2, typename... Params>
	class MySmClosure2<R (T::*)(B1, B2, Params...)>
	{
	public:
		typedef R (T::*MethodPtrType)(B1, B2, Params...);

		MySmClosure2(MethodPtrType func, T &callee, B1 bound1, B2 bound2)
			: mUserObject(&callee)
			, mMethodPtr(func)
			, mBound(bound1)
			, mBound2(bound2)
		{
		}

		R operator()(Params... args) const
		{
			return (mUserObject->*mMethodPtr)(mBound, mBound2, args...);
		}

		bool operator==(const closure2 &other) const
		{
			return (mUserObject == other.mUserObject) && (mMethodPtr == other.mMethodPtr) &&
				   (mBound == other.mBound) && (mBound2 == other.mBound2);
		}

	private:
		T *mUserObject;
		MethodPtrType mMethodPtr;
		B1 mBound;
		B2 mBound2;
	};
	template <typename F, typename T, typename B>
	closure<F> make_closure(F func, T &obj, B b)
	{
		return MySmClosure<F>(func, obj, b);
	}
	template <typename F, typename T, typename B1, typename B2>
	closure2<F> make_closure2(F func, T &obj, B1 b1, B2 b2)
	{
		return MySmClosure2<F>(func, obj, b1, b2);
	}
}

#endif