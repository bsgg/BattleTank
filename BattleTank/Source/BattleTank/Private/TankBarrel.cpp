// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankBarrel.h"


void UTankBarrel::Elevate(float InRelativeSpeed)
{

	// Move the barrel the right amount this frame
	// Given a max elevation speed, and the frame time
	InRelativeSpeed = FMath::Clamp<float>(InRelativeSpeed, -1, +1);
	auto ElevationChange = InRelativeSpeed * MaxDegressPersSecond * GetWorld()->DeltaTimeSeconds;
	auto RawNewElevation = RelativeRotation.Pitch + ElevationChange;
	auto Elevation = FMath::Clamp<float>(RawNewElevation, MinElevationDegrees, MaxElevationDegrees);
	SetRelativeRotation(FRotator(Elevation, 0, 0));
	
}

