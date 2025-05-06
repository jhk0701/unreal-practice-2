// Fill out your copyright notice in the Description page of Project Settings.
#include "Character/MoveComponent.h"

// Sets default values for this component's properties
UMoveComponent::UMoveComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	Speed = 1000.0f;
}

void UMoveComponent::BeginPlay()
{
	Super::BeginPlay();
	Owner = GetOwner();	
}

void UMoveComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	Move(DeltaTime);
}


void UMoveComponent::SetMoveInput(const FVector2D& Direction)
{
	Input = Direction.GetSafeNormal(0.0001f);
}

void UMoveComponent::Move(float DeltaTime)
{
	const FVector Movement = Owner->GetActorLocation() +
		Input.X * Speed * DeltaTime * Owner->GetActorRightVector() +
		Input.Y * Speed * DeltaTime * Owner->GetActorForwardVector();

	Owner->SetActorLocation(Movement);
}

