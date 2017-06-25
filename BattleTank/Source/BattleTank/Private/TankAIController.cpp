// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Tank.h"
#include "TankAIController.h"



void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto playerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (playerTank)
	{
		ATank * controllerTank = Cast<ATank>(playerTank);
		if (controllerTank)
		{
			//float time = GetWorld()->GetTimeSeconds();
			//UE_LOG(LogTemp, Warning, TEXT("%f Player tank controller found"), time);
			
			controllerTank->AimAt(playerTank->GetActorLocation());

			//controllerTank->Fire(); 

		}
	}

}



