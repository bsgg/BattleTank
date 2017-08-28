// Copyright Cubenary

#pragma once

#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h" // Must be the last include

class UTankAimingComponent;

/**
 *  Responsible for helping hte player aim
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:

	// BlueprintImplementableEvent: Macro wich allow us to call an event in blueprint and doesnt' need an implementation in cpp file
	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
	void FoundAimingComponet(UTankAimingComponent* aimingCompRef);

private:	
	
	virtual void BeginPlay() override;

	virtual void Tick( float DeltaTime ) override;

	// Start the tank moving the barrel so that a shot would hit where
	// the crosshair intersects the world
	void AimTowardsCrosshair();

	// Return an OUT parameter, true if hit landscape
	bool GetSightRayHitLocation(FVector& HitLocation) const;

	UPROPERTY(EditDefaultsOnly)
	float CrosshairXLocation = 0.5;

	UPROPERTY(EditDefaultsOnly)
	float CrosshairYLocation = 0.3333;

	UPROPERTY(EditDefaultsOnly)
	float LineTraceRange = 1000000;

	

	bool GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const;
	bool GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const;
};
