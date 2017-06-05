// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankBarrel.h"


void UTankBarrel::Elevate(float DegreesPerSecond)
{
	UE_LOG(LogTemp, Warning, TEXT("Barrel elevate called at speed: %f"), DegreesPerSecond);

	// Move the barrel
	// Given a max elevation speed, and the frame time
}

