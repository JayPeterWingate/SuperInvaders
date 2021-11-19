// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bullet.generated.h"

UENUM()
enum ETeam
{
	Defender UMETA(DisplayName = "Defender"),
	Invader UMETA(DisplayName = "Invader")
};
class UProjectileMovementComponent;
UCLASS()
class SUPERINVADERS_API ABullet : public AActor
{
	GENERATED_BODY()
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components", meta=(AllowPrivateAccess="true"))
	UProjectileMovementComponent* ProjectileMovement;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components", meta=(AllowPrivateAccess="true"))
	UStaticMeshComponent* ProjectileMesh;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Damage", meta=(AllowPrivateAccess="true"))
	TSubclassOf<UDamageType> DamageType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Move", meta=(AllowPrivateAccess="true"))
	float MovementSpeed = 1300;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Damage", meta=(AllowPrivateAccess="true"))
	float Damage = 50;
	ETeam TeamValue;
	void ApplyDamage(AActor* OtherActor);
	
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
public:	
	// Sets default values for this actor's properties
	ABullet();
	void SetTeam(ETeam team);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


};
