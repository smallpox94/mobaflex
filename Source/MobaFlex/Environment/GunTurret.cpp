// Fill out your copyright notice in the Description page of Project Settings.


#include "GunTurret.h"

#include "ObjectPooling/WorldObjectPoolSubSystem.h"

// Sets default values
AGunTurret::AGunTurret()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RotateComponent = CreateDefaultSubobject<URotatingMovementComponent>("RotateComponent");
}

// Called when the game starts or when spawned
void AGunTurret::BeginPlay()
{
	Super::BeginPlay();
	
	check(ProjectilePerSec > 0.0f);
	UWorldObjectPoolSubSystem* ObjPoolSystem = GetWorld()->GetSubsystem<UWorldObjectPoolSubSystem>();
	ObjPoolSystem->ReserveSpaceForActorClass(ProjectileClass, ProjectilePerSec * 10, false);
	
	GetWorld()->GetTimerManager().SetTimer(ShootTimerHandle, FTimerDelegate::CreateUObject(this, &AGunTurret::ShootProjectile), 1.0f/ProjectilePerSec , true);
}

void AGunTurret::ShootProjectile()
{
	SCOPED_NAMED_EVENT_TEXT("ShootProjectile", FColor::Green)
	if (GTurretUseObjectPool == 1)
	{
		UWorldObjectPoolSubSystem* ObjPoolSystem = GetWorld()->GetSubsystem<UWorldObjectPoolSubSystem>();
		if (ObjPoolSystem)
		{
			ObjPoolSystem->AcquireActorFromPool(ProjectileClass, FTransform(GetActorRotation(), GetActorLocation()), this);
		}
	}
	else
	{
		GetWorld()->SpawnActor<AGunProjectile>(ProjectileClass, GetActorLocation(), GetActorForwardVector().Rotation());	
	}
}

