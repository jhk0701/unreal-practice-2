// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MoveComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PRACTICE2_API UMoveComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UMoveComponent();
	void SetMoveInput(const FVector2D& Direction);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Setting)
	float Speed;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Input)
	FVector2D Input;

	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction);

private:
	AActor* Owner;
	void Move(float DeltaTime);
};
