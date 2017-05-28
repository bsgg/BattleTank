// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	auto ControllerTank = GetControlledTank();
	if (!ControllerTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController not possesing the tank!!!"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController  possesing: %s"), *ControllerTank->GetName());
	}	
}


void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//UE_LOG(LogTemp, Warning, TEXT("PlayerController ticking"));
	AimTowardsCrosshair();
}


ATank* ATankPlayerController::GetControlledTank() const
{
	ATank* tank = Cast<ATank>(GetPawn());
	return  tank;
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank()) return;
		
	FVector hitLocation;

	if (GetSightRayHitLocation(hitLocation))
	{
		UE_LOG(LogTemp, Warning, TEXT("hitLoc %s:"),*hitLocation.ToString());

		// Get world location of linetrace through cross hair, 

	}
}

// Return an out parameter, true if hit landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector& outHitLocation) const
{
	outHitLocation = FVector(0.0f);

	return true;
}

