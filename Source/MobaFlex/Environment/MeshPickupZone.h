// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PickupZone.h"
#include "MeshPickupZone.generated.h"

UCLASS()
class MOBAFLEX_API AMeshPickupZone : public APickupZone
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMeshPickupZone();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
