// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

// Enum for aiming state
UENUM()
enum class EFiringState : uint8
{
	Reloading,
	Aiming,
	Locked,
	NoAmmo
};


// Forward Declaration
class UTankBarrel;
class UTankTurret;
class AProjectile;

// Holds barrel's properties and Elevate method
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialise(UTankBarrel* barrelToSet, UTankTurret* turretToSet);

	void AimAt(FVector HitLocation);

protected:
	//UPROPERTY BlueprintReadOnly has to be in protected section
	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringState FiringState = EFiringState::Reloading;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float LaunchSpeed = 4000;

	
	

private:

	// Sets default values for this component's properties
	UTankAimingComponent();

	virtual void TickComponent ( float DeltaTime, enum ELevelTick TickType,	FActorComponentTickFunction * ThisTickFunction) override;

	virtual void BeginPlay() override;

	void MoveBarrelTowards(FVector aimDirection);

	bool IsBarrelMoving() const;

private:

	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;	

	FVector AimDirection;

	float Ammo = 10;

public:
	UFUNCTION(BlueprintCallable, Category = "Firing")
	void Fire();

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<AProjectile> ProjectileBlueprint;


	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float ReloadTimeInSeconds = 3;

	double LastFireTime = 0;

	EFiringState GetFireState() const;

	UFUNCTION(BlueprintCallable, Category = "Firing")
	int GetAmmoLeft() const;
};