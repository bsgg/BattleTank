// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAimingComponent.h"
#include "TankAIController.h"
#include "Tank.h" // We can implement OnDeath


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);

	if (InPawn)
	{
		auto possessedTank = Cast<ATank>(InPawn);
		if (!possessedTank)
		{
			return;
		}

		// Suscribe our local method ot the tank's death event
		possessedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnPossedTankDeath);
	}
}

void  ATankAIController::OnPossedTankDeath()
{
	UE_LOG(LogTemp, Warning, TEXT("[ ATankAIController::OnPossedTankDeath] %s "), *GetName());
	// Call this function to detach safely pawn from its controller, knowing that we will be destroyed soon.
	if (GetPawn())
	{
		GetPawn()->DetachFromControllerPendingDestroy();
	}
	

}


// Called every frame
void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto ControlledTank = GetPawn();

	if (!PlayerTank && ControlledTank) { return; }
	
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
