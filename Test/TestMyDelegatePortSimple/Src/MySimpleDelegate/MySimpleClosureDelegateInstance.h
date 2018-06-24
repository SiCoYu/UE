#ifndef __MyMiniClosureDelegateInstance_H
#define __MyMiniClosureDelegateInstance_H

#include "MySimpleDelegateInstanceBase.h"

namespace MyNS
{

// 函数指针泛化
template <typename T>
class MySimpleClosureDelegateInstance;

// 函数指针特化
// 无法推断，可变模板参数要放在最后，否则总是推断到上面的实现
//template <typename T, typename R, typename... ParamTypes, typename B>
//class MySimpleClosureDelegateInstance<R (T::*)(ParamTypes..., B)> : public MySimpleDelegateInstanceBase<R, ParamTypes...>
template <typename T, typename R, typename B, typename... ParamTypes>
class MySimpleClosureDelegateInstance<R(T::*)(B, ParamTypes...)> : public MySimpleDelegateInstanceBase<R, ParamTypes...>
{
public:
    typedef R (T::*MethodPtrType)(B, ParamTypes...);

public:
	MySimpleClosureDelegateInstance(MethodPtrType func, T* callee, B bound)
        : mUserObject(callee)
        , mMethodPtr(func)
        , mBound(bound)
    {
    }

	virtual bool empty() const override
	{
		return (!this->mUserObject || !this->mMethodPtr);
	}

	virtual void clear() override
	{
		this->mUserObject = nullptr;
		this->mMethodPtr = nullptr;
	}

    R operator()(ParamTypes... args) const
    {
        return (this->mUserObject->*this->mMethodPtr)(mBound, args...);
    }

    virtual bool operator == (const MySimpleDelegateInstanceBase &other) const override
    {
		const MySimpleClosureDelegateInstance& rhv = (MySimpleClosureDelegateInstance&)other;

        return ((this->mUserObject == rhv.mUserObject) && 
			    (this->mMethodPtr == rhv.mMethodPtr) &&
                (this->mBound == rhv.mBound));
    }

	virtual bool operator!= (const MySimpleDelegateInstanceBase& other) const override
	{
		return !((*this) == other);
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
class MySimpleClosureDelegateInstance<R (T::*)(B, ParamTypes...) const> : public MySimpleDelegateInstanceBase<R, ParamTypes...>
{
public:
	typedef R (T::*MethodPtrType)(B, ParamTypes...) const;

public:
	MySimpleClosureDelegateInstance(MethodPtrType func, T* callee, B bound)
		: mUserObject(callee)
		, mMethodPtr(func)
		, mBound(bound)
	{
	}

	virtual bool empty() const override
	{
		return (!this->mUserObject || !this->mMethodPtr);
	}

	virtual void clear() override
	{
		this->mUserObject = nullptr;
		this->mMethodPtr = nullptr;
	}

	R operator()(ParamTypes... args) const
	{
		return (this->mUserObject->*this->mMethodPtr)(mBound, args...);
	}

	bool operator == (const MySimpleDelegateInstanceBase &other) const
	{
		const MySimpleClosureDelegateInstance& rhv = (MySimpleClosureDelegateInstance&)other;

		return ((this->mUserObject == rhv.mUserObject) && 
			    (this->mMethodPtr == rhv.mMethodPtr) &&
			    (this->mBound == rhv.mBound));
	}

	virtual bool operator!= (const MySimpleDelegateInstanceBase& other) const override
	{
		return !((*this) == other);
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

template <typename R, typename B, typename... ParamTypes>
class MySimpleClosureDelegateInstance<R(*)(B, ParamTypes...)> : public MySimpleDelegateInstanceBase<R, ParamTypes...>
{
public:
	typedef R(*MethodPtrType)(B, ParamTypes...);

public:
	MySimpleClosureDelegateInstance(MethodPtrType func, B bound)
		: mMethodPtr(func), 
		  mBound(bound1)
	{
	}

	virtual bool empty() const override
	{
		return (!this->mMethodPtr);
	}

	virtual void clear() override
	{
		this->mMethodPtr = nullptr;
	}

	R operator()(ParamTypes... args) const
	{
		return (*this->mMethodPtr)(this->mBound, args...);
	}

	virtual bool operator == (const MySimpleDelegateInstanceBase &other) const override
	{
		const MySimpleClosureDelegateInstance& rhv = (MySimpleClosureDelegateInstance&)other;

		return ((this->mMethodPtr == rhv.mMethodPtr) &&
			    (this->mBound == rhv.mBound));
	}

	virtual bool operator!= (const MySimpleDelegateInstanceBase& other) const override
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

template <typename T>
class MyMiniClosureDelegateInstance2;

template <typename T, typename R, typename B1, typename B2, typename... ParamTypes>
class MyMiniClosureDelegateInstance2<R (T::*)(B1, B2, ParamTypes...)> : public MySimpleDelegateInstanceBase<R, ParamTypes...>
{
public:
    typedef R (T::*MethodPtrType)(B1, B2, ParamTypes...);

public:
	MyMiniClosureDelegateInstance2(MethodPtrType func, T* callee, B1 bound1, B2 bound2)
        : mUserObject(callee)
        , mMethodPtr(func)
        , mBound(bound1)
        , mBound2(bound2)
    {
    }

	virtual bool empty() const override
	{
		return (!this->mUserObject || !this->mMethodPtr);
	}

	virtual void clear() override
	{
		this->mUserObject = nullptr;
		this->mMethodPtr = nullptr;
	}

    R operator()(ParamTypes... args) const
    {
        return (this->mUserObject->*this->mMethodPtr)(mBound, mBound2, args...);
    }

    bool operator==(const MyMiniClosureDelegateInstance2 &other) const
    {
        return ((this->mUserObject == other.mUserObject) && 
			    (this->mMethodPtr == other.mMethodPtr) &&
                (this->mBound == other.mBound) && 
			    (this->mBound2 == other.mBound2));
    }

private:
    T *mUserObject;
    MethodPtrType mMethodPtr;
    B1 mBound;
    B2 mBound2;
};

template <typename T, typename R, typename B1, typename B2, typename... ParamTypes>
class MyMiniClosureDelegateInstance2<R (T::*)(B1, B2, ParamTypes...) const> : public MySimpleDelegateInstanceBase<R, ParamTypes...>
{
public:
	typedef R (T::*MethodPtrType)(B1, B2, ParamTypes...) const;

public:
	MyMiniClosureDelegateInstance2(MethodPtrType func, T* callee, B1 bound1, B2 bound2)
		: mUserObject(callee)
		, mMethodPtr(func)
		, mBound(bound1)
		, mBound2(bound2)
	{

	}

	virtual bool empty() const override
	{
		return (!this->mUserObject || !this->mMethodPtr);
	}

	virtual void clear() override
	{
		this->mUserObject = nullptr;
		this->mMethodPtr = nullptr;
	}

	R operator()(ParamTypes... args) const
	{
		return (this->mUserObject->*this->mMethodPtr)(mBound, mBound2, args...);
	}

	bool operator==(const MyMiniClosureDelegateInstance2 &other) const
	{
		return ((this->mUserObject == other.mUserObject) && 
			    (this->mMethodPtr == other.mMethodPtr) &&
			    (this->mBound == other.mBound) && 
			    (this->mBound2 == other.mBound2));
	}

private:
	const T *mUserObject;
	MethodPtrType mMethodPtr;
	B1 mBound;
	B2 mBound2;
};

template <typename R, typename B1, typename B2, typename... ParamTypes>
class MyMiniClosureDelegateInstance2<R(*)(B1, B2, ParamTypes...)> : public MySimpleDelegateInstanceBase<R, ParamTypes...>
{
public:
	typedef R(*MethodPtrType)(B1, B2, ParamTypes...);

public:
	MyMiniClosureDelegateInstance2(MethodPtrType func, B1 bound1, B2 bound2)
		: mMethodPtr(func)
		, mBound(bound1)
		, mBound2(bound2)
	{
	}

	virtual bool empty() const override
	{
		return (!this->mMethodPtr);
	}

	virtual void clear() override
	{
		this->mMethodPtr = nullptr;
	}

	R operator()(ParamTypes... args) const
	{
		return (*this->mMethodPtr)(this->mBound, this->mBound2, args...);
	}

	bool operator==(const MyMiniClosureDelegateInstance2 &other) const
	{
		return ((this->mMethodPtr == other.mMethodPtr) &&
			    (this->mBound == other.mBound) && 
			    (this->mBound2 == other.mBound2));
	}

private:
	MethodPtrType mMethodPtr;
	B1 mBound;
	B2 mBound2;
};

template <typename F, typename T, typename B>
MySimpleClosureDelegateInstance<F>* makeClosure(F func, T* obj, B b)
{
    return new MySimpleClosureDelegateInstance<F>(func, obj, b);
}

template <typename F, typename B>
MySimpleClosureDelegateInstance<F>* makeClosure(F func, B b)
{
	return new MySimpleClosureDelegateInstance<F>(func, b);
}

template <typename F, typename T, typename B1, typename B2>
MyMiniClosureDelegateInstance2<F>* makeClosure2(F func, T* obj, B1 b1, B2 b2)
{
    return new MyMiniClosureDelegateInstance2<F>(func, obj, b1, b2);
}

template <typename F, typename B1, typename B2>
MyMiniClosureDelegateInstance2<F>* makeClosure2(F func, B1 b1, B2 b2)
{
	return new MyMiniClosureDelegateInstance2<F>(func, b1, b2);
}

template <typename F, typename T, typename B>
MySimpleClosureDelegateInstance<F>* makeDelegate(F func, T* obj, B b)
{
	return makeClosure(func, obj, b);
}

template <typename F, typename B>
MySimpleClosureDelegateInstance<F>* makeDelegate(F func, B b)
{
	return makeClosure(func, b);
}

template <typename F, typename T, typename B1, typename B2>
MyMiniClosureDelegateInstance2<F>* makeDelegate(F func, T* obj, B1 b1, B2 b2)
{
	return new makeClosure2(func, obj, b1, b2);
}

template <typename F, typename B1, typename B2>
MyMiniClosureDelegateInstance2<F>* makeDelegate(F func, B1 b1, B2 b2)
{
	return new makeClosure2(func, b1, b2);
}

}

#endif