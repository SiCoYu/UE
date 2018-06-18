#ifndef __MyMiniDelegateBase_H
#define __MyMiniDelegateBase_H

namespace MyNS
{
class MyMiniDelegateBase
{
public:
	MyMiniDelegateBase()
	{

	}

	virtual ~MyMiniDelegateBase()
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
