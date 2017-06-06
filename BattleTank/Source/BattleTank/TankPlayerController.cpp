// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankPlayerController.h"
#include "Tank.h"

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
		//UE_LOG(LogTemp, Warning, TEXT("hitLoc %s:"),*hitLocation.ToString());

		// Get world location of linetrace through cross hair, 
		GetControlledTank()->AimAt(hitLocation);

	}
}

// Return an out parameter, true if hit landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector& outHitLocation) const
{
	// Get the crosshair prosition	
	int32 viewportSizeX, viewportSizeY;
	GetViewportSize(viewportSizeX, viewportSizeY);

	FVector2D screenLocation = FVector2D(viewportSizeX * CrossHairXLocation, viewportSizeY * CrossHairYLocation);

	// De project the screen positon of the crosshair ot a world direction
	FVector lookDirection;
	if (GetLookDirecton(screenLocation, lookDirection))
	{
		// Line trace along that look direction, and see what we hit (up to max range)
		//UE_LOG(LogTemp, Warning, TEXT("lookDirection %s:"), *lookDirection.ToString());		
		if (GetLookVectorHitLocation(lookDirection, outHitLocation))
		{
			//UE_LOG(LogTemp, Warning, TEXT("outHitLocation %s:"), *outHitLocation.ToString());
		}
		else
		{
			//UE_LOG(LogTemp, Warning, TEXT("outHitLocation %s:"), *outHitLocation.ToString());
		}
	}

	return true;
}

bool ATankPlayerController::GetLookDirecton(FVector2D screenLocation, FVector& lookDirection) const
{
	FVector cameraWorldLocation;
	return DeprojectScreenPositionToWorld(screenLocation.X, screenLocation.Y, cameraWorldLocation, lookDirection);
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector lookDirection, FVector& outHitLocation) const
{
	FHitResult hitResult;
	FVector start = PlayerCameraManager->GetCameraLocation();
	FVector end = start + (lookDirection * LineTraceRange);

	if (GetWorld()->LineTraceSingleByChannel(hitResult, start, end, ECollisionChannel::ECC_Visibility))
	{
		outHitLocation = hitResult.Location;
		return true;
	}

	outHitLocation = FVector(0.0f);
	return false;
}

