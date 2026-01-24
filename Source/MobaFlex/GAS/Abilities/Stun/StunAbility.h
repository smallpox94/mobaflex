// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Base/MobaFlexGameplayAbilityBase.h"
#include "StunAbility.generated.h"

class UNiagaraSystem;
class UNiagaraComponent;

/**
 * 
 */
UCLASS()
class MOBAFLEX_API UStunAbility : public UMobaFlexGameplayAbilityBase
{
	GENERATED_BODY()

public:
	UStunAbility();

protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

	UPROPERTY(EditDefaultsOnly, Category = "Stun")
	float StunDuration;

	UPROPERTY(EditDefaultsOnly, Category = "Stun")
	FGameplayTagContainer AbilitiesToCancel;

	UPROPERTY(EditDefaultsOnly, Category = "Stun|Visuals")
	TObjectPtr<UNiagaraSystem> StunVFX;

	UPROPERTY()
	TObjectPtr<UNiagaraComponent> SpawnedVFX;

	UFUNCTION()
	void OnStunFinished();
};
