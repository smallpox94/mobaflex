// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "WorldObjectPoolSubSystem.generated.h"


USTRUCT()
struct FActorPool
{
	GENERATED_BODY()
	
	int MaxPoolSize = 1000;
	
	UPROPERTY()
	TArray<AActor*> Actors;
};

UCLASS()
class MOBAFLEX_API UWorldObjectPoolSubSystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	void ReserveSpaceForActorClass(TSubclassOf<AActor> ActorClass, int Nb, bool PreSpawn = false);
	void DeletePoolForActorClass(TSubclassOf<AActor> ActorClass);
	AActor* AcquireActorFromPool(TSubclassOf<AActor> ActorClass, FTransform Transform, AActor* Owner = nullptr, APawn* Instigator = nullptr);
	void ReleaseActorToPool(AActor* Actor, int Index = -1);
	
protected:
	UPROPERTY(Transient)
	TMap<TSubclassOf<AActor>, FActorPool> ObjectPools;
};
