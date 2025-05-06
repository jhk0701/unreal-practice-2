#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TestActor.generated.h"

DECLARE_DELEGATE(FOnSingleDelegate);
DECLARE_DELEGATE_RetVal(int32, FOnAfterDamaged);

UCLASS()
class PRACTICE2_API ATestActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ATestActor();

	FOnSingleDelegate OnCharDead;

	FOnAfterDamaged OnAfterDamaged;

protected:
	virtual void BeginPlay() override;

};
