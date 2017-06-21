// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankBarrel.h"
#include "Tank.h"
#include "Projectile.h"
#include "TankAimingComponent.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// No need to protect pointers as added at construction
	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
}


void ATank::SetBarrelReference(UTankBarrel* barrelToSet)
{
	TankAimingComponent->SetBarrelReference(barrelToSet);
	Barrel = barrelToSet;
}


void ATank::SetTurretBarrelReference(UTankTurret* turretToSet)
{
	TankAimingComponent->SetTurretReference(turretToSet);
}

// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATank::AimAt(FVector hitLocation)
{
	// Call the AimAt method from TankAimingComponent
	TankAimingComponent->AimAt(hitLocation, LaunchSpeed);
	
}

void ATank::Fire()
{
	float time = GetWorld()->GetTimeSeconds();
	UE_LOG(LogTemp, Warning, TEXT("%f Fire!"), time);

	if (!Barrel) { return; }

	// Spawn a projectile at the socket location on the barrel
	GetWorld()->SpawnActor<AProjectile>(
		ProjectileBlueprint, 
		Barrel->GetSocketLocation(FName("Projectile")),
		Barrel->GetSocketRotation(FName("Projectile"))	
		);
}

