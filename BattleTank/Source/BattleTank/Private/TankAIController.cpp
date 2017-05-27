// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAIController.h"



void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	auto playerTank = GetPlayerTank();
	if (!playerTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("ATankAIController can't find player tank"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("ATankAIController found player: %s"), *playerTank->GetName());
	}	
}


ATank* ATankAIController::GetControlledTank() const
{
	ATank* tank = Cast<ATank>(GetPawn());
	return  tank;
}

ATank* ATankAIController::GetPlayerTank() const
{
	auto playerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();

	if (!playerPawn)
	{
		return nullptr;
	}
	else
	{
		return Cast<ATank>(playerPawn);
	}

}


