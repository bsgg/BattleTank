// Fill out your copyright notice in the Description page of Project Settings.

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
	RightTrack->SetThrottle(-Throw);
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

	// Vector Dot product
	// A . B = ||A||||B||cosa
	// A . B == 0 Angle between them is 90
	// A . B == ||A||||B|| Angle between them is 0

	float forwardThrow = FVector::DotProduct(tankForward, aiForwardIntention);
	UE_LOG(LogTemp, Warning, TEXT("RequestDirectMove speed: %f"), forwardThrow);
	IntendMoveForward(forwardThrow);
}

