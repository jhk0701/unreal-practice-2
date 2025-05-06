// Fill out your copyright notice in the Description page of Project Settings.
#include "PracSaveGame.h"

UPracSaveGame::UPracSaveGame()
{
	SlotName = TEXT("DefaultSaveSlot");
	UserIndex = 0;
}

void UPracSaveGame::SaveData(int32 InScore, const FAsyncSaveGameToSlotDelegate& Callback)
{
	UE_LOG(LogTemp, Warning, TEXT("Save game data"));

	BestScore = InScore;

	// 비동기식 저장	
	UGameplayStatics::AsyncSaveGameToSlot(this, SlotName, UserIndex, Callback);

	// 동기식 저장
	/*
	if(UGameplayStatics::SaveGameToSlot(this, SlotName.ToString(), UserIndex))
	{

	}
	*/
	
}

void UPracSaveGame::LoadData(const FAsyncLoadGameFromSlotDelegate& Callback)
{
	if(UGameplayStatics::DoesSaveGameExist(SlotName, UserIndex))
	{
		// 비동기식 불러오기
		UGameplayStatics::AsyncLoadGameFromSlot(SlotName, UserIndex, Callback);
	}
	else
		Callback.ExecuteIfBound(SlotName, UserIndex, this);

	// 동기식 불러오기
	if (UPracSaveGame* SaveGame = Cast<UPracSaveGame>(UGameplayStatics::LoadGameFromSlot(SlotName, UserIndex)))
	{

	}
}

