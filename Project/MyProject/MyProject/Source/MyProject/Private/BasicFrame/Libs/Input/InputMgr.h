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
#include "MMouseDeviceType.h"
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
	MMouseDispatch* mMouseDispatchArray[MMouseDeviceType::eMouseTotalButton];

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
	void onTick(float delta, TickMode tickMode);

	bool keyJustPressed(InputKey* inputKey);
	bool keyJustReleased(InputKey* inputKey);
	bool isKeyDown(InputKey* inputKey);
	bool isAnyKeyDown();

	// 添加 KeyInput 输入事件
	void addKeyListener(InputKey* inputKey, InputEventId evtId, EventDispatchDelegate handle);
	// 移除键盘 KeyInput 输入事件
	void removeKeyListener(InputKey* inputKey, InputEventId evtId, EventDispatchDelegate handle);
	// 添加鼠标监听器
	void addMouseListener(MMouseDevice* mouse, InputEventId evtId, EventDispatchDelegate handle);
	// 移除鼠标监听器
	void removeMouseListener(MMouseDevice* mouse, InputEventId evtId, EventDispatchDelegate handle);
	void addTouchListener(InputEventId evtId, EventDispatchDelegate handle);
	void removeTouchListener(InputEventId evtId, EventDispatchDelegate handle);
	void addMultiTouchListener(InputEventId evtId, EventDispatchDelegate handle);
	void removeMultiTouchListener(InputEventId evtId, EventDispatchDelegate handle);
	void addAccelerationListener(InputEventId evtId, EventDispatchDelegate handle);
	void removeAccelerationListener(InputEventId evtId, EventDispatchDelegate handle);

protected:
	void _addEventInputKey(InputKey* inputKey);
	void _removeEventInputKey(InputKey* inputKey);
	void _addEventMouse(MMouseDevice* mouse);
	void _removeEventMouse(MMouseDevice* mouse);

public:
	void ProcessTouches(float delta, TickMode tickMode);
	// 是否还有需要处理的事件
	bool hasEventHandle();
	bool hasTouch();

	void handleTouchBegan(MMouseOrTouch* touch);
	void handleTouchMoved(MMouseOrTouch* touch);
	void handleTouchStationary(MMouseOrTouch* touch);
	void handleTouchEnded(MMouseOrTouch* touch);
	void handleTouchCanceled(MMouseOrTouch* touch);

	/********************************** Multi Touch *********************************/
	// 是否还有需要处理的事件
	bool hasMultiEventHandle();
	bool hasMultiTouch();

	void handleMultiTouchBegan(IDispatchObject touch);
	void handleMultiTouchMoved(IDispatchObject touch);
	void handleMultiTouchStationary(IDispatchObject touch);
	void handleMultiTouchEnded(IDispatchObject touch);
	void handleMultiTouchCanceled(IDispatchObject touch);

	/******************* Mouse Dispatch *********************/
	// 是否还有需要处理的事件
	bool hasEventHandle(MMouseDevice* mouse);
	void handleMouseDown(MMouseOrTouch* mouse);
	void handleMouseUp(MMouseOrTouch* mouse);
	void handleMousePress(MMouseOrTouch* mouse);
	void handleMousePressOrMove(MMouseOrTouch* mouse);
	void handleMousePressMove(MMouseOrTouch* mouse);
};

MY_END_NAMESPACE

#endif