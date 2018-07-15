// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTrack.h"
#include "SprungWheel.h"

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = false;	
}


TArray<class ASprungWheel*> UTankTrack::GetWheels() const
{
	TArray<class ASprungWheel*> Wheels;
	return Wheels;
}

void UTankTrack::SetThrottle(float Throttle)
{
	float CurrentThrottle = FMath::Clamp<float>(Throttle, -1, 1);	
	DriveTrack(CurrentThrottle);
}

void UTankTrack::DriveTrack(float CurrentThrottle)
{
	auto foreApplied = CurrentThrottle * TrackMaxDrivingForce;

	auto Wheels = GetWheels();

	auto ForcePerWheel = foreApplied / Wheels.Num();

	for (ASprungWheel* Wheel : Wheels)
	{
		Wheel->AddDrivingForce(ForcePerWheel);
	}
}

