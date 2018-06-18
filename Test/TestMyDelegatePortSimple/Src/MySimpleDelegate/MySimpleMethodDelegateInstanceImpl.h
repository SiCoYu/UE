#ifndef __MyMiniMethodDelegateInstanceImpl_H
#define __MyMiniMethodDelegateInstanceImpl_H

#include "MySimpleDelegateInstanceBase.h"

namespace MyNS
{

template <typename T>
class MySimpleMethodDelegateInstanceImpl;

template <typename T, typename R, typename... ParamTypes>
class MySimpleMethodDelegateInstanceImpl<R (T::*)(ParamTypes...)> : public MySimpleDelegateInstanceBase<R, ParamTypes...>
{
public:
    typedef R (T::*MethodPtrType)(ParamTypes...);

public:
	MySimpleMethodDelegateInstanceImpl(MethodPtrType func, T* callee)
        : mUserObject(callee)
        , mMethodPtr(func)
    {}

	virtual bool empty() const override
	{
		return (!mUserObject || !mMethodPtr);
	}

	virtual void clear() override
	{
		mUserObject = nullptr;
		mMethodPtr = nullptr;
	}

    R operator()(ParamTypes... args) const
    {
        return (mUserObject->*mMethodPtr)(args...);
    }

    bool operator==(const MySimpleMethodDelegateInstanceImpl& other) const
    {
        return (&mUserObject == &other.mUserObject) && (mMethodPtr == other.mMethodPtr);
    }

    bool operator!= (const MySimpleMethodDelegateInstanceImpl& other) const
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
class MySimpleMethodDelegateInstanceImpl<R (T::*)(ParamTypes...) const> : public MySimpleDelegateInstanceBase<R, ParamTypes...>
{
public:
    typedef R (T::*MethodPtrType)(ParamTypes...) const;

public:
	MySimpleMethodDelegateInstanceImpl(MethodPtrType func, const T* callee)
        : mUserObject(callee)
        , mMethodPtr(func)
    {}

	virtual bool empty() const override
	{
		return (!mUserObject || !mMethodPtr);
	}

	virtual void clear() override
	{
		mUserObject = nullptr;
		mMethodPtr = nullptr;
	}

    R operator()(ParamTypes... args) const
    {
        return (mUserObject->*mMethodPtr)(args...);
    }

    bool operator==(const MySimpleMethodDelegateInstanceImpl& other) const
    {
        return (&mUserObject == &other.mUserObject) && (mMethodPtr == other.mMethodPtr);
    }

    bool operator!= (const MySimpleMethodDelegateInstanceImpl& other) const
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
class MySimpleMethodDelegateInstanceImpl<R (*)(ParamTypes...)> : public MySimpleDelegateInstanceBase<R, ParamTypes...>
{
public:
    typedef R (*MethodPtrType)(ParamTypes...);

public:
	MySimpleMethodDelegateInstanceImpl(MethodPtrType func)
        : mMethodPtr(func)
    {}

	virtual bool empty() const override
	{
		return !mMethodPtr;
	}

	virtual void clear() override
	{
		mMethodPtr = nullptr;
	}

    R operator()(ParamTypes... args) const
    {
        return (*mMethodPtr)(args...);
    }

    bool operator==(const MySimpleMethodDelegateInstanceImpl& other) const
    {
        return mMethodPtr == other.mMethodPtr;
    }

    bool operator!= (const MySimpleMethodDelegateInstanceImpl& other) const
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
MySimpleMethodDelegateInstanceImpl<F>* makeDelegate(F func, T& obj)
{
    return new MySimpleMethodDelegateInstanceImpl<F>(func, obj);
}

template <typename T>
MySimpleMethodDelegateInstanceImpl<T>* makeDelegate(T func)
{
    return new MySimpleMethodDelegateInstanceImpl<T>(func);
}

}

#endif