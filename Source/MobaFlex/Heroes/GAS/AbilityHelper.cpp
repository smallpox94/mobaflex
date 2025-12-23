// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilityHelper.h"


bool AbilityHelper::GiveAbility(AActor* actor, TSubclassOf<UGameplayAbility> AbilityClass, bool ActivateOnApply)
{
	if(AbilityClass)
	{
		if(AMobaFlexCharacterBase* Character = Cast<AMobaFlexCharacterBase>(actor))
		{
			if (IAbilitySystemInterface* AbilitySystemInterface = Cast<IAbilitySystemInterface>(Character))
			{
				if (UAbilitySystemComponent* AbilitySystemComponent = AbilitySystemInterface->GetAbilitySystemComponent())
				{
					if (AbilityClass)
					{
						FGameplayAbilitySpec AbilitySpec(AbilityClass);
						FGameplayAbilitySpecHandle specHandle = AbilitySystemComponent->GiveAbility(AbilitySpec);
						if (ActivateOnApply)
						{
							return AbilitySystemComponent->TryActivateAbilityByClass(AbilityClass);
						}
						return true;
					}
				}
			}
		}
	}
	return false;
}
bool AbilityHelper::RemoveAbility(AActor* actor, TSubclassOf<UGameplayAbility> AbilityClass)
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
						return true;
					}
				}
			}
		}
	}
	return false;
}

bool AbilityHelper::ActivateAbility(AActor* actor, TSubclassOf<UGameplayAbility> AbilityClass)
{
	if (AbilityClass)
	{
		if(AMobaFlexCharacterBase* Character = Cast<AMobaFlexCharacterBase>(actor))
		{
			if (IAbilitySystemInterface* AbilitySystemInterface = Cast<IAbilitySystemInterface>(Character))
			{
				if (UAbilitySystemComponent* AbilitySystemComponent = AbilitySystemInterface->GetAbilitySystemComponent())
				{
					return AbilitySystemComponent->TryActivateAbilityByClass(AbilityClass);
				}
			}
		}
	}
	return false;
}

bool AbilityHelper::DeactivateAbility(AActor* actor, TSubclassOf<UGameplayAbility> AbilityClass)
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
 						return true;
 					}
 				}
 			}
 		}
	}
	return false;
}
