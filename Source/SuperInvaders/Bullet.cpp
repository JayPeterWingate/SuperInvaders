// Fill out your copyright notice in the Description page of Project Settings.


#include "Bullet.h"

#include "HealthComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

void ABullet::ApplyDamage(AActor* OtherActor)
{
	if(OtherActor == nullptr || OtherActor == GetOwner()) return;
	auto hit = OtherActor->FindComponentByClass<UHealthComponent>();
	if(hit == nullptr || hit->GetTeam() == TeamValue) return;
	FDamageEvent dmg = FDamageEvent(DamageType);
	OtherActor->TakeDamage(Damage, dmg, nullptr, this);
}

void ABullet::SetTeam(ETeam team)
{
	TeamValue = team;
}

void ABullet::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                    FVector NormalImpulse, const FHitResult& Hit)
{
	ApplyDamage(OtherActor);
	Destroy();
}

// Sets default values
ABullet::ABullet()
{
	PrimaryActorTick.bCanEverTick = false;

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	RootComponent = ProjectileMesh;

	ProjectileMesh->OnComponentHit.AddDynamic(this, &ABullet::OnHit);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));
	ProjectileMovement -> InitialSpeed = MovementSpeed;
	ProjectileMovement -> MaxSpeed = MovementSpeed;
	

}


// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
	Super::BeginPlay();
	
}


