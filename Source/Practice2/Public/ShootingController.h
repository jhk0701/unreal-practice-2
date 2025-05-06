// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ShootingController.generated.h"

class UInputAction;
class UButton;
class UTextBlock;

/**
 * 
 */
UCLASS()
class PRACTICE2_API AShootingController : public APlayerController
{
	GENERATED_BODY()

public:
	AShootingController();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	TObjectPtr<class UInputMappingContext> InputMap;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input|Action")
	TObjectPtr<UInputAction> MoveAction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input|Action")
	TObjectPtr<UInputAction> FireAction;

	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI|Main")
	TSubclassOf<UUserWidget> HUDMain;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI|Main")
	TObjectPtr<UUserWidget> HUDMainInstance;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI|Main|Element")
	TObjectPtr<UTextBlock> TxtScore;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI|Main|Element")
	TObjectPtr<UTextBlock> TxtBestScore;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI|GameOver")
	TSubclassOf<UUserWidget> HUDGameOver;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI|GameOver")
	TObjectPtr<UUserWidget> HUDGameOverInstance;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI|GameOver|Element")
	TObjectPtr<UButton> BtnRestart;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI|GameOver|Element")
	TObjectPtr<UButton> BtnExit;

	UFUNCTION()
	void UpdateScoreHUD(int32 Point);
	void UpdateBestScoreHUD(int32 Point);
	UFUNCTION()
	void ShowGameOverHUD();
};
