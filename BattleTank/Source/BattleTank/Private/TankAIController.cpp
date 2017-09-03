// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAimingComponent.h"
#include "TankAIController.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto ControlledTank = GetPawn();

	if (!ensure(PlayerTank) && ControlledTank) { return; }
	
	// Move towards the player
	MoveToActor(PlayerTank, AcceptanceRadius);

	// Aim towards the player
	auto aimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
	
	aimingComponent->AimAt(PlayerTank->GetActorLocation());

	/*if (aimingComponent->GetFireState() == EFiringState::Locked)
	{

		UE_LOG(LogTemp, Warning, TEXT("[ATankAIController::Tick] EFiringState::Locked "));
	}
	else if (aimingComponent->GetFireState() == EFiringState::Reloading)
	{
		UE_LOG(LogTemp, Warning, TEXT("[ATankAIController::Tick] FiringState::Reloading "));

	}
	else if (aimingComponent->GetFireState() == EFiringState::Aiming)
	{
		UE_LOG(LogTemp, Warning, TEXT("[ATankAIController::Tick] EFiringState::Aiming "));

	}
	else if (aimingComponent->GetFireState() == EFiringState::NoAmmo)
	{
		UE_LOG(LogTemp, Warning, TEXT("[ATankAIController::Tick] EFiringState::NoAmmo "));

	}*/

	// If state is locked then fire
	if (aimingComponent->GetFireState() == EFiringState::Locked)
	{
		aimingComponent->Fire(); // TODO limit firing rate
	}
	
}
