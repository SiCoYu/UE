#pragma once

//#include "MyPlayerState.h"
#include "MyGameState.generated.h"

class AMyPlayerState;

/** ranked PlayerState map, created from the GameState */
typedef TMap<int32, TWeakObjectPtr<class AMyPlayerState> > RankedPlayerMap;

UCLASS()
class AMyGameState : public AGameState
{
	GENERATED_UCLASS_BODY()

public:
	/** gets ranked PlayerState map for specific team */
	void GetRankedMap(int32 TeamIndex, RankedPlayerMap& OutRankedMap) const;

	// https://wiki.unrealengine.com/Survival_Sample_Game:_Section_4
public:
	/* By passing in "exec" we expose it as a command line (press ~ to open) */
	UFUNCTION(exec)
	void SetTimeOfDay(float NewTimeOfDay);
};
