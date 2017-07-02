// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTrack.h"

void UTankTrack :: SetThrottle(float throttle)
{
	//float time = GetWorld()->GetTimeSeconds();
	auto name = GetName();
	UE_LOG(LogTemp, Warning, TEXT("%s: Throttle %f"), *name, throttle);
}


