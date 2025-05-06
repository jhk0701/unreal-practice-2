#include "ShootingController.h"
#include "EnhancedInputSubsystems.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "ShootingGameMode.h"

AShootingController::AShootingController()
{
}

void AShootingController::BeginPlay()
{
	Super::BeginPlay();

	ULocalPlayer* LocalPlayer = GetLocalPlayer();
	
	if (!LocalPlayer) 
		return;
	
	UEnhancedInputLocalPlayerSubsystem* InputSystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();

	if (!InputSystem) 
		return;

	if (InputMap)
		InputSystem->AddMappingContext(InputMap, 0);

	if (HUDMain) 
	{
		HUDMainInstance = CreateWidget(this, HUDMain);
		HUDMainInstance->AddToViewport();
		
		TxtScore = Cast<UTextBlock>(HUDMainInstance->GetWidgetFromName(TEXT("ScoreData")));
		TxtBestScore = Cast<UTextBlock>(HUDMainInstance->GetWidgetFromName(TEXT("BestScoreData")));

		AShootingGameMode* Mode = Cast<AShootingGameMode>(GetWorld()->GetAuthGameMode());
		if (Mode)
		{
			Mode->OnScoreChanged.AddUObject(this, &AShootingController::UpdateScoreHUD);
			Mode->OnBestScoreChanged.AddUObject(this, &AShootingController::UpdateBestScoreHUD);
		}
	}

	if (HUDGameOver) 
	{
		HUDGameOverInstance = CreateWidget(this, HUDGameOver);

		BtnRestart = Cast<UButton>(HUDGameOverInstance->GetWidgetFromName(TEXT("ButtonRestart")));
		BtnExit = Cast<UButton>(HUDGameOverInstance->GetWidgetFromName(TEXT("ButtonExit")));

		if (AShootingGameMode* Mode = Cast<AShootingGameMode>(GetWorld()->GetAuthGameMode()))
		{
			Mode->OnGameOver.AddUObject(this, &AShootingController::ShowGameOverHUD);

			if (BtnRestart)
				BtnRestart->OnClicked.AddUniqueDynamic(Mode, &AShootingGameMode::Restart);

			if (BtnExit)
				BtnExit->OnClicked.AddUniqueDynamic(Mode, &AShootingGameMode::Exit);
		}
	}
}

void AShootingController::UpdateScoreHUD(int32 Point)
{
	if (!TxtScore) return;

	TxtScore->SetText(FText::FromString(FString::Printf(TEXT("%d"), Point)));
}

void AShootingController::UpdateBestScoreHUD(int32 Point)
{
	if (!TxtBestScore) return;

	TxtBestScore->SetText(FText::FromString(FString::Printf(TEXT("%d"), Point)));
}

void AShootingController::ShowGameOverHUD()
{
	HUDMainInstance->RemoveFromViewport();
	HUDGameOverInstance->AddToViewport();
}
