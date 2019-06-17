#include "MyProject.h"
#include "CppAndBlueprintTargetInterface.h"

UCppAndBlueprintTargetInterface::UCppAndBlueprintTargetInterface(const class FObjectInitializer& PCIP) : Super(PCIP) {

}
// Give GetHealth a default implementation
float ICppAndBlueprintTargetInterface::GetHealth() {
	return 0.0f;
}