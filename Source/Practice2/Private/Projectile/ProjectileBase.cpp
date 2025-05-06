#include "Projectile/ProjectileBase.h"
#include "Components/BoxComponent.h"
#include "ShootingGameMode.h"

// Sets default values
AProjectileBase::AProjectileBase()
{
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));
	SetRootComponent(Root);

	Col = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
	Col->SetupAttachment(Root);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Col);

	MoveSpeed = 1000.f;
	Damage = 100.f;
	LifeTime = 5.f;

	Col->OnComponentBeginOverlap.AddDynamic(this, &AProjectileBase::OnOverlapBegin);
}

void AProjectileBase::BeginPlay()
{
	Super::BeginPlay();
	ElapsedTime = 0.0f;
}

void AProjectileBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ElapsedTime += DeltaTime;
	if (ElapsedTime >= LifeTime)
	{
		Release();
		return;
	}

	Move(DeltaTime);
}

void AProjectileBase::Move(float DeltaTime)
{
	const FVector Location = GetActorLocation() + MoveSpeed * DeltaTime * GetActorForwardVector();
	SetActorLocation(Location);
}

void AProjectileBase::Release()
{
	Destroy();
}


void AProjectileBase::OnOverlapBegin(
	UPrimitiveComponent* OverlappedComponent, 
	AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, 
	int32 OtherBodyIndex, 
	bool bFromSweep, 
	const FHitResult& SweepResult)
{
	// 앞선 옵션에서 Enemy와 충돌하도록 설정됨.
	if (OtherActor)
	{
		OtherActor->Destroy();

		if (AShootingGameMode* GameMode = Cast<AShootingGameMode>(GetWorld()->GetAuthGameMode())) 
			GameMode->AddScore(10);
	}

	Release();
}

