#ifndef __MyMiniClosureDelegateInstanceImpl_H
#define __MyMiniClosureDelegateInstanceImpl_H

#include "MyMiniDelegateInstanceBase.h"

namespace MyNS
{

// 函数指针泛化
template <typename T>
class MyMiniClosureDelegateInstanceImpl;

// 函数指针特化
// 无法推断，可变模板参数要放在最后
//template <typename T, typename R, typename... ParamTypes, typename B>
//class MyMiniClosureDelegateInstanceImpl<R (T::*)(ParamTypes..., B)> : public MyMiniDelegateInstanceBase<R, ParamTypes...>
template <typename T, typename R, typename B, typename... ParamTypes>
class MyMiniClosureDelegateInstanceImpl<R(T::*)(B, ParamTypes...)> : public MyMiniDelegateInstanceBase<R, ParamTypes...>
{
public:
    typedef R (T::*func_type)(B, ParamTypes...);

	MyMiniClosureDelegateInstanceImpl(func_type func, T &callee, B bound)
        : callee_(&callee)
        , func_(func)
        , bound_(bound)
    {
    }

    R operator()(ParamTypes... args) const
    {
        return (callee_->*func_)(bound_, args...);
    }

    bool operator==(const MyMiniClosureDelegateInstanceImpl &other) const
    {
        return (callee_ == other.callee_) && (func_ == other.func_) &&
               (bound_ == other.bound_);
    }

	virtual RetValType call(ParamTypes... Params) const override
	{
		return this->operator()(Params...);
	}

private:
    T *callee_;
    func_type func_;
    B bound_;
};

template <typename T>
class MyMiniClosureDelegateInstanceImpl2;

template <typename T, typename R, typename B1, typename B2, typename... ParamTypes>
class MyMiniClosureDelegateInstanceImpl2<R (T::*)(B1, B2, ParamTypes...)> : public MyMiniDelegateInstanceBase<R, ParamTypes...>
{
public:
    typedef R (T::*func_type)(B1, B2, ParamTypes...);

	MyMiniClosureDelegateInstanceImpl2(func_type func, T &callee, B1 bound1, B2 bound2)
        : callee_(&callee)
        , func_(func)
        , bound_(bound1)
        , bound2_(bound2)
    {
    }

    R operator()(ParamTypes... args) const
    {
        return (callee_->*func_)(bound_, bound2_, args...);
    }

    bool operator==(const MyMiniClosureDelegateInstanceImpl2 &other) const
    {
        return (callee_ == other.callee_) && (func_ == other.func_) &&
               (bound_ == other.bound_) && (bound2_ == other.bound2_);
    }

private:
    T *callee_;
    func_type func_;
    B1 bound_;
    B2 bound2_;
};

template <typename F, typename T, typename B>
MyMiniClosureDelegateInstanceImpl<F>* make_closure(F func, T &obj, B b)
{
    return new MyMiniClosureDelegateInstanceImpl<F>(func, obj, b);
}

template <typename F, typename T, typename B1, typename B2>
MyMiniClosureDelegateInstanceImpl2<F>* make_closure2(F func, T &obj, B1 b1, B2 b2)
{
    return new MyMiniClosureDelegateInstanceImpl2<F>(func, obj, b1, b2);
}

template <typename F, typename T, typename B>
MyMiniClosureDelegateInstanceImpl<F>* make_delegate(F func, T &obj, B b)
{
	return make_closure(func, obj, b);
}

template <typename F, typename T, typename B1, typename B2>
MyMiniClosureDelegateInstanceImpl2<F>* make_delegate(F func, T &obj, B1 b1, B2 b2)
{
	return new make_closure2(func, obj, b1, b2);
}

}

#endif
