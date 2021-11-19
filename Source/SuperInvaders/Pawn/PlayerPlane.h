// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PlayerPlane.generated.h"

UCLASS()
class SUPERINVADERS_API APlayerPlane : public APawn
{
	GENERATED_BODY()
	float HorizontalInput = 0.0f;
	float VerticalInput = 0.0f;

	FVector TargetRot = FVector(1,0,0);
	UPROPERTY(EditAnywhere)
	float RotEffect = 100.0f;
	UPROPERTY(EditAnywhere)
	float RotSpeed = 1.0f;
	UPROPERTY(EditAnywhere)
	float Speed;
	
	UPROPERTY(EditAnywhere)
	USceneComponent* Root;
	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent* BaseMesh = nullptr;
	UPROPERTY(EditAnywhere)
	USceneComponent* CannonSp = nullptr;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AGun> GunClass;
	UPROPERTY()
	AGun* Cannon;

	UPROPERTY(EditAnywhere)
	FName BoneName;

	UPROPERTY(EditAnywhere)
	class UCapsuleComponent* Collider;

	
public:
	// Sets default values for this pawn's properties
	APlayerPlane();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void UpdateMovement(float DeltaTime);

	UFUNCTION()
	void HorizontalMovement(float input);
	UFUNCTION()
	void VerticalMovement(float input);
	UFUNCTION()
	void Fire();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
