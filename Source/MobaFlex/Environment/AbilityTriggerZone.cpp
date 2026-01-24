// Fill out your copyright notice in the Description page of Project Settings.

#include "AbilityTriggerZone.h"
#include "AbilitySystemComponent.h"
#include "MobaFlex/GAS/AbilityHelper.h"

// Sets default values
AAbilityTriggerZone::AAbilityTriggerZone()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TriggerZone = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerZone"));
	RootComponent = TriggerZone;
}


// Called when the game starts or when spawned
void AAbilityTriggerZone::BeginPlay()
{
	Super::BeginPlay();

	TriggerZone->OnComponentBeginOverlap.AddDynamic(this, &AAbilityTriggerZone::OnOverlapBegin);
	TriggerZone->OnComponentEndOverlap.AddDynamic(this, &AAbilityTriggerZone::OnOverlapEnd);
}

void AAbilityTriggerZone::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	for (TSubclassOf<UGameplayEffect> Effect : EffectsEntering)
	{
		AbilityHelper::AddEffect(OtherActor, Effect, true);
	}
}

void AAbilityTriggerZone::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (RemoveEnteringEffectsOnExist)
	{
		for (TSubclassOf<UGameplayEffect> Effect : EffectsEntering)
		{
			AbilityHelper::RemoveEffect(OtherActor, Effect);
		}
	}
	
	for (TSubclassOf<UGameplayEffect> Effect : EffectsLeaving)
	{
		AbilityHelper::AddEffect(OtherActor, Effect, true);
	}
}
