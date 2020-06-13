// Fill out your copyright notice in the Description page of Project Settings.

#include "SceneComponentBala.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "Pared.h"
#include "Interfaces/MyInterfaceDamageable.h"

// Sets default values for this component's properties
USceneComponentBala::USceneComponentBala()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USceneComponentBala::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void USceneComponentBala::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void USceneComponentBala::Shoot(int amount, float shakes) {
	float currentDamage = damageGun;
	TArray <FHitResult> hitInfoArray;
	FVector vectorShake;
	for (int i = 0; i < amount; i++) {
		vectorShake.X = FMath::RandRange(-shakes, shakes);
		vectorShake.Y = FMath::RandRange(-shakes, shakes);
		vectorShake.Z = FMath::RandRange(-shakes, shakes);
		GetWorld()->LineTraceMultiByChannel(hitInfoArray,
			GetComponentLocation(),
			GetComponentLocation() + GetForwardVector() * 1000 + vectorShake,
			ECC_GameTraceChannel3);

		DrawDebugLine(GetWorld(),
			GetComponentLocation(),
			GetComponentLocation() + GetForwardVector() * 1000 + vectorShake,
			FColor::Red,
			false,
			3);
		TArray <AActor*> hitActors;
		for (int i = 0; i < hitInfoArray.Num(); i++) {
			FHitResult hitInfo = hitInfoArray[i];
			if (hitInfo.GetActor() && !(hitActors.Contains(hitInfo.GetActor()))) {
				hitActors.Add(hitInfo.GetActor());

				IMyInterfaceDamageable* damageable = Cast<IMyInterfaceDamageable>(hitInfo.GetActor());
				if (damageable != nullptr) {

					damageable->TakeDamage(hitInfo.BoneName, currentDamage);
				}
				APared* myPared = Cast<APared>(hitInfo.GetActor());
				if (myPared != nullptr) {
					currentDamage -= myPared->danoAAbsorver;
				}
			}
		}
	}
}

