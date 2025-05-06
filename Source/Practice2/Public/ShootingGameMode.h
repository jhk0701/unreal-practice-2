// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ShootingGameMode.generated.h"

DECLARE_EVENT(AShootingGameMode, FOnGameOver);
DECLARE_EVENT_OneParam(AShootingGameMode, FOnScoreChanged, int32);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnBestScoreChanged, int32);

/**
 * 
 */
UCLASS()
class PRACTICE2_API AShootingGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AShootingGameMode();

	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Score)
	int32 CurrentScore;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Score)
	int32 BestScore;

	FOnScoreChanged OnScoreChanged;
	FOnBestScoreChanged OnBestScoreChanged;
	FOnGameOver OnGameOver;

	void AddScore(int32 Point);
	void UpdateBestScore();

	void CallGameOver();

	UFUNCTION()
	void Restart();
	UFUNCTION()
	void Exit();

	void LoadData();

};
