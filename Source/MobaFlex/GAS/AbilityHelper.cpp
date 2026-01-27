// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilityHelper.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "GameplayEffect.h"


void UAbilityHelperSubSystem::Server_GiveAbility_Implementation(AActor* actor, TSubclassOf<UGameplayAbility> AbilityClass, bool ActivateOnApply)
{
	if(AbilityClass)
	{
		if(AMobaFlexCharacterBase* Character = Cast<AMobaFlexCharacterBase>(actor))
		{
			if (IAbilitySystemInterface* AbilitySystemInterface = Cast<IAbilitySystemInterface>(Character))
			{
				if (UAbilitySystemComponent* AbilitySystemComponent = AbilitySystemInterface->GetAbilitySystemComponent())
				{
					FGameplayAbilitySpec AbilitySpec(AbilityClass);
					FGameplayAbilitySpecHandle specHandle = AbilitySystemComponent->GiveAbility(AbilitySpec);
					if (ActivateOnApply)
					{
						AbilitySystemComponent->TryActivateAbilityByClass(AbilityClass);
					}
					return;
				}
			}
		}
	}
}
void UAbilityHelperSubSystem::Server_RemoveAbility_Implementation(AActor* actor, TSubclassOf<UGameplayAbility> AbilityClass)
{
	if(AbilityClass)
	{
		if(AMobaFlexCharacterBase* Character = Cast<AMobaFlexCharacterBase>(actor))
		{
			if (IAbilitySystemInterface* AbilitySystemInterface = Cast<IAbilitySystemInterface>(Character))
			{
				if (UAbilitySystemComponent* AbilitySystemComponent = AbilitySystemInterface->GetAbilitySystemComponent())
				{
					FGameplayAbilitySpec* Spec = AbilitySystemComponent->FindAbilitySpecFromClass(AbilityClass);
					if (Spec && Spec->IsActive())
					{
						AbilitySystemComponent->ClearAbility(Spec->Handle);
					}
				}
			}
		}
	}
}

void UAbilityHelperSubSystem::Server_ActivateAbility_Implementation(AActor* actor, TSubclassOf<UGameplayAbility> AbilityClass)
{
	if (AbilityClass)
	{
		if(AMobaFlexCharacterBase* Character = Cast<AMobaFlexCharacterBase>(actor))
		{
			if (IAbilitySystemInterface* AbilitySystemInterface = Cast<IAbilitySystemInterface>(Character))
			{
				if (UAbilitySystemComponent* AbilitySystemComponent = AbilitySystemInterface->GetAbilitySystemComponent())
				{
					AbilitySystemComponent->TryActivateAbilityByClass(AbilityClass);
				}
			}
		}
	}
}

void UAbilityHelperSubSystem::Server_DeactivateAbility_Implementation(AActor* actor, TSubclassOf<UGameplayAbility> AbilityClass)
{
 	if (AbilityClass)
	{
 		if(AMobaFlexCharacterBase* Character = Cast<AMobaFlexCharacterBase>(actor))
 		{
 			if (IAbilitySystemInterface* AbilitySystemInterface = Cast<IAbilitySystemInterface>(Character))
 			{
 				if (UAbilitySystemComponent* AbilitySystemComponent = AbilitySystemInterface->GetAbilitySystemComponent())
 				{
 					FGameplayAbilitySpec* Spec = AbilitySystemComponent->FindAbilitySpecFromClass(AbilityClass);
 					if (Spec && Spec->IsActive())
 					{
 						AbilitySystemComponent->CancelAbilityHandle(Spec->Handle);
 					}
 				}
 			}
 		}
	}
}

void UAbilityHelperSubSystem::Server_AddEffect_Implementation(AActor* actor, TSubclassOf<UGameplayEffect> EffectClass, bool ReplaceIfExist)
{
	if(EffectClass)
	{
		if(AMobaFlexCharacterBase* Character = Cast<AMobaFlexCharacterBase>(actor))
		{
			if (IAbilitySystemInterface* AbilitySystemInterface = Cast<IAbilitySystemInterface>(Character))
			{
				if (UAbilitySystemComponent* AbilitySystemComponent = AbilitySystemInterface->GetAbilitySystemComponent())
				{
                    if(ReplaceIfExist)
                    {
                        FGameplayEffectQuery Query;
                        Query.EffectDefinition = EffectClass;
                        AbilitySystemComponent->RemoveActiveEffects(Query);
                    }

					FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
					EffectContext.AddSourceObject(actor);
					FGameplayEffectSpecHandle SpecHandle = AbilitySystemComponent->MakeOutgoingSpec(EffectClass, 1, EffectContext);
					if(SpecHandle.IsValid())
					{
						AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
						return;
					}
				}
			}
		}
	}
	return;
}

void UAbilityHelperSubSystem::Server_RemoveEffect_Implementation(AActor* actor, TSubclassOf<UGameplayEffect> EffectClass)
{
	if(EffectClass)
	{
		if(AMobaFlexCharacterBase* Character = Cast<AMobaFlexCharacterBase>(actor))
		{
			if (IAbilitySystemInterface* AbilitySystemInterface = Cast<IAbilitySystemInterface>(Character))
			{
				if (UAbilitySystemComponent* AbilitySystemComponent = AbilitySystemInterface->GetAbilitySystemComponent())
				{
					FGameplayEffectQuery Query;
                    Query.EffectDefinition = EffectClass;
					AbilitySystemComponent->RemoveActiveEffects(Query);
				}
			}
		}
	}
}

void UAbilityHelperSubSystem::Server_ClearAllEffects_Implementation(AActor* actor)
{
	if(actor)
	{
		if(AMobaFlexCharacterBase* Character = Cast<AMobaFlexCharacterBase>(actor))
		{
			if (IAbilitySystemInterface* AbilitySystemInterface = Cast<IAbilitySystemInterface>(Character))
			{
				if (UAbilitySystemComponent* AbilitySystemComponent = AbilitySystemInterface->GetAbilitySystemComponent())
				{
					FGameplayEffectQuery Query;
					AbilitySystemComponent->RemoveActiveEffects(Query);
				}
			}
		}
	}
}

FGameplayTag UAbilityHelperSubSystem::FindGameplayTag(FString TagName)
{
	return FGameplayTag::RequestGameplayTag(FName(TagName));
}
