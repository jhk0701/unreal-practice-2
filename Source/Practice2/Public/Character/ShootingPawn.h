#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "ShootingPawn.generated.h"

struct FInputActionValue;

UCLASS()
class PRACTICE2_API AShootingPawn : public APawn
{
	GENERATED_BODY()

public:
	AShootingPawn();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = SubComp)
	TObjectPtr<USceneComponent> Root;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SubComp)
	TObjectPtr<class UBoxComponent> Col;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SubComp)
	TObjectPtr<UStaticMeshComponent> Mesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = SubComp)
	TObjectPtr<class UFireSystemComponent> FireSys;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = FirePoint)
	TObjectPtr<class UArrowComponent> FirePoint;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = SubComp)
	TObjectPtr<class UMoveComponent> MoveSys;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	virtual void BeginPlay() override;
	virtual void Destroyed() override;

	UFUNCTION()
	void Move(const FInputActionValue& InputValue);
	UFUNCTION()
	void StopMove(const FInputActionValue& InputValue);
	UFUNCTION()
	void Fire(const FInputActionValue& InputValue);

};
