// Fill out your copyright notice in the Description page of Project Settings.
#include "Character/FireSystemComponent.h"
#include "Components/ArrowComponent.h"
#include "Projectile/ProjectileBase.h"

// Sets default values for this component's properties
UFireSystemComponent::UFireSystemComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	CooldownTime = 1.0f;
	CurCooldown = 0.0f;
}

void UFireSystemComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	if (CurCooldown >= 0.0f)
		CurCooldown -= DeltaTime;
}


void UFireSystemComponent::Fire()
{
	if (!ProjectileClass || !FirePoint || CurCooldown >= 0.f)
		return;
	
	GetWorld()->SpawnActor<AActor>(
		ProjectileClass,
		FirePoint->GetComponentLocation(), 
		FirePoint->GetComponentRotation(),
		FActorSpawnParameters());

	CurCooldown = CooldownTime;
}

void UFireSystemComponent::SetFirePoint(UArrowComponent* InArrow)
{
	FirePoint = InArrow;
}
