// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h" // Must be the last include

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:

	void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	ATank* GetControlledTank() const;
	
private:
	// Start the tank moving the barrel so that a shot would hit where 
	// the crosshair intersects the world
	void AimTowardsCrosshair();

	// Return an out parameter, true if hit landscape
	bool GetSightRayHitLocation(FVector& outHitLocation) const;
	
};
