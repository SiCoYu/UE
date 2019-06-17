#ifndef __EditorWinLogDevice_H
#define __EditorWinLogDevice_H

#include "LogDeviceBase.h"
#include "PlatformDefine.h"

class NativeEditorWinLogDevice;

MY_BEGIN_NAMESPACE(MyNS)

class EditorWinLogDevice : public LogDeviceBase
{
protected:
	NativeEditorWinLogDevice* mNativeEditorWinLogDevice;

public:
	EditorWinLogDevice();
};

MY_END_NAMESPACE

#endif