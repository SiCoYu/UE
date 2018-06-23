#include "MyProject.h"
#include "MMouseDevice.h"
#include "Ctx.h"
#include "InputMgr.h"

MY_BEGIN_NAMESPACE(MyNS)

MMouseDevice* MMouseDevice::MouseLeftButton = MY_NEW MMouseDevice(0);
MMouseDevice* MMouseDevice::MouseRightButton = MY_NEW MMouseDevice(1);
MMouseDevice* MMouseDevice::MouseMiddleButton = MY_NEW MMouseDevice(2);

MMouseDevice* MMouseDevice::mMouse[MMouseDeviceType::eMouseTotalButton];

MMouseDevice* MMouseDevice::GetMouse(int button)
{
	if (nullptr == MMouseDevice::mMouse[0])
	{
		MMouseDevice::mMouse[0] = MMouseDevice::MouseLeftButton;
		MMouseDevice::mMouse[1] = MMouseDevice::MouseRightButton;
		MMouseDevice::mMouse[2] = MMouseDevice::MouseMiddleButton;
	}

	return MMouseDevice::mMouse[button];
}

MMouseDevice::MMouseDevice(int button)
{
	this->mTouchIndex = button;
}

void MMouseDevice::onTick(float delta, TickMode tickMode)
{
	if (GInputMgr->GetMouseButtonDown(this->mTouchIndex))
	{
		this->mTouchBegan = true;
		this->mTouchEnd = false;

		// 按下的时候，设置位置相同
		this->mPos = GInputMgr->GetMousePosition(0);
		this->mLastPos = this->mPos;

		this->handleMouseDown();
	}
	else if (GInputMgr->GetMouseButtonUp(this->mTouchIndex))
	{
		this->mTouchBegan = false;
		this->mTouchEnd = true;

		// Up 的时候，先设置之前的位置，然后设置当前位置
		this->mLastPos = this->mPos;
		this->mPos = GInputMgr->GetMousePosition(0);

		this->handleMouseUp();
	}
	else if (GInputMgr->GetMouseButton(this->mTouchIndex))
	{
		this->mTouchBegan = false;
		this->mTouchEnd = false;

		// Press 的时候，先设置之前的位置，然后设置当前位置
		this->mLastPos = this->mPos;
		this->mPos = GInputMgr->GetMousePosition(0);

		if (this->isPosChanged())
		{
			this->handleMousePressMove();
		}
		else
		{
			this->handleMousePress();
		}
	}
	else if (this->isPosChanged())     // 位置不相等的时候，就是移动
	{
		this->mTouchBegan = false;
		this->mTouchEnd = false;

		// 鼠标移动
		this->mLastPos = this->mPos;
		this->mPos = GInputMgr->GetMousePosition();

		this->handleMousePressOrMove();
	}
}

void MMouseDevice::handleMouseDown()
{
	if (!GInputMgr->mSimulateMouseWithTouches)
	{
		GInputMgr->handleMouseDown(this);
	}
	else
	{
		GInputMgr->handleTouchBegan(this);
	}
}

void MMouseDevice::handleMouseUp()
{
	if (!GInputMgr->mSimulateMouseWithTouches)
	{
		GInputMgr->handleMouseUp(this);
	}
	else
	{
		GInputMgr->handleTouchEnded(this);
	}
}

void MMouseDevice::handleMousePress()
{
	if (!GInputMgr->mSimulateMouseWithTouches)
	{
		GInputMgr->handleMousePress(this);
	}
	else
	{
		GInputMgr->handleTouchStationary(this);
	}
}

void MMouseDevice::handleMousePressOrMove()
{
	if (this->isPosChanged())
	{
		GInputMgr->handleMousePressOrMove(this);
	}
}

void MMouseDevice::handleMousePressMove()
{
	if (this->isPosChanged())
	{
		if (!GInputMgr->mSimulateMouseWithTouches)
		{
			GInputMgr->handleMousePressMove(this);
		}
		else
		{
			GInputMgr->handleTouchMoved(this);
		}
	}
}

MY_END_NAMESPACE