// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Components/SplineComponent.h"
#include "GameFramework/Actor.h"
#include "WaveSpawner.generated.h"
class AEnemyBase;
UCLASS()
class SUPERINVADERS_API AWaveSpawner : public AActor
{
	GENERATED_BODY()
	float StartTime;
	
public:	
	// Sets default values for this actor's properties
	AWaveSpawner();
	UFUNCTION(BlueprintCallable)
	void StartWave(FString Data);
	USplineComponent* GetSpline() const;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "SplineController")
	USceneComponent* Root;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "SplineController")
	class USplineComponent* Spline;

	int SpawnedIndex = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="SplineController")
	float EnemySpacing = 1;
	
	UPROPERTY(EditAnywhere)
	float TotalPathTimeController  = 10;

	UPROPERTY(EditAnywhere, Category="Wave details")
	TMap<FString, TSubclassOf<AEnemyBase>> EnemyMap;
	FString SpawnData;
	FTimerHandle WaveSpawnTimer;

	UFUNCTION()
	void SpawnWave();

	
};
