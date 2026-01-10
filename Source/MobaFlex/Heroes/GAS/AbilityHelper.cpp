// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilityHelper.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "GameplayEffect.h"


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

bool AbilityHelper::AddEffect(AActor* actor, TSubclassOf<UGameplayEffect> EffectClass, bool ReplaceIfExist)
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
						return true;
					}
				}
			}
		}
	}
	return false;
}

bool AbilityHelper::RemoveEffect(AActor* actor, TSubclassOf<UGameplayEffect> EffectClass)
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
					return AbilitySystemComponent->RemoveActiveEffects(Query) > 0;
				}
			}
		}
	}
	return false;
}

bool AbilityHelper::ClearAllEffects(AActor* actor)
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
					return AbilitySystemComponent->RemoveActiveEffects(Query) > 0;
				}
			}
		}
	}
	return false;
}

FGameplayTag AbilityHelper::FindGameplayTag(FString TagName)
{
	return FGameplayTag::RequestGameplayTag(FName(TagName));
}
