#pragma once

#include "MyProjectPlayerState.generated.h"

UCLASS()
class AMyProjectPlayerState : public APlayerState
{
	GENERATED_UCLASS_BODY()


	// Begin APlayerState interface
	/** clear scores */
	virtual void Reset() override;

	/**
	 * Set the team 
	 *
	 * @param	InController	The controller to initialize state with
	 */
	virtual void ClientInitialize(class AController* InController) override;

	virtual void UnregisterPlayerWithSession() override;

	virtual void CopyProperties(class APlayerState* PlayerState) override;
};
