// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "Abilities/Tasks/AbilityTask_WaitGameplayTag.h"
#include "MobaFlexGameplayAbilityBase.generated.h"

/**
 * 
 */
UCLASS()
class MOBAFLEX_API UMobaFlexGameplayAbilityBase : public UGameplayAbility
{
protected:
	UPROPERTY(EditDefaultsOnly, Category = Tags, meta=(Categories="OwnedTagsCategory"))
	FGameplayTagContainer DeactivateOnOwnedTags;
	
public:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	UFUNCTION()
	void OnInterruptTagAdded();

private:
	UPROPERTY()
	TArray<TObjectPtr<UAbilityTask_WaitGameplayTagAdded>> WaitGameplayTagAddedToDeactivate;
	
	GENERATED_BODY()
};
