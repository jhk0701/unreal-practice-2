// Fill out your copyright notice in the Description page of Project Settings.
#include "Character/ShootingPawn.h"
#include "Character/FireSystemComponent.h"
#include "Character/MoveComponent.h"
#include "EnhancedInputComponent.h"
#include "ShootingController.h"
#include "ShootingGameMode.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AShootingPawn::AShootingPawn()
{
	PrimaryActorTick.bCanEverTick = false;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));
	SetRootComponent(Root);

	Col = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
	Col->SetupAttachment(Root);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	Mesh->SetupAttachment(Col);

	FirePoint = CreateDefaultSubobject<UArrowComponent>(TEXT("FirePoint"));
	FirePoint->SetupAttachment(Root);
	
	FireSys = CreateDefaultSubobject<UFireSystemComponent>(TEXT("FireSystem"));
	FireSys->SetFirePoint(FirePoint);

	MoveSys = CreateDefaultSubobject<UMoveComponent>(TEXT("MoveSystem"));
}

void AShootingPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

void AShootingPawn::Destroyed()
{
	Super::Destroyed();
	
	if (AShootingGameMode* GameMode = Cast<AShootingGameMode>(GetWorld()->GetAuthGameMode())) 
		GameMode->CallGameOver();
}



void AShootingPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* InputComp = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	AShootingController* ShootingController = Cast<AShootingController>(GetController());

	InputComp->BindAction(ShootingController->MoveAction, ETriggerEvent::Triggered, this, &AShootingPawn::Move);
	InputComp->BindAction(ShootingController->MoveAction, ETriggerEvent::Completed, this, &AShootingPawn::StopMove);
	InputComp->BindAction(ShootingController->FireAction, ETriggerEvent::Triggered, this, &AShootingPawn::Fire);
}


void AShootingPawn::Move(const FInputActionValue& InputValue)
{
	const FVector2D Input = InputValue.Get<FVector2D>();
	GEngine->AddOnScreenDebugMessage(0, 3.f, FColor::Blue, FString::Printf(TEXT("Move : %s"), *Input.ToString()));
	MoveSys->SetMoveInput(Input);
}

void AShootingPawn::StopMove(const FInputActionValue& InputValue)
{
	GEngine->AddOnScreenDebugMessage(0, 3.f, FColor::Purple, TEXT("Stop Move"));
	MoveSys->SetMoveInput(FVector2D::ZeroVector);
}

void AShootingPawn::Fire(const FInputActionValue& InputValue)
{
	GEngine->AddOnScreenDebugMessage(0, 3.f, FColor::Red, TEXT("Fire"));
	FireSys->Fire();
}