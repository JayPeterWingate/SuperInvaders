// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"

// Sets default values
AGun::AGun()
{
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	StaticMeshComponent->SetupAttachment(Root);
	BulletSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Bullet Spawn Point"));
	BulletSpawnPoint->SetupAttachment(Root);
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

void AGun::Fire()
{
	const FVector SpawnLocation = BulletSpawnPoint->GetComponentLocation();
	const FRotator SpawnRotation = BulletSpawnPoint->GetComponentRotation();
	ABullet* TempBullet = Owner->GetWorld()->SpawnActor<ABullet>(BulletClass, SpawnLocation, SpawnRotation);
	if(TempBullet == nullptr)
		return;
	
	TempBullet -> SetOwner(Owner);
	TempBullet -> SetTeam(Team);
}

void AGun::Setup(AActor* owner, FRotator direction, ETeam team)
{
	Owner = owner;
	Team = team;
	Direction = direction;
}



