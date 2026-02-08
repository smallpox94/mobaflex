// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "IActorPooled.generated.h"

UINTERFACE(MinimalAPI, Blueprintable)
class UActorPooled : public UInterface
{
	GENERATED_BODY()
};

class MOBAFLEX_API IActorPooled
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintNativeEvent)
	void ActorPool_OnActivate(FTransform Transform, AActor* OwnerActor = nullptr, APawn* Instigator = nullptr);
	UFUNCTION(BlueprintNativeEvent)
	void ActorPool_OnDeactivate();
};