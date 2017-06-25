// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Projectile.h"


// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// No need to protect pointers as added at construction
	ProjectileComponent = CreateDefaultSubobject<UProjectileMovementComponent>(FName("Projectile Movement"));
	if (ProjectileComponent)
	{
		ProjectileComponent->bAutoActivate = false;
	}

}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectile::LaunchProjectile(float Speed)
{
	float time = GetWorld()->GetTimeSeconds();
	UE_LOG(LogTemp, Warning, TEXT("%f LaunchProjectile at Speed %f"), time, Speed);

	ProjectileComponent->SetVelocityInLocalSpace(FVector::ForwardVector * Speed);
	ProjectileComponent->Activate();
}

