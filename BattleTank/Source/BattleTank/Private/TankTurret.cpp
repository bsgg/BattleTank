// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTurret.h"



void UTankTurret::Rotate(float InRelativeSpeed)
{

	InRelativeSpeed = FMath::Clamp<float>(InRelativeSpeed, -1, +1);
	float rotationChange = InRelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;

	float newRotation = RelativeRotation.Yaw + rotationChange;
	SetRelativeRotation(FRotator(0.0f, newRotation, 0.0f));

}