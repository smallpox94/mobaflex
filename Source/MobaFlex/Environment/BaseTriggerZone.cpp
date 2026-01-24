// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseTriggerZone.h"
#include "Components/BoxComponent.h"

// Sets default values
ABaseTriggerZone::ABaseTriggerZone()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SceneBaseComp = CreateDefaultSubobject<USceneComponent>(TEXT("SceneBaseComp"));
	// Create a default box component, but derived classes can replace with any shape
	TriggerZone = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerZone"));
	RootComponent = SceneBaseComp;
	TriggerZone->SetupAttachment(SceneBaseComp);
	
}

// Called when the game starts or when spawned
void ABaseTriggerZone::BeginPlay()
{
	Super::BeginPlay();

	if (TriggerZone)
	{
		TriggerZone->OnComponentBeginOverlap.AddDynamic(this, &ABaseTriggerZone::OnOverlapBegin);
		TriggerZone->OnComponentEndOverlap.AddDynamic(this, &ABaseTriggerZone::OnOverlapEnd);
	}
}

void ABaseTriggerZone::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	HandleOverlapBegin(OtherActor, SweepResult);
}

void ABaseTriggerZone::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	HandleOverlapEnd(OtherActor);
}

void ABaseTriggerZone::HandleOverlapBegin(AActor* OtherActor, const FHitResult& SweepResult)
{
	// Override in derived classes
}

void ABaseTriggerZone::HandleOverlapEnd(AActor* OtherActor)
{
	// Override in derived classes
}
