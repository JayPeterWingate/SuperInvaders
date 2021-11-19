// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PlayerTank.generated.h"

class ABullet;
UCLASS()
class SUPERINVADERS_API APlayerTank : public APawn
{
	GENERATED_BODY()
	static FRotator Direction;
	float HorizontalInput = 0.0f;
	UPROPERTY(EditAnywhere);
	float Speed = 1.0f;
	UFUNCTION()
	void HorizontalMovement(float input);
	UFUNCTION()
	void Fire();
	
	UPROPERTY(EditAnywhere)
	USceneComponent* Root;
	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent* BaseMesh = nullptr;
	
	UPROPERTY(EditAnywhere)
	class UCapsuleComponent* Collider;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AGun> GunClass;
	
	AGun* Cannon;
	UPROPERTY(EditAnywhere)
	FName BoneName;
public:
	// Sets default values for this pawn's properties
	APlayerTank();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
};
