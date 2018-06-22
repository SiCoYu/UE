#pragma once

#include <string>

#include "IDispatchObject.h"
#include "PlatformDefine.h"
#include "KeyId.h"
#include "EventId.h"
#include "TickMode.h"
#include "EventDispatchDelegate.h"

struct FKey;

MY_BEGIN_NAMESPACE(MyNS)

class AddOnceEventDispatch;
 
class InputKey : public IDispatchObject
{
public:
	static InputKey* None;
    static InputKey* A;

    static InputKey* mInputKeyArray[(int)KeyId::Total];

private:
	FKey mKeyCode;
    std::string mKeyDesc;

    // 键盘状态
public:
	bool mKeyState;
    bool mKeyStateOld;
    bool mJustPressed;
    bool mJustReleased;

    // 事件处理
private:
	AddOnceEventDispatch* mOnKeyUpDispatch;
    AddOnceEventDispatch* mOnKeyDownDispatch;
    AddOnceEventDispatch* mOnKeyPressDispatch;

public:
	static InputKey** getInputKeyArray();

public:
	static std::string codeToString(KeyId value);

public:
	InputKey(FKey keyCode, std::string keyDesc);

	FKey getKeyCode();
	std::string getKeyDesc();
	void onTick(float delta, TickMode tickMode);

private:
	void _onKeyDown(FKey keyCode);
	void _onKeyUp(FKey keyCode);
	void _onKeyPress(FKey keyCode);

public:
	void addKeyListener(EventId evtId, EventDispatchDelegate handle);
	void removeKeyListener(EventId evtId, EventDispatchDelegate handle);
    // 是否还有需要处理的事件
	bool hasEventHandle();
	bool keyJustPressed();
	bool keyJustReleased();
	bool isKeyDown();
};

MY_END_NAMESPACE