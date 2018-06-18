#ifndef __MyMiniDelegate_H
#define __MyMiniDelegate_H

#include "MySimpleDelegateBase.h"
#include "MySimpleMemFunPtrType.h"
#include "MySimpleDelegateInstanceBase.h"
#include "MySimpleMethodDelegateInstanceImpl.h"
#include "MySimpleClosureDelegateInstanceImpl.h"

namespace MyNS
{
// error C2243: 'type cast': conversion from 'MyNS::MySimpleDelegate<bool,int,char> *' to 'MyNS::MySimpleDelegateBase *' exists, but is inaccessible
//class MySimpleDelegate : MySimpleDelegateBase
template <typename R, typename... ParamTypes>
class MySimpleDelegate : public MySimpleDelegateBase
{
public:
	typedef R RetValType;
	typedef R (*MethodPtrType) (ParamTypes...);

protected:
	MySimpleDelegateInstanceBase<R, ParamTypes...>* mMyMiniDelegateInstance;

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
	void bindObjectHandle(typename MySimpleMemFunPtrType<false, UserClass, RetValType(ParamTypes...)>::Type func, UserClass* callee)
	{
		this->mMyMiniDelegateInstance = makeDelegate(func, callee);
	}

	template <typename UserClass>
	void bindObjectHandle(typename MySimpleMemFunPtrType<true, UserClass, RetValType(ParamTypes...)>::Type func, UserClass* callee)
	{
		this->mMyMiniDelegateInstance = makeDelegate(func, callee);
	}

	// 模板自动推断 const 值
	// R (T::*)(ParamTypes...) 参数会报错
	// error C2146: syntax error: missing ')' before identifier 'func'
	template <typename UserClass, typename... VarTypes>
	void bindObjectHandle(typename MySimpleMemFunPtrType<false, UserClass, RetValType(VarTypes..., ParamTypes...)>::Type func, UserClass* callee, VarTypes... vars)
	{
		this->mMyMiniDelegateInstance = makeDelegate(func, callee, vars...);
	}

	// 模板自动推断 const 值
	template <typename UserClass, typename... VarTypes>
	void bindObjectHandle(typename MySimpleMemFunPtrType<true, UserClass, RetValType(VarTypes..., ParamTypes...)>::Type func, UserClass* callee, VarTypes... vars)
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
