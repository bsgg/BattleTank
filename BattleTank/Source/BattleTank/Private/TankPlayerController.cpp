// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAimingComponent.h"
#include "TankPlayerController.h"
#include "Tank.h"


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (!GetPawn()) return;

	// Find aimingComponent in the tank pawn and call the event
	auto aimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();

	if (!ensure(aimingComponent)) { return; }	

	FoundAimingComponet(aimingComponent);
	
	
}


void ATankPlayerController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);

	if (InPawn)
	{
		auto possessedTank = Cast<ATank>(InPawn);
		if (!ensure(possessedTank))
		{
			return;
		}

		// Suscribe our local method ot the tank's death event
		possessedTank->OnDeath.AddUniqueDynamic(this, &ATankPlayerController::OnControlTankDeath);
	}
}

void ATankPlayerController::OnControlTankDeath()
{
	UE_LOG(LogTemp, Warning, TEXT("[  ATankPlayerController::OnControlTankDeath] %s "), *GetName());

	// Start spectating mode, as the only mode allowed.
	StartSpectatingOnly();

	// Call this function to detach safely pawn from its controller, knowing that we will be destroyed soon.
	/*if (GetPawn())
	{
		//GetPawn()->DetachFromControllerPendingDestroy();
	}*/

}



void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick( DeltaTime );
	AimTowardsCrosshair();
}


void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetPawn()) { return; } // If not possesing

	auto aimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();

	if (!ensure(aimingComponent)) { return; }


	FVector HitLocation; // Out parameter
	bool bGotHitLocation = GetSightRayHitLocation(HitLocation);

	if (bGotHitLocation) // Has "side-effect", is going to line trace
	{
		aimingComponent->AimAt(HitLocation);
	}
}

// Get world location of linetrace through crosshair, true if hits landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{
	// Find the crosshair position in pixel coordinates
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	auto ScreenLocation = FVector2D(ViewportSizeX * CrosshairXLocation, ViewportSizeY * CrosshairYLocation);

	// "De-project" the screen position of the crosshair to a world direction
	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection))
	{
		// Line-trace along that LookDirection, and see what we hit (up to max range)
		return GetLookVectorHitLocation(LookDirection, HitLocation);
	}

	return false;
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const
{
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + (LookDirection * LineTraceRange);
	if (GetWorld()->LineTraceSingleByChannel(
			HitResult,
			StartLocation,
			EndLocation,
			ECollisionChannel::ECC_Visibility)
		)
	{
		HitLocation = HitResult.Location;
		return true;
	}
	HitLocation = FVector(0);
	return false; // Line trace didn't succeed
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
	FVector CameraWorldLocation; // To be discarded
	return  DeprojectScreenPositionToWorld(
		ScreenLocation.X,
		ScreenLocation.Y, 
		CameraWorldLocation,
		LookDirection
	);
}