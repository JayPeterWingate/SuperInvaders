// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Bullet.h"
#include "GameFramework/Actor.h"
#include "Gun.generated.h"

UCLASS()
class SUPERINVADERS_API AGun : public AActor
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere)
	USceneComponent* BulletSpawnPoint = nullptr;
	UPROPERTY(EditAnywhere, Category="Projectile Type")
	TSubclassOf<class ABullet> BulletClass = nullptr;
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* StaticMeshComponent = nullptr;
	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;
	ETeam Team;
	AActor* Owner;
	FRotator Direction;
public:	
	// Sets default values for this actor's properties
	AGun();
	void Fire();
	void Setup(AActor* owner, FRotator direction, ETeam team);

};
