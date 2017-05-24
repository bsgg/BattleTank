// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAIController.h"



void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	auto ControllerTank = GetControlledTank();
	if (!ControllerTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("AITankPlayerController not possesing the tank!!!"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AITankPlayerController  possesing: %s"), *ControllerTank->GetName());
	}
}


ATank* ATankAIController::GetControlledTank() const
{
	ATank* tank = Cast<ATank>(GetPawn());
	return  tank;
}


