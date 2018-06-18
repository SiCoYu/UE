#ifndef __MyMiniClosureDelegateInstanceImpl_H
#define __MyMiniClosureDelegateInstanceImpl_H

#include "MyMiniDelegateInstanceBase.h"

namespace MyNS
{

// 函数指针泛化
template <typename T>
class MyMiniClosureDelegateInstanceImpl;

// 函数指针特化
// 无法推断，可变模板参数要放在最后，否则总是推断到上面的实现
//template <typename T, typename R, typename... ParamTypes, typename B>
//class MyMiniClosureDelegateInstanceImpl<R (T::*)(ParamTypes..., B)> : public MyMiniDelegateInstanceBase<R, ParamTypes...>
template <typename T, typename R, typename B, typename... ParamTypes>
class MyMiniClosureDelegateInstanceImpl<R(T::*)(B, ParamTypes...)> : public MyMiniDelegateInstanceBase<R, ParamTypes...>
{
public:
    typedef R (T::*MethodPtrType)(B, ParamTypes...);

	MyMiniClosureDelegateInstanceImpl(MethodPtrType func, T* callee, B bound)
        : mUserObject(callee)
        , mMethodPtr(func)
        , mBound(bound)
    {
    }

    R operator()(ParamTypes... args) const
    {
        return (mUserObject->*mMethodPtr)(mBound, args...);
    }

    bool operator==(const MyMiniClosureDelegateInstanceImpl &other) const
    {
        return (mUserObject == other.mUserObject) && (mMethodPtr == other.mMethodPtr) &&
               (mBound == other.mBound);
    }

	virtual RetValType call(ParamTypes... Params) const override
	{
		return this->operator()(Params...);
	}

private:
    T *mUserObject;
    MethodPtrType mMethodPtr;
    B mBound;
};

template <typename T, typename R, typename B, typename... ParamTypes>
class MyMiniClosureDelegateInstanceImpl<R (T::*)(B, ParamTypes...) const> : public MyMiniDelegateInstanceBase<R, ParamTypes...>
{
public:
	typedef R (T::*MethodPtrType)(B, ParamTypes...) const;

	MyMiniClosureDelegateInstanceImpl(MethodPtrType func, T* callee, B bound)
		: mUserObject(callee)
		, mMethodPtr(func)
		, mBound(bound)
	{
	}

	R operator()(ParamTypes... args) const
	{
		return (mUserObject->*mMethodPtr)(mBound, args...);
	}

	bool operator==(const MyMiniClosureDelegateInstanceImpl &other) const
	{
		return (mUserObject == other.mUserObject) && (mMethodPtr == other.mMethodPtr) &&
			(mBound == other.mBound);
	}

	virtual RetValType call(ParamTypes... Params) const override
	{
		return this->operator()(Params...);
	}

private:
	// 如果这个地方写 T *mUserObject ，需要自己在调用的时候去掉指针常量
	const T *mUserObject;
	MethodPtrType mMethodPtr;
	B mBound;
};

template <typename T>
class MyMiniClosureDelegateInstanceImpl2;

template <typename T, typename R, typename B1, typename B2, typename... ParamTypes>
class MyMiniClosureDelegateInstanceImpl2<R (T::*)(B1, B2, ParamTypes...)> : public MyMiniDelegateInstanceBase<R, ParamTypes...>
{
public:
    typedef R (T::*MethodPtrType)(B1, B2, ParamTypes...);

	MyMiniClosureDelegateInstanceImpl2(MethodPtrType func, T* callee, B1 bound1, B2 bound2)
        : mUserObject(callee)
        , mMethodPtr(func)
        , mBound(bound1)
        , mBound2(bound2)
    {
    }

    R operator()(ParamTypes... args) const
    {
        return (mUserObject->*mMethodPtr)(mBound, mBound2, args...);
    }

    bool operator==(const MyMiniClosureDelegateInstanceImpl2 &other) const
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

template <typename T, typename R, typename B1, typename B2, typename... ParamTypes>
class MyMiniClosureDelegateInstanceImpl2<R (T::*)(B1, B2, ParamTypes...) const> : public MyMiniDelegateInstanceBase<R, ParamTypes...>
{
public:
	typedef R (T::*MethodPtrType)(B1, B2, ParamTypes...) const;

	MyMiniClosureDelegateInstanceImpl2(MethodPtrType func, T* callee, B1 bound1, B2 bound2)
		: mUserObject(callee)
		, mMethodPtr(func)
		, mBound(bound1)
		, mBound2(bound2)
	{
	}

	R operator()(ParamTypes... args) const
	{
		return (mUserObject->*mMethodPtr)(mBound, mBound2, args...);
	}

	bool operator==(const MyMiniClosureDelegateInstanceImpl2 &other) const
	{
		return (mUserObject == other.mUserObject) && (mMethodPtr == other.mMethodPtr) &&
			(mBound == other.mBound) && (mBound2 == other.mBound2);
	}

private:
	const T *mUserObject;
	MethodPtrType mMethodPtr;
	B1 mBound;
	B2 mBound2;
};

template <typename F, typename T, typename B>
MyMiniClosureDelegateInstanceImpl<F>* make_closure(F func, T* obj, B b)
{
    return new MyMiniClosureDelegateInstanceImpl<F>(func, obj, b);
}

template <typename F, typename T, typename B1, typename B2>
MyMiniClosureDelegateInstanceImpl2<F>* make_closure2(F func, T* obj, B1 b1, B2 b2)
{
    return new MyMiniClosureDelegateInstanceImpl2<F>(func, obj, b1, b2);
}

template <typename F, typename T, typename B>
MyMiniClosureDelegateInstanceImpl<F>* make_delegate(F func, T* obj, B b)
{
	return make_closure(func, obj, b);
}

template <typename F, typename T, typename B1, typename B2>
MyMiniClosureDelegateInstanceImpl2<F>* make_delegate(F func, T* obj, B1 b1, B2 b2)
{
	return new make_closure2(func, obj, b1, b2);
}

}

#endif