// Fill out your copyright notice in the Description page of Project Settings.


#include "WaveSpawner.h"

#include "EnemyBase.h"
#include "Misc/Char.h"
#include "Components/SplineComponent.h"


// Sets default values
AWaveSpawner::AWaveSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;
	Spline = CreateDefaultSubobject<USplineComponent>(TEXT("Spine"));
	Spline->SetupAttachment(Root);
	Spline->Duration = TotalPathTimeController;
	Spline-> bDrawDebug = true;
	
}

void AWaveSpawner::StartWave(FString Data)
{
	if(GetWorld()->GetTimerManager().TimerExists(WaveSpawnTimer))
		GetWorld()->GetTimerManager().ClearTimer(WaveSpawnTimer);
		
	SpawnData = Data;
	SpawnedIndex = 0;
	GetWorld()->GetTimerManager().SetTimer(WaveSpawnTimer, this, &AWaveSpawner::SpawnWave, EnemySpacing, true, 0.0f);
}

USplineComponent* AWaveSpawner::GetSpline() const
{
	return Spline;
}

// Called when the game starts or when spawned
void AWaveSpawner::BeginPlay()
{
	Super::BeginPlay();
	
}

void AWaveSpawner::SpawnWave()
{
	if(SpawnedIndex >= SpawnData.Len())
	{
		GetWorld()->GetTimerManager().ClearTimer(WaveSpawnTimer);
		return;
	}
	FString Key = SpawnData.Mid(SpawnedIndex,1);
	UE_LOG(LogTemp, Warning, TEXT("%s"), *Key);
	
	if(EnemyMap.Contains(Key) && EnemyMap[Key] != nullptr)
	{
		const auto EnemyClass = EnemyMap[Key];
		auto Enemy = GetWorld()->SpawnActor<AEnemyBase>(EnemyClass);
		Enemy->SetPath(Spline);
	}
	SpawnedIndex++;	
}



