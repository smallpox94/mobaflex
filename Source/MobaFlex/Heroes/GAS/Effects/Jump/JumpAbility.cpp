// Fill out your copyright notice in the Description page of Project Settings.


#include "JumpAbility.h"

#include "MobaFlex/Heroes/Base/MobaFlexCharacterBase.h"

UJumpAbility::UJumpAbility()
{
	
}

bool UJumpAbility::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, FGameplayTagContainer* OptionalRelevantTags) const
{
	if (!Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags))
	{
		return false;
	}
	const AMobaFlexCharacterBase* character = Cast<AMobaFlexCharacterBase>(ActorInfo->AvatarActor.Get());
	return character && character->CanJump();
}

void UJumpAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	if (HasAuthorityOrPredictionKey(ActorInfo, &ActivationInfo))
	{
		if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
		{
			EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
		}
		AMobaFlexCharacterBase* character = Cast<AMobaFlexCharacterBase>(ActorInfo->AvatarActor.Get());
		character->Jump();
	}
}


void UJumpAbility::CancelAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateCancelAbility)
{
	if (ScopeLockCount > 0)
	{
		WaitingToExecute.Add(FPostLockDelegate::CreateUObject(this, &UJumpAbility::CancelAbility, Handle, ActorInfo, ActivationInfo, bReplicateCancelAbility));
		return;
	}
	
	Super::CancelAbility(Handle, ActorInfo, ActivationInfo, bReplicateCancelAbility);

	AMobaFlexCharacterBase* character = Cast<AMobaFlexCharacterBase>(ActorInfo->AvatarActor.Get());
	character->StopJumping();
}

