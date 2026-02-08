 // Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GunProjectile.h"
#include "GameFramework/Actor.h"
#include "GameFramework/RotatingMovementComponent.h"
#include "GunTurret.generated.h"

extern int GTurretUseObjectPool = 0;
static FAutoConsoleVariableRef CVarEnableTurretUseObjectPool(TEXT("TurretUseObjectPool"), GTurretUseObjectPool, TEXT("Turret Use Object Pool"));


UCLASS()
class MOBAFLEX_API AGunTurret : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AGunTurret();

protected:
	void ShootProjectile();
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)	
	TSubclassOf<AGunProjectile> ProjectileClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ProjectilePerSec = 100.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<URotatingMovementComponent> RotateComponent;
private:
	FTimerHandle ShootTimerHandle;

};
