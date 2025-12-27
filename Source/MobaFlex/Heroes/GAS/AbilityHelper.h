// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MobaFlex/Heroes/Base/MobaFlexCharacterBase.h"

// UCLASS()
class AbilityHelper 
{
public:
	static bool GiveAbility(AActor* actor, TSubclassOf<UGameplayAbility> AbilityClass, bool ActivateOnApply);
	static bool RemoveAbility(AActor* actor, TSubclassOf<UGameplayAbility> AbilityClass);
	static bool ActivateAbility(AActor* actor, TSubclassOf<UGameplayAbility> AbilityClass);
	static bool DeactivateAbility(AActor* actor, TSubclassOf<UGameplayAbility> AbilityClass);
	static bool AddEffect(AActor* actor, TSubclassOf<UGameplayEffect> EffectClass, bool ReplaceIfExist); 
	static bool RemoveEffect(AActor* actor, TSubclassOf<UGameplayEffect> EffectClass);
	static bool ClearAllEffects(AActor* actor);
	static FGameplayTag FindGameplayTag(FString TagName);
};
