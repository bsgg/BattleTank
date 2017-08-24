// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTrack.h"

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = true;	
}

void UTankTrack::BeginPlay()
{
	// On Hit events
	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

void UTankTrack::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	UE_LOG(LogTemp, Warning, TEXT("I'm hit, I'm hit"));
}

void UTankTrack::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
	//Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//UE_LOG(LogTemp, Warning, TEXT("UTankTrack::TickComponent"));

	// Calculate the slippage speed
	float slippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());

	
	// Work out required acceleration this frame to correct
	FVector correctionAcceleration = -slippageSpeed / DeltaTime * GetRightVector();

	// Calculate and apply sidewasy for (F = m * a)
	auto tankRoot =  Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	auto correctionForce = (tankRoot->GetMass() * correctionAcceleration) / 2; // There are 2 tracks
	tankRoot->AddForce(correctionForce);

}

void UTankTrack::SetThrottle(float Throttle)
{

	auto foreApplied = GetForwardVector() * Throttle * TrackMaxDrivingForce;
	auto forceLocation = GetComponentLocation();
	auto tankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	tankRoot->AddForceAtLocation(foreApplied, forceLocation);
}