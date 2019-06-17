#ifndef __UtilLogic_H
#define __UtilLogic_H

#include <string>
#include "Math/Vector.h"	// FVector
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class UtilLogic
{
public:
	static FVector FAKE_POS;  // Ĭ�����ص����λ��

public:
	static std::string convScenePath2LevelName(std::string& path);
	static bool isInFakePos(FVector pos);
};

MY_END_NAMESPACE

#endif