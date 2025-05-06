#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FireSystemComponent.generated.h"

class UArrowComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PRACTICE2_API UFireSystemComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UFireSystemComponent();
	void Fire();
	void SetFirePoint(UArrowComponent* InArrow);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Projectile)
	TSubclassOf<class AProjectileBase> ProjectileClass;
	TObjectPtr<UArrowComponent> FirePoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Setting)
	float CooldownTime; 
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Setting)
	float CurCooldown;
	
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction);
};
