#ifndef __MyMiniDelegate_H
#define __MyMiniDelegate_H

#include "MyMiniDelegateBase.h"
#include "MyMiniMemFunPtrType.h"
#include "MyMiniDelegateInstanceBase.h"
#include "MyMiniMethodDelegateInstanceImpl.h"
#include "MyMiniClosureDelegateInstanceImpl.h"

namespace MyNS
{
// error C2243: 'type cast': conversion from 'MyNS::MyMiniDelegate<bool,int,char> *' to 'MyNS::MyMiniDelegateBase *' exists, but is inaccessible
//class MyMiniDelegate : MyMiniDelegateBase
template <typename R, typename... ParamTypes>
class MyMiniDelegate : public MyMiniDelegateBase
{
public:
	typedef R RetValType;
	typedef R (*MethodPtrType) (ParamTypes...);

protected:
	MyMiniDelegateInstanceBase<R, ParamTypes...>* mMyMiniDelegateInstance;

public:
	virtual bool empty() const override
	{
		return this->mMyMiniDelegateInstance->empty();
	}

	virtual void clear() override
	{

	}

	virtual bool operator ! () const override
	{
		// const 函数中只能调用 const 接口
		return this->empty();
	}

	RetValType call(ParamTypes... Params) const
	{
		return this->mMyMiniDelegateInstance->call(Params...);
	}

	template <typename UserClass>
	void bindObjectHandle(typename MyMiniMemFunPtrType<false, UserClass, RetValType(ParamTypes...)>::Type func, UserClass* callee)
	{
		this->mMyMiniDelegateInstance = makeDelegate(func, callee);
	}

	template <typename UserClass>
	void bindObjectHandle(typename MyMiniMemFunPtrType<true, UserClass, RetValType(ParamTypes...)>::Type func, UserClass* callee)
	{
		this->mMyMiniDelegateInstance = makeDelegate(func, callee);
	}

	// 模板自动推断 const 值
	// R (T::*)(ParamTypes...) 参数会报错
	// error C2146: syntax error: missing ')' before identifier 'func'
	template <typename UserClass, typename... VarTypes>
	void bindObjectHandle(typename MyMiniMemFunPtrType<false, UserClass, RetValType(VarTypes..., ParamTypes...)>::Type func, UserClass* callee, VarTypes... vars)
	{
		this->mMyMiniDelegateInstance = makeDelegate(func, callee, vars...);
	}

	// 模板自动推断 const 值
	template <typename UserClass, typename... VarTypes>
	void bindObjectHandle(typename MyMiniMemFunPtrType<true, UserClass, RetValType(VarTypes..., ParamTypes...)>::Type func, UserClass* callee, VarTypes... vars)
	{
		this->mMyMiniDelegateInstance = makeDelegate(func, callee, vars...);
	}

	//template <typename... VarTypes>
	//void bindStaticHandle(MethodPtrType func, VarTypes...)
	//{
	//	this->mMyMiniDelegateInstance = makeDelegate(func, VarTypes...);
	//}

	void bindStaticHandle(MethodPtrType func)
	{
		this->mMyMiniDelegateInstance = makeDelegate(func);
	}
};

}

#endif
