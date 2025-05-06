// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemyFactory.generated.h"

UCLASS()
class PRACTICE2_API AEnemyFactory : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemyFactory();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Setting)
	TSubclassOf<class AEnemy> EnemyClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setting|DelayTime")
	FVector2D DelayRange;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Setting|DelayTime")
	float DelayTime;

	FTimerHandle SpawnTimer;

	void Spawn();
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

};
