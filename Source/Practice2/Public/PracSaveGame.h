// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "Kismet/GameplayStatics.h"
#include "PracSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class PRACTICE2_API UPracSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	UPracSaveGame();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data|Profile")
	FString SlotName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data|Profile")
	int32 UserIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data|Score")
	int32 BestScore;

	void SaveData(int32 InScore, const FAsyncSaveGameToSlotDelegate& Callback);
	void LoadData(const FAsyncLoadGameFromSlotDelegate& Callback);
	
};
