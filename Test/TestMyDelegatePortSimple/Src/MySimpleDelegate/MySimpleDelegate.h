#ifndef __MyMiniDelegate_H
#define __MyMiniDelegate_H

#include "MySimpleDelegateBase.h"
#include "MySimpleMemFunPtrType.h"
#include "MySimpleStaticFunPtrType.h"
#include "MySimpleDelegateInstanceBase.h"
#include "MySimpleMethodDelegateInstance.h"
#include "MySimpleClosureDelegateInstance.h"

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

public:
	MySimpleDelegateInstanceBase<R, ParamTypes...>* mMyMiniDelegateInstance;

public:
	virtual bool empty() const override
	{
		return this->mMyMiniDelegateInstance->empty();
	}

	virtual void clear() override
	{

	}

	virtual bool equalTo(const MySimpleDelegate& other)
	{
		return this->mMyMiniDelegateInstance == other.mMyMiniDelegateInstance;
	}

	bool operator==(const MySimpleDelegate& other) const
	{
		return this->mMyMiniDelegateInstance == other.mMyMiniDelegateInstance;
	}

	bool operator!= (const MySimpleDelegate& other) const
	{
		return !((*this) == other);
	}

	virtual bool operator ! () const override
	{
		// const 函数中只能调用 const 接口
		return this->empty();
	}

	RetValType operator () (ParamTypes... Params) const
	{
		return this->mMyMiniDelegateInstance->call(Params...);
	}

	RetValType call(ParamTypes... Params) const
	{
		return this->mMyMiniDelegateInstance->call(Params...);
	}

	// 使用函数
	template <typename UserClass>
	MySimpleDelegate& bindObjectHandle(typename MySimpleMemFunPtrType<false, UserClass, RetValType(ParamTypes...)>::Type func, UserClass* callee)
	{
		this->mMyMiniDelegateInstance = makeDelegate(func, callee);
		return *(this);
	}

	// 使用函数
	template <typename UserClass>
	MySimpleDelegate& bindObjectHandle(typename MySimpleMemFunPtrType<true, UserClass, RetValType(ParamTypes...)>::Type func, UserClass* callee)
	{
		this->mMyMiniDelegateInstance = makeDelegate(func, callee);
		return *(this);
	}

	// 使用闭包
	// 模板自动推断 const 值
	// R (T::*)(ParamTypes...) 参数会报错
	// error C2146: syntax error: missing ')' before identifier 'func'
	template <typename UserClass, typename... VarTypes>
	MySimpleDelegate& bindObjectHandle(typename MySimpleMemFunPtrType<false, UserClass, RetValType(VarTypes..., ParamTypes...)>::Type func, UserClass* callee, VarTypes... vars)
	{
		this->mMyMiniDelegateInstance = makeDelegate(func, callee, vars...);
		return *(this);
	}

	// 使用闭包
	// 模板自动推断 const 值
	template <typename UserClass, typename... VarTypes>
	MySimpleDelegate& bindObjectHandle(typename MySimpleMemFunPtrType<true, UserClass, RetValType(VarTypes..., ParamTypes...)>::Type func, UserClass* callee, VarTypes... vars)
	{
		this->mMyMiniDelegateInstance = makeDelegate(func, callee, vars...);
		return *(this);
	}

	// 使用函数
	MySimpleDelegate& bindStaticHandle(MethodPtrType func)
	{
		this->mMyMiniDelegateInstance = makeDelegate(func);
		return *(this);
	}

	// 使用闭包
	template <typename... VarTypes>
	MySimpleDelegate& bindStaticHandle(typename MySimpleStaticFunPtrType<RetValType(VarTypes..., ParamTypes...)>::Type func, VarTypes...)
	{
		this->mMyMiniDelegateInstance = makeDelegate(func, VarTypes...);
		return *(this);
	}
};

}

#endif
