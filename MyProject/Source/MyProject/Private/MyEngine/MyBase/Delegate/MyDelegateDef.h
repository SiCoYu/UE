#pragma once

#include "IDispatchObject.h"
#include "Delegates/DelegateCombinations.h"		// DECLARE_DELEGATE_OneParams

/**
 * @brief Delegate
 */

class FMyDelegateDef
{
public:
	// 定义一个 Delegate 类型
	DECLARE_DELEGATE_OneParam(MyDelegateBaseHandle, IDispatchObject*);

	DECLARE_DELEGATE_ThreeParams(MyDelegateThreeParamsTestEvent, int, int, bool);
	DECLARE_MULTICAST_DELEGATE_ThreeParams(MyDelegateMultiThreeParamsTestEvent, int, int, bool);
};