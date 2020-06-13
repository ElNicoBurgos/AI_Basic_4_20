// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/MyInterfaceDamageable.h"
#include "Interfaces/HealInterface.h"
#include "Enemy.generated.h"

UCLASS()
class ADDNEWCOMPONENT_API AEnemy : public ACharacter, public IMyInterfaceDamageable,public IHealInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite) class UMyActorComponent* life;
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void TakeDamage(FName boneName, float currentDamage) override;
	void ZoneHealt(float amountHealt) override;
};
