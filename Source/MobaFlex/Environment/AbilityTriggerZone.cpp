// Fill out your copyright notice in the Description page of Project Settings.

#include "AbilityTriggerZone.h"
#include "AbilitySystemComponent.h"
#include "MobaFlex/GAS/AbilityHelper.h"

// Sets default values
AAbilityTriggerZone::AAbilityTriggerZone()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void AAbilityTriggerZone::HandleOverlapBegin(AActor* OtherActor, const FHitResult& SweepResult)
{
	for (TSubclassOf<UGameplayEffect> Effect : EffectsEntering)
	{
		GetGameInstance()->GetSubsystem<UAbilityHelperSubSystem>()->Server_AddEffect(OtherActor, Effect, true);
	}
}

void AAbilityTriggerZone::HandleOverlapEnd(AActor* OtherActor)
{
	if (RemoveEnteringEffectsOnExist)
	{
		for (TSubclassOf<UGameplayEffect> Effect : EffectsEntering)
		{
			GetGameInstance()->GetSubsystem<UAbilityHelperSubSystem>()->Server_RemoveEffect(OtherActor, Effect);
		}
	}

	for (TSubclassOf<UGameplayEffect> Effect : EffectsLeaving)
	{
		GetGameInstance()->GetSubsystem<UAbilityHelperSubSystem>()->Server_AddEffect(OtherActor, Effect, true);
	}
}
