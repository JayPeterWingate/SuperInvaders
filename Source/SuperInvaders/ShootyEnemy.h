// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyBase.h"

#include "ShootyEnemy.generated.h"

/**
 * 
 */
UCLASS()
class SUPERINVADERS_API AShootyEnemy : public AEnemyBase
{
	GENERATED_BODY()
	const static FRotator Direction;
	FTimerHandle ShooterHandle;
	FTimerHandle TargetingHandle;
	void Shoot();
	protected:
	virtual void BeginPlay() override;
	UPROPERTY()
	APawn* Target;
	
public:
	
	virtual void Tick(float DeltaSeconds) override;
protected:
	UPROPERTY(EditAnywhere, Category="Projective Type")
	float FireRate = 0.2f;
	UPROPERTY(EditAnywhere, Category="Projective Type")
	float FireChance = 0.5f;
	UPROPERTY(EditAnywhere, Category="Projective Type")
	float Range = 500.0f;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AGun> GunClass;

	UPROPERTY()
	AGun* Cannon;
	UPROPERTY(EditAnywhere)
	FName BoneName;

	UPROPERTY(EditAnywhere)
	FName CannonBoneParent;

	void FindTarget();
	void AimAtTarget();
	
	virtual void Destroyed() override;
	
};
