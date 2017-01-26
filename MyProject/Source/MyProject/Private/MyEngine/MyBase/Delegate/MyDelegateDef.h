#pragma once

#include "IDispatchObject.h"
#include "Delegates/DelegateCombinations.h"		// DECLARE_DELEGATE_OneParams

/**
 * @brief Delegate
 */

class FMyDelegateDef
{
public:
	// ����һ�� Delegate ����
	DECLARE_DELEGATE_OneParam(MyDelegateBaseHandle, IDispatchObject*);
};