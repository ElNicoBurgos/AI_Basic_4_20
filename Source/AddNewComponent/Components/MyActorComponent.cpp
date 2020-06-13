// Fill out your copyright notice in the Description page of Project Settings.

#include "MyActorComponent.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
UMyActorComponent::UMyActorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMyActorComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
//void UMyActorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
//{
//	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
//
//	// ...
//}
void UMyActorComponent::TakeDamage(FName boneName, float currentDamage) {
	if (damageList.Contains(boneName)) {
		float damage = damageList[boneName];
		UE_LOG(LogTemp, Warning, TEXT("Damagelist: %f"), damage);
		float totalDamage = damage * currentDamage;
		life -= totalDamage;
	}
	if (life < 0)
		GetOwner()->Destroy();
	UE_LOG(LogTemp, Warning, TEXT("Life Enemy: %f"), life);
}
void UMyActorComponent::ZoneHealt(float amountHealt) {
	if (life < lifeMax) {
		if ((life + amountHealt) > lifeMax)
			life = lifeMax;
		else
			life += amountHealt;
	}
	UE_LOG(LogTemp, Warning, TEXT("%f"), life);
}

