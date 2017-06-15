// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankBarrel.h"


void UTankBarrel::Elevate(float InRelativeSpeed)
{

	// Move the barrel the right amount this frame
	// Given a max elevation speed, and the frame time
	InRelativeSpeed = FMath::Clamp<float>(InRelativeSpeed, -1, +1);
	float elevationChange = InRelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;

	float rawNewElevation = RelativeRotation.Pitch + elevationChange;
	float elevation = FMath::Clamp<float>(rawNewElevation, MinElevationDegrees, MaxElevationDegrees);

	SetRelativeRotation(FRotator(elevation, 0.0f, 0.0f));
	
}

