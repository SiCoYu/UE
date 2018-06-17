#ifndef __MyMiniDelegate_H
#define __MyMiniDelegate_H

#include "MyMiniDelegateBase.h"
#include "MyMiniDelegateInstanceBase.h"
#include "MyMiniMemFunPtrType.h"

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

	// R (T::*)(ParamTypes...) 参数会报错
	// error C2146: syntax error: missing ')' before identifier 'func'
	template <typename UserClass>
	void bindObjectHandle(typename MyMiniMemFunPtrType<false, UserClass, RetValType(ParamTypes...)>::Type func, UserClass& callee)
	{
		this->mMyMiniDelegateInstance = make_delegate(func, callee);
	}

	void bindStaticHandle(func_type func)
	{
		this->mMyMiniDelegateInstance = make_delegate(func);
	}
};

} // namespace delegate

#endif /* end of include guard */
