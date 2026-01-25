// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayBaseAttributeSet.h"
#include "GameplayEffectExtension.h"
#include "GameplayEffectTypes.h"
#include "Net/UnrealNetwork.h"

void UPlayBaseAttributeSet::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UPlayBaseAttributeSet,Health, COND_None, REPNOTIFY_Always)
	DOREPLIFETIME_CONDITION_NOTIFY(UPlayBaseAttributeSet,Mana, COND_None, REPNOTIFY_Always)
	DOREPLIFETIME_CONDITION_NOTIFY(UPlayBaseAttributeSet,Armor, COND_None, REPNOTIFY_Always)
	DOREPLIFETIME_CONDITION_NOTIFY(UPlayBaseAttributeSet,Stamina, COND_None, REPNOTIFY_Always)	
	DOREPLIFETIME_CONDITION_NOTIFY(UPlayBaseAttributeSet,MaxHealth, COND_None, REPNOTIFY_Always)
	DOREPLIFETIME_CONDITION_NOTIFY(UPlayBaseAttributeSet,MaxMana, COND_None, REPNOTIFY_Always)
	DOREPLIFETIME_CONDITION_NOTIFY(UPlayBaseAttributeSet,MaxArmor, COND_None, REPNOTIFY_Always)
	DOREPLIFETIME_CONDITION_NOTIFY(UPlayBaseAttributeSet,MaxStamina, COND_None, REPNOTIFY_Always)
}

void UPlayBaseAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
	
	BROADCAST_ATTRIBUTE_CHANGED_EVENT_WITH_TAG(Health)
	BROADCAST_ATTRIBUTE_CHANGED_EVENT(MaxHealth)
	BROADCAST_ATTRIBUTE_CHANGED_EVENT_WITH_TAG(Mana)
	BROADCAST_ATTRIBUTE_CHANGED_EVENT(MaxMana)
	BROADCAST_ATTRIBUTE_CHANGED_EVENT_WITH_TAG(Armor)
	BROADCAST_ATTRIBUTE_CHANGED_EVENT(MaxArmor)
	BROADCAST_ATTRIBUTE_CHANGED_EVENT_WITH_TAG(Stamina)
	BROADCAST_ATTRIBUTE_CHANGED_EVENT(MaxStamina)
}

void UPlayBaseAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

}

