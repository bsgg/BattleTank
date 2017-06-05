// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankBarrel.h"
#include "TankAimingComponent.h"



// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel* barrelToSet)
{
	barrel = barrelToSet;
}

void UTankAimingComponent::AimAt(FVector hitLocation, float launchSpeed)
{
	if (barrel == nullptr) return;
	
	FVector outLaunchVelocity;
	FVector startLocation = barrel->GetSocketLocation(FName("Projectile"));
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(this,
			outLaunchVelocity,
			startLocation,
			hitLocation,
			launchSpeed,
			ESuggestProjVelocityTraceOption::Type::DoNotTrace
		);

	if (bHaveAimSolution)
	{
		// Calculate the outLaunchVelocity
		FVector aimDirection = outLaunchVelocity.GetSafeNormal();
		auto tankName = GetOwner()->GetName();
		UE_LOG(LogTemp, Warning, TEXT("[AimAt] %s Aiming at %s"), *tankName, *aimDirection.ToString());

		MoveBarrelTowards(aimDirection);
	}
}

void UTankAimingComponent::MoveBarrelTowards(FVector aimDirection)
{
	// Work out difference between current barrel rotation and aimDirection
	FRotator barrelRotator = barrel->GetForwardVector().Rotation();
	FRotator aimAsRotator = aimDirection.Rotation();
	
	//UE_LOG(LogTemp, Warning, TEXT("[AimAt] aimAsRotator: %s"), *aimAsRotator.ToString());
	FRotator deltaRotator = aimAsRotator - barrelRotator;

	// Move the barrel
	//barrel->AddLocalRotation(deltaRotator);
	barrel->Elevate(5);

	// Given a max elevation speed, and the frame time
	

}

