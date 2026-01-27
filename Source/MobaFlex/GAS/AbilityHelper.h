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
	UFUNCTION(Server, Reliable)
	void Server_GiveAbility(AActor* actor, TSubclassOf<UGameplayAbility> AbilityClass, bool ActivateOnApply);
	UFUNCTION(Server, Reliable)
	void Server_RemoveAbility(AActor* actor, TSubclassOf<UGameplayAbility> AbilityClass);
	UFUNCTION(Server, Reliable)
	void Server_ActivateAbility(AActor* actor, TSubclassOf<UGameplayAbility> AbilityClass);
	UFUNCTION(Server, Reliable)
	void Server_DeactivateAbility(AActor* actor, TSubclassOf<UGameplayAbility> AbilityClass);
	UFUNCTION(Server, Reliable)
	void Server_AddEffect(AActor* actor, TSubclassOf<UGameplayEffect> EffectClass, bool ReplaceIfExist); 
	UFUNCTION(Server, Reliable)
	void Server_RemoveEffect(AActor* actor, TSubclassOf<UGameplayEffect> EffectClass);
	UFUNCTION(Server, Reliable)
	void Server_ClearAllEffects(AActor* actor);
	
	static FGameplayTag FindGameplayTag(FString TagName);
};
