#ifndef __InputMgr_H
#define __InputMgr_H

#include <string>

#include "MList.h"
#include "GObject.h"
#include "ITickedObject.h"
#include "INoOrPriorityObject.h"
#include "KeyId.h"
#include "InputEventId.h"
#include "EventDispatchDelegate.h"
#include "PlatformDefine.h"

class AMyPlayerControllerBase;
class UPlayerInput;
struct FKey;

MY_BEGIN_NAMESPACE(MyNS)

class InputKey;
class MMouseDevice;
class MTouchDevice;
class AddOnceEventDispatch;
class MultiTouchSet;

/**
 * @brief 主要是场景消息处理， UI 消息单独走，这个主要是从硬件判断
 * @error InputMgr 的 Tick 一定不能放在 FixedUpdate 里面，会经常检测不到
 */
class InputMgr : public GObject, public ITickedObject, public INoOrPriorityObject
{
protected:
	AMyPlayerControllerBase* mPlayerController;

	// GameFramework/PlayerInput.h
	// UCLASS(Within = PlayerController, config = Input, transient)
	// class ENGINE_API UPlayerInput : public UObject
	UPlayerInput* mPlayerInput;

	// 有监听事件的键盘 InputKey
	MList<InputKey*> mEventInputKeyList;
	// 有监听事件的鼠标 MMouse
	MList<MMouseDevice*> mEventMouseList;
	// 是否有重力感应事件
	bool mHasAccelerationHandle;

	MControlScheme mCurrentScheme;
	int mCurrentTouchId;
	MTouchDevice* mCurrentTouch;

	bool mHasTouch;
	bool mHasMultiTouch;

	// 单触碰
	AddOnceEventDispatch* mOnTouchBeganDispatch;         // 触碰开始
	AddOnceEventDispatch* mOnTouchMovedDispatch;         // 触碰状态，但是移动
	AddOnceEventDispatch* mOnTouchStationaryDispatch;    // 触碰状态但是不移动
	AddOnceEventDispatch* mOnTouchEndedDispatch;         // 触碰结束
	AddOnceEventDispatch* mOnTouchCanceledDispatch;      // 触碰取消
															// 多触碰
	AddOnceEventDispatch* mOnMultiTouchBeganDispatch;         // 触碰开始
	AddOnceEventDispatch* mOnMultiTouchMovedDispatch;         // 触碰状态，但是移动
	AddOnceEventDispatch* mOnMultiTouchStationaryDispatch;    // 触碰状态但是不移动
	AddOnceEventDispatch* mOnMultiTouchEndedDispatch;         // 触碰结束
	AddOnceEventDispatch* mOnMultiTouchCanceledDispatch;      // 触碰取消

	AddOnceEventDispatch* mOnDeviceOpDispatch;      // android返回按键操作
	AddOnceEventDispatch* mOnDeviceHomeDispatch;      // androidHome按键操作

															// 多触碰集合
	MultiTouchSet* mMultiTouchSet;
	// 鼠标模拟触碰
	bool mMultiTouchEnabled;
	bool mSimulateMouseWithTouches;
	bool mTouchSupported;

	// 鼠标
	MMouseDispatch* mMouseDispatchArray[3];

public:
	InputMgr();
	~InputMgr();

	void init();
	void dispose();

	void setPlayerController(AMyPlayerControllerBase* value);
	void setPlayerInput(UPlayerInput* value);

	// 原生事件处理
	bool getKeyDown(FKey keyCode);
	bool getKeyUp(FKey keyCode);
	bool getKey(FKey keyCode);

	// 逻辑事件处理
	/**
	* @inheritDoc
	*/
	void onTick(float delta, TickMode tickMode)
	{
		int index = 0;

		for (index = 0; index < this->mEventInputKeyList.count(); index++)
		{
			this->mEventInputKeyList[index]->onTick(delta, tickMode);
		}

		for (index = 0; index < this->mEventMouseList.count(); index++)
		{
			this->mEventMouseList[index]->onTick(delta, tickMode);
		}

		this->ProcessTouches(delta, tickMode);

		if (this->mHasAccelerationHandle)
		{
			MAcceleration::mAccelerationOne->onTick(delta, tickMode);
		}
	}

	bool keyJustPressed(InputKey* inputKey)
	{
		return inputKey->keyJustPressed();
	}

	bool keyJustReleased(InputKey* inputKey)
	{
		return inputKey->keyJustReleased();
	}

	bool isKeyDown(InputKey* inputKey)
	{
		return inputKey->isKeyDown();
	}

	bool isAnyKeyDown()
	{
		int index = 0;
		int listLen = (int)KeyId::Total;
		InputKey* inputKey = nullptr;
		bool ret = false;

		while(index < listLen)
		{
			inputKey = InputKey::mInputKeyArray[index];

			if (nullptr != inputKey)
			{
				ret = inputKey->mKeyState;
				break;
			}

			index += 1;
		}

		return ret;
	}

	// 添加 KeyInput 输入事件
	void addKeyListener(InputKey* inputKey, InputEventId evtId, EventDispatchDelegate handle)
	{
		inputKey->addKeyListener(evtId, handle);

		this->addEventInputKey(inputKey);
	}

	// 移除键盘 KeyInput 输入事件
	void removeKeyListener(InputKey* inputKey, InputEventId evtId, EventDispatchDelegate handle)
	{
		inputKey->removeKeyListener(evtId, handle);

		if (!inputKey->hasEventHandle())
		{
			this->removeEventInputKey(inputKey);
		}
	}

	// 添加鼠标监听器
	void addMouseListener(MMouseDevice* mouse, InputEventId evtId, EventDispatchDelegate handle)
	{
		this->mMouseDispatchArray[mouse.mTouchIndex].addMouseListener(evtId, handle);
		this->addEventMouse(mouse);
	}

	// 移除鼠标监听器
	void removeMouseListener(MMouseDevice* mouse, InputEventId evtId, EventDispatchDelegate handle)
	{
		this->mMouseDispatchArray[mouse.mTouchIndex].removeMouseListener(evtId, handle);

		if (!this->hasEventHandle(mouse))
		{
			this->removeEventMouse(mouse);
		}
	}

	void addTouchListener(InputEventId evtId, EventDispatchDelegate handle)
	{
		if (InputEventId::TOUCHBEGIN_EVENT == evtId)
		{
			this->mOnTouchBeganDispatch->addEventHandle(nullptr, handle);
		}
		else if (InputEventId::TOUCHMOVED_EVENT == evtId)
		{
			this->mOnTouchMovedDispatch.addEventHandle(nullptr, handle);
		}
		else if (InputEventId::TOUCHSTATIONARY_EVENT == evtId)
		{
			this->mOnTouchStationaryDispatch.addEventHandle(nullptr, handle);
		}
		else if (InputEventId::TOUCHENDED_EVENT == evtId)
		{
			this->mOnTouchEndedDispatch->addEventHandle(nullptr, handle);
		}
		else if (InputEventId::TOUCHCANCELED_EVENT == evtId)
		{
			this->mOnTouchCanceledDispatch->addEventHandle(nullptr, handle);
		}

		this->mHasTouch = true;

		if (!this->mTouchSupported)
		{
			if (this->mSimulateMouseWithTouches)
			{
				this->addEventMouse(MMouseDevice::MouseLeftButton);
			}
		}
	}

	void removeTouchListener(InputEventId evtId, EventDispatchDelegate handle)
	{
		if (InputEventId::TOUCHBEGIN_EVENT == evtId)
		{
			this->mOnTouchBeganDispatch->removeEventHandle(nullptr, handle);
		}
		else if (InputEventId::TOUCHMOVED_EVENT == evtId)
		{
			this->mOnTouchMovedDispatch.removeEventHandle(nullptr, handle);
		}
		else if (InputEventId::TOUCHSTATIONARY_EVENT == evtId)
		{
			this->mOnTouchStationaryDispatch.removeEventHandle(nullptr, handle);
		}
		else if (InputEventId::TOUCHENDED_EVENT == evtId)
		{
			this->mOnTouchEndedDispatch->removeEventHandle(nullptr, handle);
		}
		else if (InputEventId::TOUCHCANCELED_EVENT == evtId)
		{
			this->mOnTouchCanceledDispatch->removeEventHandle(nullptr, handle);
		}

		this->mHasTouch = this->hasEventHandle();

		if (!this->mTouchSupported && !this->mHasTouch)
		{
			if (this->mSimulateMouseWithTouches)
			{
				this->mHasMultiTouch = this->hasMultiEventHandle();

				if (!this->mHasMultiTouch)
				{
					this->removeEventMouse(MMouseDevice::MouseLeftButton);
				}
			}
		}
	}

	void addMultiTouchListener(InputEventId evtId, EventDispatchDelegate handle)
	{
		if (InputEventId::MULTI_TOUCHBEGIN_EVENT == evtId)
		{
			this->mOnMultiTouchBeganDispatch->addEventHandle(nullptr, handle);
		}
		else if (InputEventId::MULTI_TOUCHMOVED_EVENT == evtId)
		{
			this->mOnMultiTouchMovedDispatch->addEventHandle(nullptr, handle);
		}
		else if (InputEventId::MULTI_TOUCHSTATIONARY_EVENT == evtId)
		{
			this->mOnMultiTouchStationaryDispatch->addEventHandle(nullptr, handle);
		}
		else if (InputEventId::MULTI_TOUCHENDED_EVENT == evtId)
		{
			this->mOnMultiTouchEndedDispatch->addEventHandle(nullptr, handle);
		}
		else if (InputEventId::MULTI_TOUCHCANCELED_EVENT == evtId)
		{
			this->mOnMultiTouchCanceledDispatch->addEventHandle(nullptr, handle);
		}

		this->mHasMultiTouch = true;

		if (!this->mTouchSupported)
		{
			if (this->mSimulateMouseWithTouches)
			{
				this->addEventMouse(MMouseDevice::MouseLeftButton);
			}
		}
	}

	void removeMultiTouchListener(InputEventId evtId, EventDispatchDelegate handle)
	{
		if (InputEventId::MULTI_TOUCHBEGIN_EVENT == evtId)
		{
			this->mOnMultiTouchBeganDispatch->removeEventHandle(nullptr, handle);
		}
		else if (InputEventId::MULTI_TOUCHMOVED_EVENT == evtId)
		{
			this->mOnMultiTouchMovedDispatch->removeEventHandle(nullptr, handle);
		}
		else if (InputEventId::MULTI_TOUCHSTATIONARY_EVENT == evtId)
		{
			this->mOnMultiTouchStationaryDispatch->removeEventHandle(nullptr, handle);
		}
		else if (InputEventId::MULTI_TOUCHENDED_EVENT == evtId)
		{
			this->mOnMultiTouchEndedDispatch->removeEventHandle(nullptr, handle);
		}
		else if (InputEventId::MULTI_TOUCHCANCELED_EVENT == evtId)
		{
			this->mOnMultiTouchCanceledDispatch->removeEventHandle(nullptr, handle);
		}

		this->mHasMultiTouch = this->hasMultiEventHandle();

		if (!this->mTouchSupported && !this->mHasMultiTouch)
		{
			if (this->mSimulateMouseWithTouches)
			{
				this->mHasTouch = this->hasEventHandle();

				if (!this->mHasTouch)
				{
					this->removeEventMouse(MMouseDevice::MouseLeftButton);
				}
			}
		}
	}

	void addAccelerationListener(InputEventId evtId, EventDispatchDelegate handle)
	{
		MAcceleration.mAccelerationOne.addAccelerationListener(evtId, handle);
		this->mHasAccelerationHandle = true;
	}

	public void removeAccelerationListener(InputEventId evtId, EventDispatchDelegate handle)
	{
		MAcceleration.mAccelerationOne.removeAccelerationListener(evtId, handle);
		if (!MAcceleration.mAccelerationOne.hasEventHandle())
		{
			this->mHasAccelerationHandle = false;
		}
	}

protected:
	void _addEventInputKey(InputKey* inputKey)
	{
		if (-1 == this->mEventInputKeyList.indexOf(inputKey))
		{
			this->mEventInputKeyList.add(inputKey);
		}
	}

	void _removeEventInputKey(InputKey* inputKey)
	{
		if (-1 != this->mEventInputKeyList.indexOf(inputKey))
		{
			this->mEventInputKeyList.remove(inputKey);
		}
	}

	void _addEventMouse(MMouseDevice* mouse)
	{
		if (-1 == this->mEventMouseList.indexOf(mouse))
		{
			this->mEventMouseList.add(mouse);
		}
	}

	void _removeEventMouse(MMouseDevice* mouse)
	{
		if (-1 != this->mEventMouseList.indexOf(mouse))
		{
			this->mEventMouseList.remove(mouse);
		}
	}

public:
	void ProcessTouches(float delta, TickMode tickMode)
	{
		if (this->hasTouch() || this->hasMultiTouch())
		{
			this->mMultiTouchSet.reset();

			this->mCurrentScheme = MControlScheme.Touch;

			int index = 0;
			while (index < UnityEngine.Input.touchCount)
			{
				UnityEngine.Touch touch = UnityEngine.Input.GetTouch(index);

				this->mCurrentTouchId = this->mMultiTouchEnabled ? touch.fingerId : 0;
				this->mCurrentTouch = MTouchDevice.GetTouch(this->mCurrentTouchId);

				this->mCurrentTouch.setNativeTouch(touch, this->mCurrentTouchId);
				this->mCurrentTouch.onTick(delta, tickMode);

				if (this->hasMultiTouch())
				{
					this->mMultiTouchSet.addTouch(this->mCurrentTouch);
				}

				++index;
			}

			if (this->hasMultiTouch())
			{
				this->mMultiTouchSet.onTick(delta, tickMode);
			}
		}
	}

	// 是否还有需要处理的事件
	bool hasEventHandle()
	{
		bool ret = false;

		if (this->mOnTouchBeganDispatch->hasEventHandle())
		{
			ret = true;
		}
		if (this->mOnTouchMovedDispatch.hasEventHandle())
		{
			ret = true;
		}
		if (this->mOnTouchStationaryDispatch.hasEventHandle())
		{
			ret = true;
		}
		if (this->mOnTouchEndedDispatch->hasEventHandle())
		{
			ret = true;
		}
		if (this->mOnTouchCanceledDispatch->hasEventHandle())
		{
			ret = true;
		}

		return ret;
	}

	bool hasTouch()
	{
		return this->mHasTouch;
	}

	void handleTouchBegan(MMouseOrTouch* touch)
	{
		if (nullptr != this->mOnTouchBeganDispatch)
		{
			this->mOnTouchBeganDispatch->dispatchEvent(touch);
		}
	}

	void handleTouchMoved(MMouseOrTouch* touch)
	{
		if (nullptr != this->mOnTouchMovedDispatch)
		{
			this->mOnTouchMovedDispatch.dispatchEvent(touch);
		}
	}

	void handleTouchStationary(MMouseOrTouch* touch)
	{
		if (nullptr != this->mOnTouchStationaryDispatch)
		{
			this->mOnTouchStationaryDispatch.dispatchEvent(touch);
		}
	}

	void handleTouchEnded(MMouseOrTouch* touch)
	{
		if (nullptr != this->mOnTouchEndedDispatch)
		{
			this->mOnTouchEndedDispatch->dispatchEvent(touch);
		}
	}

	void handleTouchCanceled(MMouseOrTouch* touch)
	{
		if (nullptr != this->mOnTouchCanceledDispatch)
		{
			this->mOnTouchCanceledDispatch->dispatchEvent(touch);
		}
	}

	/********************************** Multi Touch *********************************/
	// 是否还有需要处理的事件
	bool hasMultiEventHandle()
	{
		if (this->mOnMultiTouchBeganDispatch->hasEventHandle())
		{
			return true;
		}
		if (this->mOnMultiTouchMovedDispatch->hasEventHandle())
		{
			return true;
		}
		if (this->mOnMultiTouchStationaryDispatch->hasEventHandle())
		{
			return true;
		}
		if (this->mOnMultiTouchEndedDispatch->hasEventHandle())
		{
			return true;
		}
		if (this->mOnMultiTouchCanceledDispatch->hasEventHandle())
		{
			return true;
		}

		return false;
	}

	bool hasMultiTouch()
	{
		return this->mHasMultiTouch;
	}

	void handleMultiTouchBegan(IDispatchObject touch)
	{
		if (nullptr != this->mOnMultiTouchBeganDispatch)
		{
			this->mOnMultiTouchBeganDispatch->dispatchEvent(touch);
		}
	}

	void handleMultiTouchMoved(IDispatchObject touch)
	{
		if (nullptr != this->mOnMultiTouchMovedDispatch)
		{
			this->mOnMultiTouchMovedDispatch->dispatchEvent(touch);
		}
	}

	void handleMultiTouchStationary(IDispatchObject touch)
	{
		if (nullptr != this->mOnMultiTouchStationaryDispatch)
		{
			this->mOnMultiTouchStationaryDispatch->dispatchEvent(touch);
		}
	}

	void handleMultiTouchEnded(IDispatchObject touch)
	{
		if (nullptr != this->mOnMultiTouchEndedDispatch)
		{
			this->mOnMultiTouchEndedDispatch->dispatchEvent(touch);
		}
	}

	void handleMultiTouchCanceled(IDispatchObject touch)
	{
		if (nullptr != this->mOnMultiTouchCanceledDispatch)
		{
			this->mOnMultiTouchCanceledDispatch->dispatchEvent(touch);
		}
	}

	/******************* Mouse Dispatch *********************/
	// 是否还有需要处理的事件
	bool hasEventHandle(MMouseDevice* mouse)
	{
		return this->mMouseDispatchArray[mouse.mTouchIndex].hasEventHandle();
	}

	void handleMouseDown(MMouseOrTouch* mouse)
	{
		this->mMouseDispatchArray[mouse.mTouchIndex].handleMouseDown(mouse);
	}

	void handleMouseUp(MMouseOrTouch* mouse)
	{
		this->mMouseDispatchArray[mouse.mTouchIndex].handleMouseUp(mouse);
	}

	void handleMousePress(MMouseOrTouch* mouse)
	{
		this->mMouseDispatchArray[mouse.mTouchIndex].handleMousePress(mouse);
	}

	void handleMousePressOrMove(MMouseOrTouch* mouse)
	{
		this->mMouseDispatchArray[mouse.mTouchIndex].handleMousePressOrMove(mouse);
	}

	void handleMousePressMove(MMouseOrTouch* mouse)
	{
		this->mMouseDispatchArray[mouse.mTouchIndex].handleMousePressMove(mouse);
	}
};

MY_END_NAMESPACE

#endif