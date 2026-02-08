// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldObjectPoolSubSystem.h"

#include "IActorPooled.h"

void UWorldObjectPoolSubSystem::ReserveSpaceForActorClass(TSubclassOf<AActor> ActorClass, int Nb, bool PreSpawn /* = false */)
{
	SCOPED_NAMED_EVENT_TEXT("WorldObjectPool::ReserveSpaceForActorClass", FColor::Green)
	FActorPool& existingPool = ObjectPools.FindOrAdd(ActorClass);
	existingPool.Actors.Empty();
	existingPool.Actors.Reserve(Nb);
	if (PreSpawn)
	{
		SCOPED_NAMED_EVENT_TEXT("WorldObjectPool::ReserveSpaceForActorClass::PreSpawn", FColor::Green)
		for(int i = 0; i < Nb; i++)
		{
			AActor* pooledActor = GetWorld()->SpawnActor<AActor>(ActorClass);
			ReleaseActorToPool(pooledActor);
		}		
	}
	existingPool.MaxPoolSize = Nb;
}

void UWorldObjectPoolSubSystem::DeletePoolForActorClass(TSubclassOf<AActor> ActorClass)
{
	FActorPool& existingPool = ObjectPools.FindOrAdd(ActorClass);
	for (AActor* Actor : existingPool.Actors)
	{
		Actor->Destroy();
	}
	ObjectPools.Remove(ActorClass);
}

AActor* UWorldObjectPoolSubSystem::AcquireActorFromPool(TSubclassOf<AActor> ActorClass, FTransform Transform, AActor* Owner /* = nullptr*/, APawn* Instigator /*= nullptr*/)
{
	SCOPED_NAMED_EVENT_TEXT("WorldObjectPool::Acquire", FColor::Green)
	FActorPool& existingPool = ObjectPools.FindOrAdd(ActorClass);
	AActor* pooledActor;
	if (existingPool.Actors.IsEmpty())
	{
		pooledActor = GetWorld()->SpawnActor<AActor>(ActorClass);
	}
	else
	{
		pooledActor = existingPool.Actors[0];
		existingPool.Actors.RemoveAt(0);
	}
	
	if (pooledActor && pooledActor->Implements<UActorPooled>())
	{
		IActorPooled::Execute_ActorPool_OnActivate(pooledActor, Transform, Owner, Instigator);
	}
	
	return pooledActor;
}

void UWorldObjectPoolSubSystem::ReleaseActorToPool(AActor* Actor, int Index /*= -1*/)
{
	SCOPED_NAMED_EVENT_TEXT("WorldObjectPool::Release", FColor::Green)
	FActorPool& existingPool = ObjectPools.FindOrAdd(Actor->GetClass());
	
	if (Actor->Implements<UActorPooled>())
	{
		IActorPooled::Execute_ActorPool_OnDeactivate(Actor);
	}
	if (existingPool.Actors.Num() <= existingPool.MaxPoolSize)
	{
		if (Index < 0)
		{	
			existingPool.Actors.Add(Actor);
		}
		else
		{
			existingPool.Actors.Insert(Actor, Index);
		}
	}
}

