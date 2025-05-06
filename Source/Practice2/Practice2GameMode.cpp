// Copyright Epic Games, Inc. All Rights Reserved.

#include "Practice2GameMode.h"
#include "Practice2Character.h"
#include "UObject/ConstructorHelpers.h"

APractice2GameMode::APractice2GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
