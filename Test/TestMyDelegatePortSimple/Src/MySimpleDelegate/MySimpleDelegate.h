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
		// const ������ֻ�ܵ��� const �ӿ�
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

	// ʹ�ú���
	template <typename UserClass>
	MySimpleDelegate& bindObjectHandle(typename MySimpleMemFunPtrType<false, UserClass, RetValType(ParamTypes...)>::Type func, UserClass* callee)
	{
		this->mMyMiniDelegateInstance = makeDelegate(func, callee);
		return *(this);
	}

	// ʹ�ú���
	template <typename UserClass>
	MySimpleDelegate& bindObjectHandle(typename MySimpleMemFunPtrType<true, UserClass, RetValType(ParamTypes...)>::Type func, UserClass* callee)
	{
		this->mMyMiniDelegateInstance = makeDelegate(func, callee);
		return *(this);
	}

	// ʹ�ñհ�
	// ģ���Զ��ƶ� const ֵ
	// R (T::*)(ParamTypes...) �����ᱨ��
	// error C2146: syntax error: missing ')' before identifier 'func'
	template <typename UserClass, typename... VarTypes>
	MySimpleDelegate& bindObjectHandle(typename MySimpleMemFunPtrType<false, UserClass, RetValType(VarTypes..., ParamTypes...)>::Type func, UserClass* callee, VarTypes... vars)
	{
		this->mMyMiniDelegateInstance = makeDelegate(func, callee, vars...);
		return *(this);
	}

	// ʹ�ñհ�
	// ģ���Զ��ƶ� const ֵ
	template <typename UserClass, typename... VarTypes>
	MySimpleDelegate& bindObjectHandle(typename MySimpleMemFunPtrType<true, UserClass, RetValType(VarTypes..., ParamTypes...)>::Type func, UserClass* callee, VarTypes... vars)
	{
		this->mMyMiniDelegateInstance = makeDelegate(func, callee, vars...);
		return *(this);
	}

	// ʹ�ú���
	MySimpleDelegate& bindStaticHandle(MethodPtrType func)
	{
		this->mMyMiniDelegateInstance = makeDelegate(func);
		return *(this);
	}

	// ʹ�ñհ�
	template <typename... VarTypes>
	MySimpleDelegate& bindStaticHandle(typename MySimpleStaticFunPtrType<RetValType(VarTypes..., ParamTypes...)>::Type func, VarTypes...)
	{
		this->mMyMiniDelegateInstance = makeDelegate(func, VarTypes...);
		return *(this);
	}
};

}

#endif
