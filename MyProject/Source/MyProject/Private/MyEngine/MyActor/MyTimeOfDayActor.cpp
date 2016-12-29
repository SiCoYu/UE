#include "MyProject.h"
#include "MyGameState.h"
#include "MyTimeOfDayActor.h"

AMyTimeOfDayActor::AMyTimeOfDayActor(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{

}

void AMyTimeOfDayActor::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	AMyGameState* MyGameState = Cast<AMyGameState>(GetWorld()->GetGameState());
	if (MyGameState)
	{
		///* Update the position of the sun. */
		//if (PrimarySunLight)
		//{
		//	if (LastTimeOfDay == MyGameState->ElapsedGameMinutes)
		//	{
		//		TimeSinceLastIncrement += DeltaSeconds;
		//	}
		//	else
		//	{
		//		/* Reset prediction */
		//		TimeSinceLastIncrement = 0;
		//	}

		//	/* Predict the movement of the sun to smooth out the rotations between replication updates of the actual time of day */
		//	const float PredictedIncrement = MyGameState->GetTimeOfDayIncrement() * TimeSinceLastIncrement;

		//	/* TimeOfDay is expressed in minutes, we need to convert this into a pitch rotation */
		//	const float MinutesInDay = 24 * 60;
		//	const float PitchOffset = 90; /* The offset to account for time of day 0 should equal midnight */
		//	const float PitchRotation = 360 * ((MyGameState->ElapsedGameMinutes + PredictedIncrement) / MinutesInDay);

		//	FRotator NewSunRotation = FRotator(PitchRotation + PitchOffset, 45.0f, 0);
		//	PrimarySunLight->SetActorRelativeRotation(NewSunRotation);

		//	LastTimeOfDay = MyGameState->ElapsedGameMinutes;
		//}
	}
}