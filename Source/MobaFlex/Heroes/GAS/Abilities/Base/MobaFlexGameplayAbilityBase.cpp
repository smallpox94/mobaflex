// Fill out your copyright notice in the Description page of Project Settings.

#include "MobaFlexGameplayAbilityBase.h"

void UMobaFlexGameplayAbilityBase::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	if (HasAuthorityOrPredictionKey(ActorInfo, &ActivationInfo))
	{
		if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
		{
			EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
		}
		for(const FGameplayTag& DeactivateTag : DeactivateOnOwnedTags)
		{
			UAbilityTask_WaitGameplayTagAdded* WaitTagTask = UAbilityTask_WaitGameplayTagAdded::WaitGameplayTagAdd(this, DeactivateTag, GetAvatarActorFromActorInfo(), true);
			if (WaitTagTask)
			{
				WaitGameplayTagAddedToDeactivate.Add(WaitTagTask);
				WaitTagTask->Added.AddDynamic(this, &UMobaFlexGameplayAbilityBase::OnInterruptTagAdded);
				WaitTagTask->ReadyForActivation();
			}
		}
	}
}

void UMobaFlexGameplayAbilityBase::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UMobaFlexGameplayAbilityBase::OnInterruptTagAdded()
{
	bool bWasCancelled = true;
	for(UAbilityTask_WaitGameplayTagAdded* DeactivateTask : WaitGameplayTagAddedToDeactivate)
	{
		DeactivateTask->Added.Clear();
	}
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, bWasCancelled);
}