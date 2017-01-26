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

	FMyDelegateDef::MyDelegateThreeParamsTestEvent mMyDelegateThreeParamsTestHandle;

	FMyDelegateDef::MyDelegateMultiThreeParamsTestEvent mMyDelegateMultiThreeParamsTestEvent
	FMyDelegateDef::MyDelegateMultiThreeParamsTestEvent::FDelegate mOnMultiThreeParamsTestDelegate;
	FDelegateHandle mOnMultiThreeParamsTestDelegateHandle;

public:
	void testOneDelegate();
	void testMultiDelegate();
	void handle(int aaa, int bbb, bool ccc);
	void multiHandle(int aaa, int bbb, bool ccc);
};