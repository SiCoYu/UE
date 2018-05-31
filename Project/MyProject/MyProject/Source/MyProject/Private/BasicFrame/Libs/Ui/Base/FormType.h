#ifndef __FormType_H
#define __FormType_H

#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

namespace NSFormType
{
	enum FormType
	{
		eUMG,
		eSlate,
	};

	enum UMGOuterType
	{
		eWorld,
		ePlayerController,
		eGameInstance,
	};
}

MY_END_NAMESPACE

#endif