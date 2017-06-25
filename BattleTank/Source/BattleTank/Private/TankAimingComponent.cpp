// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankBarrel.h"
#include "TankTurret.h"
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
	if (!barrelToSet) { return; }
	barrel = barrelToSet;
}

void UTankAimingComponent::SetTurretReference(UTankTurret* turretToSet)
{
	if (!turretToSet) { return; }
	turret = turretToSet;
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
			0,
			0,
			ESuggestProjVelocityTraceOption::DoNotTrace
		);

	if (bHaveAimSolution)
	{
		// Calculate the outLaunchVelocity
		FVector aimDirection = outLaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(aimDirection);

		/*float time = GetWorld()->GetTimeSeconds();
		UE_LOG(LogTemp, Warning, TEXT("%f YES found solution"), time);*/
	}/*else
	{
	
		//float time = GetWorld()->GetTimeSeconds();
		//UE_LOG(LogTemp, Warning, TEXT("%f NO found solution"), time);
	}*/
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
	barrel->Elevate(deltaRotator.Pitch);

	turret->Rotate(deltaRotator.Yaw);
}

