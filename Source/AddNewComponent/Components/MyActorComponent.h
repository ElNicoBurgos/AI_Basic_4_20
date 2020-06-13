// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MyActorComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ADDNEWCOMPONENT_API UMyActorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMyActorComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame}
	UPROPERTY(EditAnywhere) float life = 100;
	UPROPERTY(EditAnywhere) float lifeMax = 100;
	UPROPERTY(EditAnywhere) TMap<FName, float> damageList;
	//virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void TakeDamage(FName boneName, float currentDamage);
	void ZoneHealt(float amountHealt);
};
