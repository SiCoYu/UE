#ifndef __MyMiniMethodDelegateInstanceImpl_H
#define __MyMiniMethodDelegateInstanceImpl_H

#include "MyMiniDelegateInstanceBase.h"

namespace MyNS
{

template <typename T>
class MyMiniMethodDelegateInstanceImpl;

template <typename T, typename R, typename... ParamTypes>
class MyMiniMethodDelegateInstanceImpl<R (T::*)(ParamTypes...)> : public MyMiniDelegateInstanceBase<R, ParamTypes...>
{
public:
    typedef R (T::*MethodPtrType)(ParamTypes...);

	MyMiniMethodDelegateInstanceImpl(MethodPtrType func, T* callee)
        : mUserObject(callee)
        , mMethodPtr(func)
    {}

    R operator()(ParamTypes... args) const
    {
        return (mUserObject->*mMethodPtr)(args...);
    }

    bool operator==(const MyMiniMethodDelegateInstanceImpl& other) const
    {
        return (&mUserObject == &other.mUserObject) && (mMethodPtr == other.mMethodPtr);
    }

    bool operator!= (const MyMiniMethodDelegateInstanceImpl& other) const
    {
        return !((*this) == other);
    }

	virtual RetValType call(ParamTypes... Params) const override
	{
		return this->operator()(Params...);
	}

private:
    T* mUserObject;
    MethodPtrType mMethodPtr;
};

template <typename T, typename R, typename... ParamTypes>
class MyMiniMethodDelegateInstanceImpl<R (T::*)(ParamTypes...) const> : public MyMiniDelegateInstanceBase<R, ParamTypes...>
{
public:
    typedef R (T::*MethodPtrType)(ParamTypes...) const;

	MyMiniMethodDelegateInstanceImpl(MethodPtrType func, const T* callee)
        : mUserObject(callee)
        , mMethodPtr(func)
    {}

    R operator()(ParamTypes... args) const
    {
        return (mUserObject->*mMethodPtr)(args...);
    }

    bool operator==(const MyMiniMethodDelegateInstanceImpl& other) const
    {
        return (&mUserObject == &other.mUserObject) && (mMethodPtr == other.mMethodPtr);
    }

    bool operator!= (const MyMiniMethodDelegateInstanceImpl& other) const
    {
        return !(*this == other);
    }

	virtual RetValType call(ParamTypes... Params) const override
	{
		return this->operator()(Params...);
	}

private:
    const T* mUserObject;
    MethodPtrType mMethodPtr;
};

/**
 * @brief 非成员函数没有 const 偏特化
 */
template <typename R, typename... ParamTypes>
class MyMiniMethodDelegateInstanceImpl<R (*)(ParamTypes...)> : public MyMiniDelegateInstanceBase<R, ParamTypes...>
{
public:
    typedef R (*MethodPtrType)(ParamTypes...);

	MyMiniMethodDelegateInstanceImpl(MethodPtrType func)
        : mMethodPtr(func)
    {}

    R operator()(ParamTypes... args) const
    {
        return (*mMethodPtr)(args...);
    }

    bool operator==(const MyMiniMethodDelegateInstanceImpl& other) const
    {
        return mMethodPtr == other.mMethodPtr;
    }

    bool operator!= (const MyMiniMethodDelegateInstanceImpl& other) const
    {
        return !((*this) == other);
    }

	virtual RetValType call(ParamTypes... Params) const override
	{
		return this->operator()(Params...);
	}

private:
    MethodPtrType mMethodPtr;
};

template <typename F, typename T>
MyMiniMethodDelegateInstanceImpl<F>* makeDelegate(F func, T& obj)
{
    return new MyMiniMethodDelegateInstanceImpl<F>(func, obj);
}

template <typename T>
MyMiniMethodDelegateInstanceImpl<T>* makeDelegate(T func)
{
    return new MyMiniMethodDelegateInstanceImpl<T>(func);
}

}

#endif