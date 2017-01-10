#pragma once

#include "Animation/AnimNodeBase.h"	// UAnimGraphNode_Base
#include "AnimGraphNode_VictoryTurnInPlace.generated.h"

//Whole point of this is to be wrapper for node struct
//		so it depends on it, and that node must compile first
//		for type to be recognized

/**
 * @brief https://wiki.unrealengine.com/Animation_Node,_Entire_Source_for_a_Turn_In_Place_Node
 */

// The dependsOn specifier is deprecated. Please use #include "ClassHeaderFilename.h" instead.
//UCLASS(MinimalAPI, dependson = FAnimNode_VictoryTurnInPlace)
UCLASS(MinimalAPI)
class FAnimNode_VictoryTurnInPlace : public FAnimNode_Base
{
	GENERATED_UCLASS_BODY()
};