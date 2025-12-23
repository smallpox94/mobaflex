// Fill out your copyright notice in the Description page of Project Settings.


#include "BurnAbility.h"

#include "AbilitySystemComponent.h"

UBurnAbility::UBurnAbility()
{
	
}

void UBurnAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,	const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	if (HasAuthorityOrPredictionKey(ActorInfo, &ActivationInfo))
	{
		if (UAbilitySystemComponent* AbilityComponent = ActorInfo->AbilitySystemComponent.Get())
		{
			AbilityComponent->ApplyGameplayEffectToTarget(BurnEffect.Get(), ActorInfo->AvatarActor.Get()->GetComponentByClass(UAbilitySystemComponent::StaticClass()));
			// FGameplayEffectSpecHandle SpecHandle = AbilityComponent->MakeOutgoingSpec(BurnEffect, GetAbilityLevel());
			// if(SpecHandle.IsValid())
			// {
			// 	ApplyGameplayEffectSpecToOwner(Handle, ActorInfo, ActivationInfo, SpecHandle);
			// }
		}
	}
    EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
}
