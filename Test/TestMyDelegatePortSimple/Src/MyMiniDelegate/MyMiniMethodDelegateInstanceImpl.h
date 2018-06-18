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
    typedef R (T::*func_type)(ParamTypes...);

	MyMiniMethodDelegateInstanceImpl(func_type func, T* callee)
        : callee_(callee)
        , func_(func)
    {}

    R operator()(ParamTypes... args) const
    {
        return (callee_->*func_)(args...);
    }

    bool operator==(const MyMiniMethodDelegateInstanceImpl& other) const
    {
        return (&callee_ == &other.callee_) && (func_ == other.func_);
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
    T* callee_;
    func_type func_;
};

template <typename T, typename R, typename... ParamTypes>
class MyMiniMethodDelegateInstanceImpl<R (T::*)(ParamTypes...) const> : public MyMiniDelegateInstanceBase<R, ParamTypes...>
{
public:
    typedef R (T::*func_type)(ParamTypes...) const;

	MyMiniMethodDelegateInstanceImpl(func_type func, const T* callee)
        : callee_(callee)
        , func_(func)
    {}

    R operator()(ParamTypes... args) const
    {
        return (callee_->*func_)(args...);
    }

    bool operator==(const MyMiniMethodDelegateInstanceImpl& other) const
    {
        return (&callee_ == &other.callee_) && (func_ == other.func_);
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
    const T* callee_;
    func_type func_;
};

/**
 * @brief �ǳ�Ա����û�� const ƫ�ػ�
 */
template <typename R, typename... ParamTypes>
class MyMiniMethodDelegateInstanceImpl<R (*)(ParamTypes...)> : public MyMiniDelegateInstanceBase<R, ParamTypes...>
{
public:
    typedef R (*func_type)(ParamTypes...);

	MyMiniMethodDelegateInstanceImpl(func_type func)
        : func_(func)
    {}

    R operator()(ParamTypes... args) const
    {
        return (*func_)(args...);
    }

    bool operator==(const MyMiniMethodDelegateInstanceImpl& other) const
    {
        return func_ == other.func_;
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
    func_type func_;
};

template <typename F, typename T>
MyMiniMethodDelegateInstanceImpl<F>* make_delegate(F func, T& obj)
{
    return new MyMiniMethodDelegateInstanceImpl<F>(func, obj);
}

template <typename T>
MyMiniMethodDelegateInstanceImpl<T>* make_delegate(T func)
{
    return new MyMiniMethodDelegateInstanceImpl<T>(func);
}

}

#endif
