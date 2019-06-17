#ifndef __UtilSysLibWrap_H
#define __UtilSysLibWrap_H

#include <string>
#include "PlatformDefine.h"

class UUserWidget;
class UObject;

MY_BEGIN_NAMESPACE(MyNS)

class UtilSysLibWrap
{
public:
	static FVector FAKE_POS;

public:
	static std::string getRandomVersion();
};

MY_END_NAMESPACE

#include "UtilSysLibWrap.inl"

#endif