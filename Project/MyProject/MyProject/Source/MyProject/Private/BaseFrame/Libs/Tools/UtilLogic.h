#ifndef __UtilLogic_H
#define __UtilLogic_H

#include <string>
#include "Math/Vector.h"	// FVector
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class UtilLogic
{
public:
	static FVector FAKE_POS;  // 默认隐藏到这个位置

public:
	static std::string convScenePath2LevelName(std::string& path);
	static bool isInFakePos(FVector pos);
};

MY_END_NAMESPACE

#endif