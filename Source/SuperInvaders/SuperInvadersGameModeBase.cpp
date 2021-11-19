// Copyright Epic Games, Inc. All Rights Reserved.


#include "SuperInvadersGameModeBase.h"

#include "EnemyBase.h"
#include "WaveSpawner.h"
#include "Kismet/GameplayStatics.h"
#include "Pawn/PlayerTank.h"


void ASuperInvadersGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	PlayerRef = Cast<APlayerTank>(UGameplayStatics::GetPlayerPawn(this, 0));
	TArray<AActor*> Spawners;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AWaveSpawner::StaticClass(), Spawners);
	if(Spawners.Num() == 0) return;
	WaveSpawner = Cast<AWaveSpawner>(Spawners[0]);
	if(WaveSpawner == nullptr) return;
	RoundStart();
}

void ASuperInvadersGameModeBase::SpawnWave(FString SpawnData)
{
	if(WaveSpawner == nullptr || SpawnData.Len() == 0)
		return;
	RemainingTargets = SpawnData.Len();
	WaveSpawner->StartWave(SpawnData);
	
}

AWaveSpawner* ASuperInvadersGameModeBase::GetWaveSpawner() const
{
	return WaveSpawner;
}

void ASuperInvadersGameModeBase::ActorDied(AActor* actor)
{
	if(actor != PlayerRef)
	{
		RemainingTargets -= 1;
		if(RemainingTargets == 0)
			RoundOver(true);
		actor->Destroy();
		return;
	}
	auto Controller = PlayerRef->GetController();
	RoundOver(false);
	Controller ->UnPossess();
}

void ASuperInvadersGameModeBase::TakeLives(AEnemyBase* Enemy)
{
	TeamLives -= Enemy->GetDamage();
	ActorDied(Enemy);
	if(TeamLives <= 0)
		RoundOver(false);
}
