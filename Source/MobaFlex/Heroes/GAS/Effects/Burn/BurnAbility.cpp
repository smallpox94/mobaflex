// Fill out your copyright notice in the Description page of Project Settings.


#include "BurnAbility.h"

#include "AbilitySystemComponent.h"

UBurnAbility::UBurnAbility()
{
	
}

bool UBurnAbility::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, FGameplayTagContainer* OptionalRelevantTags) const
{
	if (!Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags))
	{
		return false;
	}
	return true;
}

void UBurnAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,	const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	if (HasAuthorityOrPredictionKey(ActorInfo, &ActivationInfo))
	{
		if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
		{
			EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
			return;
		}
		
		if (UAbilitySystemComponent* AbilityComponent = ActorInfo->AbilitySystemComponent.Get())
		{
			if (!BurnEffect)
			{
				UE_LOG(LogTemp, Error, TEXT("BurnAbility: BurnEffect not set on %s"), *GetName());
				EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
				return;
			}
			
			const FGameplayEffectContextHandle EffectContext = AbilityComponent->MakeEffectContext();
			AbilityComponent->ApplyGameplayEffectToSelf(BurnEffect.GetDefaultObject(), GetAbilityLevel(), EffectContext);
		}
	}
}

void UBurnAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	if (HasAuthorityOrPredictionKey(ActorInfo, &ActivationInfo))
	{
		if (UAbilitySystemComponent* AbilityComponent = ActorInfo->AbilitySystemComponent.Get())
		{
			if(BurnEffect)
			{
				// Remove the effect when the ability ends
				AbilityComponent->RemoveActiveGameplayEffectBySourceEffect(BurnEffect, AbilityComponent);
			}
		}
	}

	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}
