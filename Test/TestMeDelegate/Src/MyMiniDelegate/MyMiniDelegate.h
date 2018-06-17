#ifndef __MyMiniDelegate_H
#define __MyMiniDelegate_H

#include "MyMiniDelegateBase.h"
#include "MyMiniDelegateInstanceBase.h"

namespace MyNS
{
template <typename R, typename... Params>
class MyMiniDelegate : MyMiniDelegateBase
{
	typedef R(*func_type)(Params...);

protected:
	MyMiniDelegateInstanceBase* mMyMiniDelegateInstance;

public:
	//template <typename T>
	//void bindObjectHandle(R (T::*)(Params...) func, T& callee)
	//{
	//	this->mMyMiniDelegateInstance = make_delegate(func, callee);
	//}

	void bindStaticHandle(func_type func)
	{
		this->mMyMiniDelegateInstance = make_delegate(func);
	}
};

} // namespace delegate

#endif /* end of include guard */
