// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "TankAimingComponent.h"
#include "Projectile.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	//bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;
	//Ammo = 3;
}

void UTankAimingComponent::BeginPlay()
{
	//Super::BeginPlay(); 

	LastFireTime = FPlatformTime::Seconds();

	//UE_LOG(LogTemp, Warning, TEXT("UTankAimingComponent::BeginPlay"));
}

void UTankAimingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
	//Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (Ammo <= 0)
	{
		FiringState = EFiringState::NoAmmo;
	}
	else if ((FPlatformTime::Seconds() - LastFireTime) < ReloadTimeInSeconds)
	{
		FiringState = EFiringState::Reloading;
	}
	else if (IsBarrelMoving())
	{
		FiringState = EFiringState::Aiming;
	}
	else
	{
		FiringState = EFiringState::Locked;
	}
}

void UTankAimingComponent::Initialise(UTankBarrel* barrelToSet, UTankTurret* turretToSet)
{
	Barrel = barrelToSet;
	Turret = turretToSet;
}

bool UTankAimingComponent::IsBarrelMoving() const
{
	if (!ensure(Barrel)) { return false; }

	FVector forwardBarrel = Barrel->GetForwardVector();

	return (!forwardBarrel.Equals(AimDirection, 0.01f));
}


void UTankAimingComponent::AimAt(FVector HitLocation)
{
	if (!ensure(Barrel)) { return; }

	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity
	(
		this,
		OutLaunchVelocity,
		StartLocation,
		HitLocation,
		LaunchSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace // Paramater must be present to prevent bug
	);

	if (bHaveAimSolution)
	{
		FVector aimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(aimDirection);
	}
}

void UTankAimingComponent::MoveBarrelTowards(FVector aimDirection)
{
	if (!ensure(Barrel) || !ensure(Turret)) { return; }

	// Work-out difference between current barrel roation, and AimDirection
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = aimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;

	Barrel->Elevate(DeltaRotator.Pitch);

	// Always yaw the shortest way
	if (FMath::Abs(DeltaRotator.Yaw) < 180.0f)
	{
		Turret->Rotate(DeltaRotator.Yaw);

	}else // Avoid going the long-way round
	{
		Turret->Rotate(-DeltaRotator.Yaw);
	}
	
}

void UTankAimingComponent::Fire()
{
	if ((FiringState == EFiringState::Locked) || (FiringState == EFiringState::Aiming))
	{
		if (!ensure(Barrel)) return;
		if (!ensure(ProjectileBlueprint)) return;


		UE_LOG(LogTemp, Warning, TEXT("Fire!! "));

		// Spawn a projectile at the socket location on the barrel
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBlueprint,
			Barrel->GetSocketLocation(FName("Projectile")),
			Barrel->GetSocketRotation(FName("Projectile"))
			);

		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();
		

		// Decrease Ammo and set state to NoAmmo if there is no ammo
		Ammo -= 1;

	}
}

EFiringState UTankAimingComponent::GetFireState() const
{
	return FiringState;
}

int32 UTankAimingComponent::GetAmmoLeft() const
{
	return Ammo;
}
