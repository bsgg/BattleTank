// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "TankAIController.generated.h"


/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
protected:
	// How close can the AI tank get 
	UPROPERTY(EditDefaultsOnly, Category = "Setup") // Consider EditDefaultsOnly
	float AcceptanceRadius = 8000;

	// Method to suscribe the event delegate OnDeath form Tank.h
	UFUNCTION()
		void OnPossedTankDeath();


private:
	virtual void BeginPlay() override;

	// Override Setter for Pawn. This function is called when  possessing/unpossessing a Pawn.
	virtual void SetPawn(APawn* InPawn) override;

	virtual void Tick(float DeltaSeconds) override;

	
	
};
