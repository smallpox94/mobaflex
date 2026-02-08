// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CascadeParticleSystemComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "ObjectPooling/IActorPooled.h"
#include "GunProjectile.generated.h"

UCLASS()
class MOBAFLEX_API AGunProjectile : public AActor, public IActorPooled
{
public:
	virtual void ActorPool_OnActivate_Implementation(FTransform Transform, AActor* OwnerActor  = nullptr, APawn* instigator = nullptr ) override;
	virtual void ActorPool_OnDeactivate_Implementation() override;
private:
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AGunProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UCascadeParticleSystemComponent> FXComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UProjectileMovementComponent> ProjectileMovementComponent;
};
