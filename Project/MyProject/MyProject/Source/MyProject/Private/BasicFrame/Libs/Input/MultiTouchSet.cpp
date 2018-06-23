#include "MyProject.h"
#include "MultiTouchSet.h"
#include "IDispatchObject.h"
#include "MMouseOrTouch.h"
#include "Ctx.h"
#include "InputMgr.h"

MY_BEGIN_NAMESPACE(MyNS)

MultiTouchSet::MultiTouchSet()
{
	
}

void MultiTouchSet::init()
{

}

void MultiTouchSet::dispose()
{

}

void MultiTouchSet::reset()
{
	this->mTouchList.clear();
}

void MultiTouchSet::addTouch(MMouseOrTouch* touch)
{
	this->mTouchList.add(touch);
}

void MultiTouchSet::onTick(float delta, TickMode tickMode)
{
	bool isTouchBegan = false;
	bool isMove = false;
	bool isStationary = false;
	bool isEnd = false;

	MMouseOrTouch* touch = nullptr;

	int index = 0;
	int len = this->mTouchList.count();

	while (index < len)
	{
		touch = this->mTouchList[index];

		if (touch->mTouchBegan)
		{
			isTouchBegan = true;
		}
		else if (touch->mTouchEnd)
		{
			isEnd = true;
		}
		else if (touch->isPosChanged())
		{
			isMove = true;
			break;
		}
		else
		{
			isStationary = true;
		}

		++index;
	}

	// 暂时只支持多触碰移动
	if (isMove)
	{
		GInputMgr->handleMultiTouchMoved(this);
	}
}

MY_END_NAMESPACE