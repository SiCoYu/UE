#ifndef __MyMiniDelegateBase_H
#define __MyMiniDelegateBase_H

namespace MyNS
{
class MySimpleDelegateBase
{
public:
	MySimpleDelegateBase()
	{

	}

	virtual ~MySimpleDelegateBase()
	{

	}

	virtual bool empty() const
	{
		return true;
	}

	virtual void clear()
	{
		
	}

	virtual bool operator ! () const
	{
		return true;
	}
};
}

#endif
