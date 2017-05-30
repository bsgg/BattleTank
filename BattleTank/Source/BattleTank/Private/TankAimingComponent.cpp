// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAimingComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::SetBarrelReference(UStaticMeshComponent* barrelToSet)
{
	barrel = barrelToSet;
}


// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	if (barrel != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("[UTankAimingComponent] there is a barrel:"));
	}else
	{
		UE_LOG(LogTemp, Warning, TEXT("[UTankAimingComponent] there is NO a barrel:"));
	}
}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


void UTankAimingComponent::AimAt(FVector hitLocation)
{
	
	if (barrel != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("[UTankAimingComponent] there is a barrel:"));

		auto ourTankName = GetOwner()->GetName();
		auto barrelPosition = barrel->GetComponentLocation().ToString();
		UE_LOG(LogTemp, Warning, TEXT("[AimAt] %s aiming at %s: from %s"), *ourTankName, *hitLocation.ToString(), *barrelPosition);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("[UTankAimingComponent] there is NO a barrel:"));
	}

	//
	
}

