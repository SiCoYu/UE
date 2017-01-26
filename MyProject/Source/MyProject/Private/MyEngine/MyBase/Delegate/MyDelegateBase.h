#pragma once

#include "UObject/Object.h"	// UObject
#include "Delegates/DelegateCombinations.h"		// DECLARE_DELEGATE_OneParams
#include "IDispatchObject.h"
#include "MyDelegateDef.h"
#include "Delegates/Delegate.h"
//#include "Delegates/DelegateSignatureImpl.inl"
#include "MyDelegateBase.generated.h"

/**
 * @brief Delegate
 */

UCLASS()
class UMyDelegateBase : public UObject
{
	GENERATED_UCLASS_BODY()

public:
	FMyDelegateDef::MyDelegateBaseHandle mMyDelegateBaseHandle;
};