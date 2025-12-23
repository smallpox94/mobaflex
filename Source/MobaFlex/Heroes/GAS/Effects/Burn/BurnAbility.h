// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "BurnAbility.generated.h"

/**
 * 
 */
UCLASS()
class MOBAFLEX_API UBurnAbility : public UGameplayAbility
{
	GENERATED_BODY()
public:
	UBurnAbility();
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

};
