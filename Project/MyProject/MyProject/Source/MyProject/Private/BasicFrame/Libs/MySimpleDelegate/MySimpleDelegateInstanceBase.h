#ifndef __MyMiniDelegateInstanceBase_H
#define __MyMiniDelegateInstanceBase_H

namespace MyNS
{
template <typename R, typename... ParamTypes>
class MySimpleDelegateInstanceBase
{
public:
	typedef R RetValType;

public:
	virtual bool empty() const
	{
		return true;
	}

	virtual void clear()
	{

	}

	virtual bool operator==(const MySimpleDelegateInstanceBase& other) const
	{
		return false;
	}

	virtual bool operator!= (const MySimpleDelegateInstanceBase& other) const
	{
		return !((*this) == other);
	}

	// Ϊ��֧�ַ���ֵ�� void ����Ҫ���óɴ��麯��
	virtual RetValType call(ParamTypes... Params) const = 0;
	//{
	//	return *((RetValType*)0);
	//}
};
}

#endif
