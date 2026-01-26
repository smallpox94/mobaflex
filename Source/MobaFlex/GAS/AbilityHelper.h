// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MobaFlex/Heroes/Base/MobaFlexCharacterBase.h"

#include "AbilityHelper.generated.h"

UCLASS()
class UAbilityHelperSubSystem : public UGameInstanceSubsystem 
{
	GENERATED_BODY()
	
public:
	bool GiveAbility(AActor* actor, TSubclassOf<UGameplayAbility> AbilityClass, bool ActivateOnApply);
	bool RemoveAbility(AActor* actor, TSubclassOf<UGameplayAbility> AbilityClass);
	bool ActivateAbility(AActor* actor, TSubclassOf<UGameplayAbility> AbilityClass);
	bool DeactivateAbility(AActor* actor, TSubclassOf<UGameplayAbility> AbilityClass);
	UFUNCTION(Server, Reliable)
	void Server_AddEffect(AActor* actor, TSubclassOf<UGameplayEffect> EffectClass, bool ReplaceIfExist); 
	UFUNCTION(Server, Reliable)
	void Server_RemoveEffect(AActor* actor, TSubclassOf<UGameplayEffect> EffectClass);
	bool ClearAllEffects(AActor* actor);
	static FGameplayTag FindGameplayTag(FString TagName);
};
