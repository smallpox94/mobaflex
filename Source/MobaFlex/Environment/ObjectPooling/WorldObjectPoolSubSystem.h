// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "WorldObjectPoolSubSystem.generated.h"

/**
 * 
 */
UCLASS()
class MOBAFLEX_API UWorldObjectPoolSubSystem : public UWorldSubsystem
{
public:
	virtual void Deinitialize() override;
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

private:
	GENERATED_BODY()
};
