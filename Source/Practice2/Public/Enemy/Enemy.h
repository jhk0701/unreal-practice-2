#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Enemy.generated.h"

UCLASS()
class PRACTICE2_API AEnemy : public AActor
{
	GENERATED_BODY()
	
public:	
	AEnemy();	
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = SubComp)
	TObjectPtr<USceneComponent> Root;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SubComp)
	TObjectPtr<class UBoxComponent> Col;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SubComp)
	TObjectPtr<UStaticMeshComponent> Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effect)
	TObjectPtr<class UParticleSystem> DestroyParticle;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
	float MaxHealth;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stat)
	float CurHealth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
	float Damage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat|Move")
	float MoveSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat|Move")
	float TraceRate;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stat|Move")
	FVector Direction;

	virtual void BeginPlay() override;
	virtual void Destroyed() override;
	void Move(float DeltaTime);

	UFUNCTION()
	void OnOverlapBegin(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);
};
