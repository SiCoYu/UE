#ifndef __InputMgr_H
#define __InputMgr_H

#include <string>

#include "MyProject.h"
#include "MCamera.h"
#include "UtilEngineWrap.h"
#include "MDictionary.h"
#include "MRay.h"
#include "IOEventDispatchDelegate.h"
#include "PlatformDefine.h"

class AMyPlayerControllerBase;
class UPlayerInput;
class FKey;

MY_BEGIN_NAMESPACE(MyNS)

/**
 * @brief 输入管理器主要是控制场景中的对象的
 */
class InputMgr
{
protected:
	AMyPlayerControllerBase* mPlayerController;
	UPlayerInput* mPlayerInput;

public:
	InputMgr();
	~InputMgr();

	void init();
	void dispose();

	bool getKeyDown(FKey keyCode);
	bool getKeyUp(FKey keyCode);
	bool getKey(FKey keyCode);
};

MY_END_NAMESPACE

#endif