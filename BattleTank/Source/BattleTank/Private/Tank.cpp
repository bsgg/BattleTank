// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Tank.h"



// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;    
}

float ATank::GetHealthPercent() const
{
	return (float)CurrentHealth / (float)StartingHealth;
}


float ATank::TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser)
{
	int32 damagePoints = FPlatformMath::RoundToInt(DamageAmount);

	int32 damageToApply = FMath::Clamp(damagePoints, 0, CurrentHealth);

	CurrentHealth -= damageToApply;


	UE_LOG(LogTemp, Warning, TEXT("[ATank::TakeDamage] %s: damagePoints %i, damageToApply: %i, CurrentHealth: %i"), *GetName(), damagePoints, damageToApply, CurrentHealth);


	if (CurrentHealth <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("[ATank::TakeDamage] Tank Dead %s "), *GetName());
	}

	return damageToApply;
}