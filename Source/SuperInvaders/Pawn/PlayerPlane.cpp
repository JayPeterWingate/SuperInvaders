// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPlane.h"


#include "Components/CapsuleComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "SuperInvaders/Gun.h"

void APlayerPlane::VerticalMovement(float input)
{
	VerticalInput = input;
}

void APlayerPlane::Fire()
{
	if(Cannon == nullptr) return;
	Cannon->Fire();
}

// Sets default values
APlayerPlane::APlayerPlane()
{
	PrimaryActorTick.bCanEverTick = true;
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);
	BaseMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(Root);
	Collider = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Collider"));
	Collider->SetupAttachment(Root);
	CannonSp = CreateDefaultSubobject<USceneComponent>(TEXT("Cannon Spawn Point"));
	CannonSp->SetupAttachment(BaseMesh);

}

// Called when the game starts or when spawned
void APlayerPlane::BeginPlay()
{
	Super::BeginPlay();
	if(GunClass == nullptr) return;
	Cannon = GetWorld()->SpawnActor<AGun>(GunClass);
	Cannon->AttachToComponent( BaseMesh, FAttachmentTransformRules::KeepRelativeTransform, BoneName);
	Cannon->Setup(this, FRotator(0, 0, 0), Defender);
}

void APlayerPlane::UpdateMovement(float DeltaTime)
{
	FVector PlayerPos = GetActorLocation();
	
	SetActorLocation(PlayerPos + ( BaseMesh->GetForwardVector() * Speed * DeltaTime));
}

void APlayerPlane::HorizontalMovement(float input)
{
	HorizontalInput = input;
}
// Called every frame
void APlayerPlane::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
	if(HorizontalInput != 0 || VerticalInput != 0)
	{
		TargetRot.Y = FMath::Lerp(TargetRot.Y , HorizontalInput, DeltaTime * RotSpeed );
		TargetRot.X = FMath::Lerp(TargetRot.X , VerticalInput, DeltaTime * RotSpeed );
	}
	if(TargetRot.Y == 0)
		TargetRot.Y = 0.001f;
	auto NewRot = UKismetMathLibrary::FindLookAtRotation(FVector::ZeroVector, TargetRot);
	NewRot.Roll = FMath::Clamp((NewRot.Yaw - BaseMesh->GetComponentRotation().Yaw) * RotEffect, -90.0f, 90.0f);
	//const auto current = BaseMesh->GetComponentRotation();
	// const auto newRot = FRotator(0, FMath::Lerp(current.Yaw , rotation.Yaw, DeltaTime * RotSpeed ),0);
	BaseMesh->SetWorldRotation(NewRot);
	
	
	UpdateMovement(DeltaTime);
}

// Called to bind functionality to input
void APlayerPlane::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis(TEXT("Vertical"), this, &APlayerPlane::VerticalMovement);
	PlayerInputComponent->BindAxis(TEXT("Horizontal"), this, &APlayerPlane::HorizontalMovement);
	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &APlayerPlane::Fire);
}

