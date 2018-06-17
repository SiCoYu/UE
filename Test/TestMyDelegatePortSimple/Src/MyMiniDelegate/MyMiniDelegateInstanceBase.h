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
	virtual RetValType call(ParamTypes... Params) const
	{
		return *((RetValType*)0);
	}
};
} // namespace delegate

#endif /* end of include guard */
