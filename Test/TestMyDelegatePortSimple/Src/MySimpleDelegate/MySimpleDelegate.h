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
		// const ������ֻ�ܵ��� const �ӿ�
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

	// ģ���Զ��ƶ� const ֵ
	// R (T::*)(ParamTypes...) �����ᱨ��
	// error C2146: syntax error: missing ')' before identifier 'func'
	template <typename UserClass, typename... VarTypes>
	void bindObjectHandle(typename MySimpleMemFunPtrType<false, UserClass, RetValType(VarTypes..., ParamTypes...)>::Type func, UserClass* callee, VarTypes... vars)
	{
		this->mMyMiniDelegateInstance = makeDelegate(func, callee, vars...);
	}

	// ģ���Զ��ƶ� const ֵ
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
