// Fill out your copyright notice in the Description page of Project Settings.


#include "MeshPickupZone.h"


// Sets default values
AMeshPickupZone::AMeshPickupZone()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMeshPickupZone::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMeshPickupZone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

