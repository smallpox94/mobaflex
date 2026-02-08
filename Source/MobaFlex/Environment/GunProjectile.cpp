// Fill out your copyright notice in the Description page of Project Settings.


#include "GunProjectile.h"
#include "CascadeParticleSystemComponent.h"
#include "GunTurret.h"
#include "ObjectPooling/WorldObjectPoolSubSystem.h"

// Sets default values
AGunProjectile::AGunProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	FXComponent = CreateDefaultSubobject<UCascadeParticleSystemComponent>("FXComponent"); 
	RootComponent = FXComponent;
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovementComponent");
}

// Called when the game starts or when spawned
void AGunProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGunProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(GetActorLocation().Z < 0.0f)
	{
		SCOPED_NAMED_EVENT_TEXT("Destroy/Release Projectiles", FColor::Green)
		if (GTurretUseObjectPool == 1)
		{
			UWorldObjectPoolSubSystem* ObjPoolSystem = GetWorld()->GetSubsystem<UWorldObjectPoolSubSystem>();
			ObjPoolSystem->ReleaseActorToPool(this);
		}
		else
		{
			Destroy();
		}
	}
}

void AGunProjectile::ActorPool_OnActivate_Implementation(FTransform Transform, AActor* OwnerActor /* = nullptr */, APawn* instigator /* = nullptr */)
{
	SetActorTransform(Transform);
	SetInstigator(instigator);
	SetOwner(OwnerActor);
	SetActorEnableCollision(true);
	SetActorHiddenInGame(false);
	if (!ProjectileMovementComponent->HasBeenInitialized())
	{
		ProjectileMovementComponent->InitializeComponent();
	}
	ProjectileMovementComponent->Activate();
	DispatchBeginPlay();
}

void AGunProjectile::ActorPool_OnDeactivate_Implementation()
{
	SetActorEnableCollision(false);
	SetActorHiddenInGame(true);
	if (ProjectileMovementComponent->HasBeenInitialized())
    {
		ProjectileMovementComponent->UninitializeComponent();
    }
	ProjectileMovementComponent->Deactivate();
	RouteEndPlay(EEndPlayReason::Destroyed);
}
