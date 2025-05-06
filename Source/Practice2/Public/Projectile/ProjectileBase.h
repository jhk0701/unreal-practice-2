#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjectileBase.generated.h"

UCLASS()
class PRACTICE2_API AProjectileBase : public AActor
{
	GENERATED_BODY()
	
public:	
	AProjectileBase();
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = SubComp)
	TObjectPtr<USceneComponent> Root;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = SubComp)
	TObjectPtr<class UBoxComponent> Col;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SubComp)
	TObjectPtr<UStaticMeshComponent> Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Setting)
	float MoveSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Setting)
	float Damage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Setting)
	float LifeTime;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Setting)
	float ElapsedTime;

	void Move(float DeltaTime);
	void Release();
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnOverlapBegin(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);
};
