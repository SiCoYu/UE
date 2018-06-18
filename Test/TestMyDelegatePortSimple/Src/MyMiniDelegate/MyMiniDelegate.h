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
	typedef R (*func_type) (ParamTypes...);

protected:
	MyMiniDelegateInstanceBase<R, ParamTypes...>* mMyMiniDelegateInstance;

public:
	RetValType call(ParamTypes... Params) const
	{
		return this->mMyMiniDelegateInstance->call(Params...);
	}

	template <typename UserClass>
	void bindObjectHandle(typename MyMiniMemFunPtrType<false, UserClass, RetValType(ParamTypes...)>::Type func, UserClass* callee)
	{
		this->mMyMiniDelegateInstance = make_delegate(func, callee);
	}

	template <typename UserClass>
	void bindObjectHandle(typename MyMiniMemFunPtrType<true, UserClass, RetValType(ParamTypes...)>::Type func, UserClass* callee)
	{
		this->mMyMiniDelegateInstance = make_delegate(func, callee);
	}

	// 模板自动推断 const 值
	// R (T::*)(ParamTypes...) 参数会报错
	// error C2146: syntax error: missing ')' before identifier 'func'
	template <typename UserClass, typename... VarTypes>
	void bindObjectHandle(typename MyMiniMemFunPtrType<false, UserClass, RetValType(VarTypes..., ParamTypes...)>::Type func, UserClass* callee, VarTypes... vars)
	{
		this->mMyMiniDelegateInstance = make_delegate(func, callee, vars...);
	}

	// 模板自动推断 const 值
	template <typename UserClass, typename... VarTypes>
	void bindObjectHandle(typename MyMiniMemFunPtrType<true, UserClass, RetValType(VarTypes..., ParamTypes...)>::Type func, UserClass* callee, VarTypes... vars)
	{
		this->mMyMiniDelegateInstance = make_delegate(func, callee, vars...);
	}

	//template <typename... VarTypes>
	//void bindStaticHandle(func_type func, VarTypes...)
	//{
	//	this->mMyMiniDelegateInstance = make_delegate(func, VarTypes...);
	//}

	void bindStaticHandle(func_type func)
	{
		this->mMyMiniDelegateInstance = make_delegate(func);
	}
};

} // namespace delegate

#endif /* end of include guard */
