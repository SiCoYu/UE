#ifndef __MyMiniClosureDelegateInstanceImpl_H
#define __MyMiniClosureDelegateInstanceImpl_H

#include "MySimpleDelegateInstanceBase.h"

namespace MyNS
{

// ����ָ�뷺��
template <typename T>
class MySimpleClosureDelegateInstanceImpl;

// ����ָ���ػ�
// �޷��ƶϣ��ɱ�ģ�����Ҫ������󣬷��������ƶϵ������ʵ��
//template <typename T, typename R, typename... ParamTypes, typename B>
//class MySimpleClosureDelegateInstanceImpl<R (T::*)(ParamTypes..., B)> : public MySimpleDelegateInstanceBase<R, ParamTypes...>
template <typename T, typename R, typename B, typename... ParamTypes>
class MySimpleClosureDelegateInstanceImpl<R(T::*)(B, ParamTypes...)> : public MySimpleDelegateInstanceBase<R, ParamTypes...>
{
public:
    typedef R (T::*MethodPtrType)(B, ParamTypes...);

public:
	MySimpleClosureDelegateInstanceImpl(MethodPtrType func, T* callee, B bound)
        : mUserObject(callee)
        , mMethodPtr(func)
        , mBound(bound)
    {
    }

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
        return (mUserObject->*mMethodPtr)(mBound, args...);
    }

    bool operator==(const MySimpleClosureDelegateInstanceImpl &other) const
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
class MySimpleClosureDelegateInstanceImpl<R (T::*)(B, ParamTypes...) const> : public MySimpleDelegateInstanceBase<R, ParamTypes...>
{
public:
	typedef R (T::*MethodPtrType)(B, ParamTypes...) const;

public:
	MySimpleClosureDelegateInstanceImpl(MethodPtrType func, T* callee, B bound)
		: mUserObject(callee)
		, mMethodPtr(func)
		, mBound(bound)
	{
	}

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
		return (mUserObject->*mMethodPtr)(mBound, args...);
	}

	bool operator==(const MySimpleClosureDelegateInstanceImpl &other) const
	{
		return (mUserObject == other.mUserObject) && (mMethodPtr == other.mMethodPtr) &&
			(mBound == other.mBound);
	}

	virtual RetValType call(ParamTypes... Params) const override
	{
		return this->operator()(Params...);
	}

private:
	// �������ط�д T *mUserObject ����Ҫ�Լ��ڵ��õ�ʱ��ȥ��ָ�볣��
	const T *mUserObject;
	MethodPtrType mMethodPtr;
	B mBound;
};

template <typename T>
class MyMiniClosureDelegateInstanceImpl2;

template <typename T, typename R, typename B1, typename B2, typename... ParamTypes>
class MyMiniClosureDelegateInstanceImpl2<R (T::*)(B1, B2, ParamTypes...)> : public MySimpleDelegateInstanceBase<R, ParamTypes...>
{
public:
    typedef R (T::*MethodPtrType)(B1, B2, ParamTypes...);

public:
	MyMiniClosureDelegateInstanceImpl2(MethodPtrType func, T* callee, B1 bound1, B2 bound2)
        : mUserObject(callee)
        , mMethodPtr(func)
        , mBound(bound1)
        , mBound2(bound2)
    {
    }

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
class MyMiniClosureDelegateInstanceImpl2<R (T::*)(B1, B2, ParamTypes...) const> : public MySimpleDelegateInstanceBase<R, ParamTypes...>
{
public:
	typedef R (T::*MethodPtrType)(B1, B2, ParamTypes...) const;

public:
	MyMiniClosureDelegateInstanceImpl2(MethodPtrType func, T* callee, B1 bound1, B2 bound2)
		: mUserObject(callee)
		, mMethodPtr(func)
		, mBound(bound1)
		, mBound2(bound2)
	{
	}

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
MySimpleClosureDelegateInstanceImpl<F>* makeClosure(F func, T* obj, B b)
{
    return new MySimpleClosureDelegateInstanceImpl<F>(func, obj, b);
}

template <typename F, typename T, typename B1, typename B2>
MyMiniClosureDelegateInstanceImpl2<F>* makeClosure2(F func, T* obj, B1 b1, B2 b2)
{
    return new MyMiniClosureDelegateInstanceImpl2<F>(func, obj, b1, b2);
}

template <typename F, typename T, typename B>
MySimpleClosureDelegateInstanceImpl<F>* makeDelegate(F func, T* obj, B b)
{
	return makeClosure(func, obj, b);
}

template <typename F, typename T, typename B1, typename B2>
MyMiniClosureDelegateInstanceImpl2<F>* makeDelegate(F func, T* obj, B1 b1, B2 b2)
{
	return new makeClosure2(func, obj, b1, b2);
}

}

#endif