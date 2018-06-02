#pragma once

#include "IDispatchObject.h"
#include "Delegates/DelegateCombinations.h"		// DECLARE_DELEGATE_OneParams
#include "PlatformDefine.h"

MY_USING_NAMESPACE(MyNS)

/**
 * @brief Delegate
 */

class FMyDelegateDef
{
public:
	// ����һ�� Delegate ����
	DECLARE_DELEGATE_OneParam(MyDelegateBaseEvent, IDispatchObject*);

	DECLARE_DELEGATE_ThreeParams(MyDelegateThreeParamsTestEvent, int, int, bool);
	DECLARE_MULTICAST_DELEGATE_ThreeParams(MyDelegateMultiThreeParamsTestEvent, int, int, bool);
};