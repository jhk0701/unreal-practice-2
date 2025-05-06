// Fill out your copyright notice in the Description page of Project Settings.
#include "Enemy/EnemyFactory.h"
#include "TimerManager.h"
#include "Enemy/Enemy.h"

// Sets default values
AEnemyFactory::AEnemyFactory()
{
	PrimaryActorTick.bCanEverTick = false;

	DelayRange = FVector2D(1.0f, 3.0f);
	DelayTime = 1.f;
}


void AEnemyFactory::BeginPlay()
{
	Super::BeginPlay();
	
	DelayTime = FMath::FRandRange(DelayRange.X, DelayRange.Y);

	GetWorldTimerManager().SetTimer(
		SpawnTimer,
		this,
		&AEnemyFactory::Spawn,
		DelayTime,  
		true);
}

void AEnemyFactory::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	GetWorldTimerManager().ClearTimer(SpawnTimer);

	Super::EndPlay(EndPlayReason);
}


void AEnemyFactory::Spawn()
{
	if (!EnemyClass)
		return;

	GetWorld()->SpawnActor(EnemyClass, &GetActorTransform(), FActorSpawnParameters());
}
