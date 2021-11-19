// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemyBase.generated.h"

UCLASS()
class SUPERINVADERS_API AEnemyBase : public AActor
{
	GENERATED_BODY()
	float StartTime;
	bool bCanMove;
public:	
	// Sets default values for this actor's properties
	AEnemyBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Enemy")
	USceneComponent* Root;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Enemy")
	class UPoseableMeshComponent* Mesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Enemy")
	class UCapsuleComponent* Collider;
	class USplineComponent* Path = nullptr;
	class UHealthComponent* HealthComponent = nullptr;
	UPROPERTY(EditAnywhere)
	float Speed;
	UPROPERTY(EditAnywhere)
	int Damage = 1;
	
	void GoalHit();
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void SetPath(USplineComponent* Spline);
	int GetDamage() const;

};
