// Fill out your copyright notice in the Description page of Project Settings.
#include "Enemy/Enemy.h"
#include "ShootingController.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AEnemy::AEnemy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	Col = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
	Col->SetupAttachment(Root);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Col);

	MaxHealth = 100.f;
	CurHealth = MaxHealth;
	Damage = 100.f;
	MoveSpeed = 300.f;
	TraceRate = 0.35f;

	Col->OnComponentBeginOverlap.AddDynamic(this, &AEnemy::OnOverlapBegin);
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();

	CurHealth = MaxHealth;

	float Rate = FMath::FRand();
	if (Rate <= TraceRate) 
	{
		APawn* pawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
		if (pawn)
		{
			Direction = pawn->GetActorLocation() - GetActorLocation();
			Direction = Direction.GetSafeNormal();
			
			SetActorRotation(Direction.Rotation());

			return;
		}
	}
	
	Direction = GetActorForwardVector();
}

void AEnemy::Destroyed()
{
	if(DestroyParticle)
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), DestroyParticle, GetActorTransform());
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Move(DeltaTime);
}

void AEnemy::Move(float DeltaTime)
{
	const FVector Location = GetActorLocation() + DeltaTime * MoveSpeed * Direction;
	SetActorLocation(Location);
}

void AEnemy::OnOverlapBegin(
	UPrimitiveComponent* OverlappedComponent, 
	AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, 
	int32 OtherBodyIndex, 
	bool bFromSweep, 
	const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor->ActorHasTag("Player"))
	{
		OtherActor->Destroy();
		Destroy();
	}
}
