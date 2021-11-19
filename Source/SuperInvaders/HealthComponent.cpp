// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"

#include "SuperInvadersGameModeBase.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

ETeam UHealthComponent::GetTeam() const
{
	return TeamValue;
}

void UHealthComponent::SetTeam(ETeam team)
{
	TeamValue = team;
}

// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	health = DefaultHealth;
	GameModeRef = Cast<ASuperInvadersGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::TakeDamage);
}

void UHealthComponent::TakeDamage(
	AActor* DamagedActor,
	float Damage,
	const UDamageType* DamageType,
	AController* InstigatedBy,
	AActor* DamageCauser
)
{
	
	if(Damage == 0 || health <= 0)
		return;
	health = FMath::Clamp(health - Damage, 0.0f, DefaultHealth);
	if(health <= 0)
		GameModeRef->ActorDied(GetOwner());
}



