#ifndef __MyMiniDelegateInstanceBase_H
#define __MyMiniDelegateInstanceBase_H

namespace MyNS
{
template <typename R, typename... ParamTypes>
class MyMiniDelegateInstanceBase
{
public:
	typedef R RetValType;

public:
	// 为了支持返回值是 void ，需要设置成纯虚函数
	virtual RetValType call(ParamTypes... Params) const = 0;
	//{
	//	return *((RetValType*)0);
	//}
};
}

#endif
