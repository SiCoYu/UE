#include "MyProject.h"
#include "CppAndBlueprintTargetInterface.h"
#include "TargetInterfaceBPFunctionLibrary.h"

UTargetInterfaceBPFunctionLibrary::UTargetInterfaceBPFunctionLibrary(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{

}

float UTargetInterfaceBPFunctionLibrary::GetHealth(const TScriptInterface<ICppAndBlueprintTargetInterface> &target)
{
	return target->GetHealth();
}