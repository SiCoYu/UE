#pragma once

#include <string>
#include "InputCoreTypes.h"		// FKey \ EKeys

#include "IDispatchObject.h"
#include "PlatformDefine.h"
#include "KeyId.h"
#include "InputEventId.h"
#include "TickMode.h"
#include "EventDispatchDelegate.h"

MY_BEGIN_NAMESPACE(MyNS)

class AddOnceEventDispatch;
 
class InputKey : public IDispatchObject
{
public:
    static InputKey* A;
	static InputKey* S;
	static InputKey* D;
	static InputKey* F;

	static bool msIsInit;
    static InputKey* msInputKeyArray[(int)KeyId::Total];

private:
	KeyId mKeyId;
	FKey mKeyCode;
    std::string mKeyDesc;

    // 键盘状态
public:
	bool mKeyState;			// true: down, false:up
    bool mKeyStateOld;		// 前一个状态
    bool mJustPressed;		// 从 up 变换到 down 状态
    bool mJustReleased;		// 从 down 变换到 up 状态

    // 事件处理
private:
	AddOnceEventDispatch* mOnKeyUpDispatch;
    AddOnceEventDispatch* mOnKeyDownDispatch;
    AddOnceEventDispatch* mOnKeyPressDispatch;

public:
	static InputKey** getInputKeyArray();

public:
	static std::string codeToString(FKey value);

public:
	InputKey(KeyId keyId, FKey keyCode, std::string keyDesc);

	KeyId getKeyId();
	FKey getKeyCode();
	std::string getKeyDesc();
	void onTick(float delta, TickMode tickMode);

private:
	// down
	void _onKeyDown(FKey keyCode);
	// up
	void _onKeyUp(FKey keyCode);
	// press 一直按下
	void _onKeyPress(FKey keyCode);

public:
	void addKeyListener(InputEventId evtId, EventDispatchDelegate handle);
	void removeKeyListener(InputEventId evtId, EventDispatchDelegate handle);

    // 是否还有需要处理的事件
	bool hasEventHandle();
	bool keyJustPressed();
	bool keyJustReleased();
	bool isKeyDown();
};

MY_END_NAMESPACE