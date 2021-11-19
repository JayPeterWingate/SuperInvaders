// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/GameModeBase.h"

#include "SuperInvadersGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class SUPERINVADERS_API ASuperInvadersGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	class APlayerTank* PlayerRef = nullptr;
	class AWaveSpawner* WaveSpawner = nullptr;
	int RemainingTargets;

	UPROPERTY(EditDefaultsOnly)
	int StartingTeamLives = 10;
	int TeamLives = StartingTeamLives;
	
	virtual void BeginPlay() override;
	
	protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Game Data")
	int WaveCount;
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void RoundStart();
	UFUNCTION(BlueprintImplementableEvent)
	void RoundOver(bool PlayerWon);
	UFUNCTION(BlueprintCallable)
	void SpawnWave(FString SpawnData);

	UFUNCTION(BlueprintCallable)
	AWaveSpawner* GetWaveSpawner() const;
	public:
	void ActorDied(AActor* actor);
	void TakeLives(class AEnemyBase* Enemy);
};
