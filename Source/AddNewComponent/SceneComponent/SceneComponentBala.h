// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "SceneComponentBala.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ADDNEWCOMPONENT_API USceneComponentBala : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USceneComponentBala();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	UPROPERTY(EditAnywhere) float damageGun = 25;
	void Shoot(int amount, float shakes);
	
};
