// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemySpawner.h"
#include "Engine/World.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AEnemySpawner::AEnemySpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEnemySpawner::BeginPlay()
{
	Super::BeginPlay();
	int lenghtArraySpawn = spawns.Num();

	int spawnRandom;
	
	int lenghtArrayActor = enemyActor.Num();
	int enemyRandom;
	UE_LOG(LogTemp, Warning, TEXT("%d"), lenghtArraySpawn);
	for (int i = 0; i < cantSpawns; i++){	
		
		spawnRandom = FMath::FRandRange(0, lenghtArraySpawn);
		UE_LOG(LogTemp, Warning, TEXT("%d"), spawnRandom);
		enemyRandom = FMath::FRandRange(0, lenghtArrayActor);
		GetWorld()->SpawnActor<AActor>(enemyActor[enemyRandom], spawns[spawnRandom]->GetTransform());
	
	}
	

	//GetWorld()->SpawnActor<AActor *>(enemyActor, actorSpawns[spawnRandom].GetActorLocation(),
		//actorSpawns[spawnRandom].GetActorRotation());
}

// Called every frame
void AEnemySpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

