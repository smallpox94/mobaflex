// Fill out your copyright notice in the Description page of Project Settings.


#include "StunAbility.h"
#include "AbilitySystemComponent.h"
#include "Abilities/Tasks/AbilityTask_WaitDelay.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"

UStunAbility::UStunAbility()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	StunDuration = 2.0f;
}

void UStunAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	if (HasAuthorityOrPredictionKey(ActorInfo, &ActivationInfo))
	{
		// Cancel other abilities with the specified tags
		if (ActorInfo->AbilitySystemComponent.IsValid())
		{
			ActorInfo->AbilitySystemComponent->CancelAbilities(&AbilitiesToCancel);
		}

		// Spawn Niagara VFX if specified
		AActor* Avatar = GetAvatarActorFromActorInfo();
		if (StunVFX && Avatar)
		{
			SpawnedVFX = UNiagaraFunctionLibrary::SpawnSystemAttached(StunVFX, Avatar->GetRootComponent(), NAME_None, FVector::ZeroVector, FRotator::ZeroRotator, EAttachLocation::KeepRelativeOffset, true);
		}

		// Use AbilityTask_WaitDelay for the stun duration
		UAbilityTask_WaitDelay* WaitDelayTask = UAbilityTask_WaitDelay::WaitDelay(this, StunDuration);
		if (WaitDelayTask)
		{
			WaitDelayTask->OnFinish.AddDynamic(this, &UStunAbility::OnStunFinished);
			WaitDelayTask->ReadyForActivation();
		}
		else
		{
			// If we couldn't create the task, just end the ability
			EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
		}
	}
}

void UStunAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	if (SpawnedVFX)
	{
		SpawnedVFX->Deactivate();
		SpawnedVFX = nullptr;
	}

	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UStunAbility::OnStunFinished()
{
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
}
