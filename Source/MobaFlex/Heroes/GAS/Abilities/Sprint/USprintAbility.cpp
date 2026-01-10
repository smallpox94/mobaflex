// Fill out your copyright notice in the Description page of Project Settings.


#include "USprintAbility.h"
#include "AbilitySystemComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "MobaFlex/Heroes/Base/MobaFlexCharacterBase.h"
#include "MobaFlex/Heroes/GAS/AbilityHelper.h"
#include "MobaFlex/Heroes/GAS/PlayBaseAttributeSet.h"

UUSprintAbility::UUSprintAbility()
{
	
}

bool UUSprintAbility::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, 	const FGameplayTagContainer* TargetTags, FGameplayTagContainer* OptionalRelevantTags) const
{
	if (!Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags))
	{
		return false;
	}
	
	ACharacter* Character = Cast<ACharacter>(ActorInfo->AvatarActor.Get());
	if (!Character || Character->GetCharacterMovement()->IsFalling())
	{
		return false;
	}

	return true;
}

void UUSprintAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	if (HasAuthorityOrPredictionKey(ActorInfo, &ActivationInfo))
	{
		if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
		{
			EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
			return;
		}
		
		Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
		
		AMobaFlexCharacterBase* character = Cast<AMobaFlexCharacterBase>(ActorInfo->AvatarActor.Get());
		if(character)
		{
			character->SetSprint(true);
		}
	}
}

void UUSprintAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	if (HasAuthorityOrPredictionKey(ActorInfo, &ActivationInfo))
	{
		AMobaFlexCharacterBase* character = Cast<AMobaFlexCharacterBase>(ActorInfo->AvatarActor.Get());
		if(character)
		{
			character->SetSprint(false);
			AbilityHelper::RemoveEffect(character, GetCostGameplayEffect()->GetClass());
		}
	}
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

