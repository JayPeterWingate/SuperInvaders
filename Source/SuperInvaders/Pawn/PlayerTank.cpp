// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerTank.h"
#include "Components/StaticMeshComponent.h"
#include "Math/UnitConversion.h"
#include "Components/CapsuleComponent.h"
#include "SuperInvaders/Bullet.h"
#include "SuperInvaders/Gun.h"



FRotator APlayerTank::Direction = FRotationMatrix::MakeFromX(FVector(0,0,0)).Rotator();

// Sets default values
APlayerTank::APlayerTank()
{
	PrimaryActorTick.bCanEverTick = true;
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);
	BaseMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(Root);
	Collider = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Collider"));
	Collider->SetupAttachment(Root);

	
	
}

// Called when the game starts or when spawned
void APlayerTank::BeginPlay()
{
	Super::BeginPlay();
	if(GunClass == nullptr) return;
	Cannon = GetWorld()->SpawnActor<AGun>(GunClass);
	Cannon->AttachToComponent( BaseMesh, FAttachmentTransformRules::KeepRelativeTransform, BoneName);
	Cannon->Setup(this, FRotator(0, 0, 0), Defender);
}

// Called every frame
void APlayerTank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	FVector PlayerPos = GetActorLocation();
	PlayerPos.Y += HorizontalInput * DeltaTime * Speed;
	SetActorLocation(PlayerPos);	
}
void APlayerTank::HorizontalMovement(float input)
{
	HorizontalInput = input;
}

void APlayerTank::Fire()
{
	if(Cannon == nullptr) return;
	Cannon->Fire();
}

// Called to bind functionality to input
void APlayerTank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	PlayerInputComponent->BindAxis(TEXT("Horizontal"), this, &APlayerTank::HorizontalMovement);
	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &APlayerTank::Fire);
}

