#ifndef __FormType_H
#define __FormType_H

#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

enum class FormType
{
	eUMG,
	eSlate,
};

enum class UMGOuterType
{
	eWorld,
	ePlayerController,
	eGameInstance,
};

MY_END_NAMESPACE

#endif