#include "MyProject.h"
#include "LoopDepth.h"
#include "AddOnceEventDispatch.h"
#include "MyMemoryConstructorFlag.h"
#include "MyMemoryAllocatorConfig.h"

MY_BEGIN_NAMESPACE(MyNS)

LoopDepth::LoopDepth()
{
	this->mLoopDepth = 0;
}

void LoopDepth::init()
{

}

void LoopDepth::dispose()
{
	if (nullptr != this->mIncHandle)
	{
		this->mIncHandle->clearEventHandle();
		MY_DELETE this->mIncHandle;
		this->mIncHandle = nullptr;
	}
	if (nullptr != this->mDecHandle)
	{
		this->mDecHandle->clearEventHandle();
		MY_DELETE this->mDecHandle;
		this->mDecHandle = nullptr;
	}
	if (nullptr != this->mZeroHandle)
	{
		this->mZeroHandle->clearEventHandle();
		MY_DELETE this->mZeroHandle;
		this->mZeroHandle = nullptr;
	}
}

void LoopDepth::setIncHandle(EventDispatchDelegate handle)
{
	if (nullptr == this->mIncHandle)
	{
		this->mIncHandle = MY_NEW AddOnceEventDispatch();
	}

	this->mIncHandle.addEventHandle(handle);
}

void LoopDepth::setDecHandle(EventDispatchDelegate handle)
{
	if (nullptr == this->mDecHandle)
	{
		this->mDecHandle = MY_NEW AddOnceEventDispatch();
	}

	this->mDecHandle.addEventHandle(handle);
}

void LoopDepth::setZeroHandle(EventDispatchDelegate handle)
{
	if (nullptr == this->mZeroHandle)
	{
		this->mZeroHandle = MY_NEW AddOnceEventDispatch();
	}

	this->mZeroHandle->addEventHandle(handle);
}

void LoopDepth::_incDepth()
{
	++this->mLoopDepth;

	if (nullptr != this->mIncHandle)
	{
		this->mIncHandle->dispatchEvent(nullptr);
	}
}

void LoopDepth::_decDepth()
{
	--this->mLoopDepth;

	if (nullptr != this->mDecHandle)
	{
		this->mDecHandle->dispatchEvent(nullptr);
	}

	if (0 == this->mLoopDepth)
	{
		if (nullptr != this->mZeroHandle)
		{
			this->mZeroHandle->dispatchEvent(nullptr);
		}
	}

	if (this->mLoopDepth < 0)
	{
		this->mLoopDepth = 0;
		// 错误，不对称
		//LogError("LoopDepth::_decDepth, Error !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
	}
}

bool LoopDepth::_isInDepth()
{
	return this->mLoopDepth > 0;
}

MY_END_NAMESPACE