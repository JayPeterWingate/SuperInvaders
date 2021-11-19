// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"


#include "SuperInvadersGameModeBase.h"
#include "Components/ActorComponent.h"

#include "HealthComponent.generated.h"

class AGameModeBase;
enum ETeam;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UHealthComponent : public UActorComponent
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere)
	float DefaultHealth = 100;
	float health = 0;
	

	ASuperInvadersGameModeBase* GameModeRef;
public:	
	// Sets default values for this component's properties
	UHealthComponent();
	ETeam GetTeam() const;
	void SetTeam(ETeam team); 

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<ETeam> TeamValue;
	UFUNCTION()
	void TakeDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser);		
};
