// Fill out your copyright notice in the Description page of Project Settings.
#include "ShootingGameMode.h"
#include "PracSaveGame.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

AShootingGameMode::AShootingGameMode()
{
	CurrentScore = 0;
	BestScore = 0;
}

void AShootingGameMode::BeginPlay()
{
	Super::BeginPlay();

	LoadData();
}

void AShootingGameMode::AddScore(int32 Point)
{
	CurrentScore += Point;

	if (OnScoreChanged.IsBound()) 
		OnScoreChanged.Broadcast(CurrentScore); 

	UpdateBestScore();
}

void AShootingGameMode::UpdateBestScore()
{
	if (BestScore < CurrentScore)
	{
		BestScore = CurrentScore;
		OnBestScoreChanged.Broadcast(BestScore);
	}
}

void AShootingGameMode::CallGameOver()
{
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Cyan, TEXT("Game Over"));

	if (OnGameOver.IsBound())
		OnGameOver.Broadcast();
}

void AShootingGameMode::Restart()
{
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Cyan, TEXT("Restart clicked"));
	UGameplayStatics::OpenLevel(GetWorld(), FName(TEXT("MainLevel")));
}

void AShootingGameMode::Exit()
{
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Cyan, TEXT("Exit clicked"));
	
	UWorld* World = GetWorld();

	if (UPracSaveGame* GameData = Cast<UPracSaveGame>(UGameplayStatics::CreateSaveGameObject(UPracSaveGame::StaticClass())))
	{
		FAsyncSaveGameToSlotDelegate Callback;
		Callback.BindWeakLambda(this, [World](const FString& SlotName, const int32 UserIdx, bool bIsIgnore)
			{
				UE_LOG(LogTemp, Warning, TEXT("Quit Game"));
				UKismetSystemLibrary::QuitGame(World, World->GetFirstPlayerController(), EQuitPreference::Quit, true);
			});

		GameData->SaveData(BestScore, Callback);
	}
	else 
	{
		UE_LOG(LogTemp, Warning, TEXT("Quit Game without saving"));
		UKismetSystemLibrary::QuitGame(World, World->GetFirstPlayerController(), EQuitPreference::Quit, true);
	}	
}

void AShootingGameMode::LoadData()
{
	if (UPracSaveGame* GameData = Cast<UPracSaveGame>(UGameplayStatics::CreateSaveGameObject(UPracSaveGame::StaticClass()))) 
	{
		FAsyncLoadGameFromSlotDelegate Callback;

		Callback.BindWeakLambda(this, [this](const FString& SlotName, const int32 UserIdx, USaveGame* GameData)
			{
				if (UPracSaveGame* Loaded = Cast<UPracSaveGame>(GameData)) 
				{
					this->BestScore = Loaded->BestScore;
					this->OnBestScoreChanged.Broadcast(this->BestScore);
				}
				
			});

		GameData->LoadData(Callback);
	}
}

