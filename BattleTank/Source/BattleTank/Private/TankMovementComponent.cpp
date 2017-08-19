#include "BattleTank.h"
#include "TankTrack.h"
#include "TankMovementComponent.h"

void UTankMovementComponent::Initialise(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	//auto Time = GetWorld()->GetTimeSeconds();
	//UE_LOG(LogTemp, Warning, TEXT("Intend move forward throw: %f"), Throw);	
	if (!LeftTrack || !RightTrack) { return; }

	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
}

void UTankMovementComponent::IntendTurnRight(float Throw)
{
	//auto Time = GetWorld()->GetTimeSeconds();
	//UE_LOG(LogTemp, Warning, TEXT("Intend turn right throw: %f"), Throw);

	if (!LeftTrack || !RightTrack) { return; }

	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	// No need to call super as we're replacing the functionality
	
	FVector tankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	FVector aiForwardIntention = MoveVelocity.GetSafeNormal();

	//auto tankName = GetOwner()->GetName();
	//UE_LOG(LogTemp, Warning, TEXT("%s RequestDirectMove speed: %s"), *tankName, *moveVelocity);

	// Dot product (returns float)
	// A . B = ||A||||B||cos(a)
	// A . B == 0 Angle between them is 90
	// A . B == ||A||||B|| Angle between them is 0
	float forwardThrow = FVector::DotProduct(tankForward, aiForwardIntention);	
	IntendMoveForward(forwardThrow);


	// Cross product (returns vector)
	// A x B = ||A||||B||sin(a)n
	// Where (a) is the angle between a and be in the plain cointaining them
	// Retruns a perpendicular vector between A and B
	float RigthThrow = FVector::CrossProduct(tankForward,aiForwardIntention).Z;
	IntendTurnRight(RigthThrow);


	//UE_LOG(LogTemp, Warning, TEXT("Right: %f, Forward: %f"), RigthThrow, forwardThrow);

}

