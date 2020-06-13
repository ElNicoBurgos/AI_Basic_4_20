// Fill out your copyright notice in the Description page of Project Settings.

#include "MyCharacter.h"
#include "Components/InputComponent.h"
#include "Engine/World.h"
#include "Camera/CameraComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "DrawDebugHelpers.h"
#include "TimerManager.h"
#include "Enemy.h"
#include "Pared.h"
#include "Interfaces/MyInterfaceDamageable.h"
#include "Interfaces/HealInterface.h"
#include "SceneComponent/SceneComponentBala.h"
// Sets default values
AMyCharacter::AMyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	cam = CreateDefaultSubobject<UCameraComponent>("CameraPlayer");
	arms = CreateDefaultSubobject<USkeletalMeshComponent>("Arms");
	gun = CreateDefaultSubobject<USkeletalMeshComponent>("Gun");
	shootSceneComponent = CreateDefaultSubobject<USceneComponentBala>("Shoot");
	cam->SetupAttachment(GetRootComponent());	
	shootSceneComponent->SetupAttachment(cam);
	arms->SetupAttachment(cam);
	gun->SetupAttachment(arms, "GripPoint");
	cam->bUsePawnControlRotation = true;
}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("Foward", this, &AMyCharacter::MoveFoward);
	PlayerInputComponent->BindAxis("Right", this, &AMyCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &AMyCharacter::RotateYaw);
	PlayerInputComponent->BindAxis("LookUp", this, &AMyCharacter::RotatePitch);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AMyCharacter::StartJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AMyCharacter::StopJump);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AMyCharacter::StartShoot);
	PlayerInputComponent->BindAction("Fire", IE_Released, this, &AMyCharacter::StopShoot);
	PlayerInputComponent->BindAction("Fire2", IE_Pressed, this, &AMyCharacter::StartShoot2);
	PlayerInputComponent->BindAction("Fire2", IE_Released, this, &AMyCharacter::StopShoot2);
}

void AMyCharacter::MoveFoward(float value){
	AddMovementInput(GetActorForwardVector(), value);
}
void AMyCharacter::MoveRight(float value){
	AddMovementInput(GetActorRightVector(), value);
}
void AMyCharacter::RotateYaw(float value) {
	AddControllerYawInput(value*velRot*GetWorld()->GetDeltaSeconds());
}
void AMyCharacter::RotatePitch(float value) {
	AddControllerPitchInput(value*velRot*GetWorld()->GetDeltaSeconds());
}
void AMyCharacter::StartJump(){
	Jump();
}
void AMyCharacter::StopJump(){
	StopJumping();
}
void AMyCharacter::StartShoot() {
	GetWorldTimerManager().SetTimer(handleShoot, this, &AMyCharacter::ShootTimer, true, 0.267);
	/*FHitResult hitInfo;
	bool hasHit =
		GetWorld()->LineTraceSingleByChannel(hitInfo,
			cam->GetComponentLocation(),
			cam->GetComponentLocation() + cam->GetForwardVector() * 1000,
			ECC_GameTraceChannel3);
	
	DrawDebugLine(GetWorld(),
		cam->GetComponentLocation(),
		cam->GetComponentLocation() + cam->GetForwardVector() * 1000,
		FColor::Red,
		false,
		3);
	if (hasHit && hitInfo.GetActor())
		hitInfo.GetActor()->Destroy();*/
}
void AMyCharacter::ShootTimer(){
	/*FHitResult hitInfo;
	bool hasHit =
		GetWorld()->LineTraceSingleByChannel(hitInfo,
			cam->GetComponentLocation(),
			cam->GetComponentLocation() + cam->GetForwardVector() * 1000,
			ECC_GameTraceChannel3);
	if (hasHit && hitInfo.GetActor()) {
		AEnemy* myEnemy = Cast<AEnemy>(hitInfo.GetActor());
		//hitInfo.GetActor()->Destroy();
		if (myEnemy && damageList.Contains(hitInfo.BoneName)) {
			float damage = damageList[hitInfo.BoneName];
			float totalDamage = damage * damageGun;
			myEnemy->life -= totalDamage;
			UE_LOG(LogTemp, Warning, TEXT("BoneName: %s"), *hitInfo.BoneName.ToString());
			UE_LOG(LogTemp, Warning, TEXT("Percent Damage: %f"), damage);
			UE_LOG(LogTemp, Warning, TEXT("Total Damage: %f"), totalDamage);
			UE_LOG(LogTemp, Warning, TEXT("Life Enemy: %f"), myEnemy->life);
		}		
	}*/
	shootSceneComponent->Shoot(1, 0);
}
void AMyCharacter::StopShoot() {
	GetWorldTimerManager().ClearTimer(handleShoot);
}

void AMyCharacter::StartShoot2() {
	GetWorldTimerManager().SetTimer(handleShoot2, this, &AMyCharacter::ShootTimer2, true, 0.267);
}
void AMyCharacter::ShootTimer2() {
	//Shoot(10, 100);
	Heal();
}
void AMyCharacter::StopShoot2() {
	GetWorldTimerManager().ClearTimer(handleShoot2);
}

//void AMyCharacter::Shoot(int amount, float shakes) {
//	float currentDamage = damageGun;
//	TArray <FHitResult> hitInfoArray;
//	FVector vectorShake;
//	for (int i = 0; i < amount; i++) {
//		vectorShake.X = FMath::RandRange(-shakes, shakes);
//		vectorShake.Y = FMath::RandRange(-shakes, shakes);
//		vectorShake.Z = FMath::RandRange(-shakes, shakes);
//		GetWorld()->LineTraceMultiByChannel(hitInfoArray,
//			cam->GetComponentLocation(),
//			cam->GetComponentLocation() + GetForwardVector() * 1000 + vectorShake,
//			ECC_GameTraceChannel3);
//
//		DrawDebugLine(GetWorld(),
//			cam->GetComponentLocation(),
//			cam->GetComponentLocation() + cam->GetForwardVector() * 1000 + vectorShake,
//			FColor::Red,
//			false,
//			3);
//		TArray <AActor*> hitActors;
//		for (int i = 0; i < hitInfoArray.Num(); i++) {
//			FHitResult hitInfo = hitInfoArray[i];
//			if (hitInfo.GetActor() && !(hitActors.Contains(hitInfo.GetActor()))) {
//				hitActors.Add(hitInfo.GetActor());
//				
//				IMyInterfaceDamageable* damageable = Cast<IMyInterfaceDamageable>(hitInfo.GetActor());
//				if (damageable != nullptr) {
//					
//					damageable->TakeDamage(hitInfo.BoneName, currentDamage);
//				}
//				APared* myPared = Cast<APared>(hitInfo.GetActor());
//				if (myPared != nullptr) {
//					currentDamage -= myPared->danoAAbsorver;
//				}
//			}
//		}
//	}
//}

void AMyCharacter::Heal() {

	FHitResult hitInfo;
	bool hasHit =
		GetWorld()->LineTraceSingleByChannel(hitInfo,
			cam->GetComponentLocation(),
			cam->GetComponentLocation() + cam->GetForwardVector() * 1000,
			ECC_GameTraceChannel3);

	DrawDebugLine(GetWorld(),
		cam->GetComponentLocation(),
		cam->GetComponentLocation() + cam->GetForwardVector() * 1000,
		FColor::Green,
		false,
		3);
	
	if (hitInfo.GetActor()) {
		UE_LOG(LogTemp, Warning, TEXT("Hit heal"));
		IHealInterface* healeable = Cast<IHealInterface>(hitInfo.GetActor());
		if (healeable != nullptr) {
			healeable->ZoneHealt(amountHeal);
		}
	}


}
