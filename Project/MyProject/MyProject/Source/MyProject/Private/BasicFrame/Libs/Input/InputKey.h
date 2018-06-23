#pragma once

#include <string>

#include "IDispatchObject.h"
#include "PlatformDefine.h"
#include "KeyId.h"
#include "InputEventId.h"
#include "TickMode.h"
#include "EventDispatchDelegate.h"

struct FKey;

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
	static std::string codeToString(FKey value);

public:
	InputKey(KeyId keyId, FKey keyCode, std::string keyDesc);

	KeyId getKeyId();
	FKey getKeyCode();
	std::string getKeyDesc();
	void onTick(float delta, TickMode tickMode);

private:
	void _onKeyDown(FKey keyCode);
	void _onKeyUp(FKey keyCode);
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