#pragma once

#include "MyProjectGameState.generated.h"

/** ranked PlayerState map, created from the GameState */
typedef TMap<int32, TWeakObjectPtr<AMyProjectPlayerState> > RankedPlayerMap;

UCLASS()
class AMyProjectGameState : public AGameState
{
	GENERATED_UCLASS_BODY()

public:
	void GetRankedMap(int32 TeamIndex, RankedPlayerMap& OutRankedMap) const;	
};
