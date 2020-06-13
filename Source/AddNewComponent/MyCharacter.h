// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/MyActorComponent.h"
#include "MyCharacter.generated.h"

UCLASS()
class ADDNEWCOMPONENT_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	FTimerHandle handleShoot;
	FTimerHandle handleShoot2;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite) class USceneComponentBala* shootSceneComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite) class UCameraComponent* cam;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite) class USkeletalMeshComponent* arms;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite) class USkeletalMeshComponent* gun;

	UPROPERTY(EditAnywhere) float life = 100;
	UPROPERTY(EditAnywhere) float damageGun = 25;
	UPROPERTY(EditAnywhere) float currentDamage;

	UPROPERTY(EditAnywhere) float amountHeal;
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	UPROPERTY(EditAnywhere)
	float velRot = 40;
	void MoveFoward(float value);
	void MoveRight(float value);
	void RotateYaw(float value);
	void RotatePitch(float value);
	void StartJump();
	void StopJump();

	void StartShoot();
	void ShootTimer();
	void StopShoot();
	
	void StartShoot2();
	void ShootTimer2();
	void StopShoot2();

	//void Shoot(int amount, float shakes);
	void Heal();

};
