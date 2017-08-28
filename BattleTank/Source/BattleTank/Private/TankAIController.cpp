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

	// If state is locked then fire
	if (aimingComponent->GetFireState() == EFiringState::Locked)
	{
		aimingComponent->Fire(); // TODO limit firing rate
	}
	
}
