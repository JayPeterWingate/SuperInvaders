// Fill out your copyright notice in the Description page of Project Settings.


#include "ShootyEnemy.h"
#include "Gun.h"
#include "Bullet.h"
#include "Components/PoseableMeshComponent.h"
#include "GameFramework/GameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

const FRotator AShootyEnemy::Direction = FRotator(0,180,0);

void AShootyEnemy::Shoot()
{
	if(Target == nullptr || FMath::RandBool()|| Cannon == nullptr) return;
	
	Cannon->Fire();
}

void AShootyEnemy::BeginPlay()
{
	Super::BeginPlay();
	
	
	auto world = GetWorld();
	if(world == nullptr)
		return;
	world->GetTimerManager().SetTimer(ShooterHandle, this, &AShootyEnemy::Shoot, FireRate, true, 0.0f);
	world->GetTimerManager().SetTimer(TargetingHandle, this, &AShootyEnemy::FindTarget, 0, true, 0.25f);
	if(GunClass == nullptr) return;
	Cannon = GetWorld()->SpawnActor<AGun>(GunClass);
	Cannon->AttachToComponent( Mesh, FAttachmentTransformRules::KeepRelativeTransform, BoneName);
	Cannon->Setup(this, Direction,Invader);
}

void AShootyEnemy::FindTarget()
{
	if(!HasAuthority())
		return;
	const auto World = GetWorld();
	if(World == nullptr)
		return;
	const auto GameMode = World->GetAuthGameMode();
	if(GameMode == nullptr)
		return;
	const int PlayerCount = GameMode->GetNumPlayers();

	Target = nullptr;
	float ClosestTarget = std::numeric_limits<int>::max();
	const FVector Position = GetActorLocation();
	
	for(int i = 0; i < PlayerCount; i++)
	{
		const auto Player = UGameplayStatics::GetPlayerPawn(World, i);
		if(Player == nullptr)
			continue;
		const float DistanceToPlayer = FVector::Distance(Position,Player->GetActorLocation());
		if( Range < DistanceToPlayer || ClosestTarget < DistanceToPlayer)
			continue;
		ClosestTarget = DistanceToPlayer;
		Target = Player;
	}
	
}

void AShootyEnemy::AimAtTarget()
{
	if(Target == nullptr)
		return;

	const auto CurrentLocation = Mesh->GetBoneLocation(CannonBoneParent);
	const auto Rotation = UKismetMathLibrary::FindLookAtRotation(Target->GetActorLocation(), CurrentLocation);
	Mesh->SetBoneRotationByName(CannonBoneParent, Rotation, EBoneSpaces::WorldSpace);
}

void AShootyEnemy::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	SetActorRotation(Direction);

	AimAtTarget();
	
}

void AShootyEnemy::Destroyed()
{
	Super::Destroyed();
	if(Cannon != nullptr)
		Cannon->Destroy();
}
