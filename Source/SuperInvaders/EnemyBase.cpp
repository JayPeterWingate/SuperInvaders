// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyBase.h"

#include "Bullet.h"
#include "HealthComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/PoseableMeshComponent.h"
#include "Components/SplineComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AEnemyBase::AEnemyBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;
	Mesh = CreateDefaultSubobject<UPoseableMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);
	

	Collider = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Collider"));
	Collider->SetupAttachment(Root);
	Collider->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health"));
	HealthComponent->SetTeam(Invader);
}

// Called when the game starts or when spawned
void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();
	StartTime = GetWorld()->GetTimeSeconds();
	bCanMove = true;	
}

// Called every frame
void AEnemyBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(!HasAuthority() || !bCanMove || Path == nullptr) return;
	
	const float CurrentTime = ((GetWorld()->GetTimeSeconds() - StartTime)/ Path->Duration) * Speed;
	const float Distance = Path->GetSplineLength() * CurrentTime;

	const FVector Position = Path->GetLocationAtDistanceAlongSpline(Distance, ESplineCoordinateSpace::World);
	const FVector Direction = Path->GetDirectionAtDistanceAlongSpline(Distance, ESplineCoordinateSpace::World);
	const FRotator Rotator = FRotationMatrix::MakeFromX(Direction).Rotator();

	SetActorLocation(Position);
	SetActorRotation(Rotator);

	if(CurrentTime >= 1)
		GoalHit();
		
}

void AEnemyBase::SetPath(USplineComponent* Spline)
{
	Path = Spline;
}

int AEnemyBase::GetDamage() const
{
	return Damage;
}

void AEnemyBase::GoalHit()
{
	auto GameMode = Cast<ASuperInvadersGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	if(GameMode == nullptr)
		return;
	GameMode->TakeLives(this);
}

