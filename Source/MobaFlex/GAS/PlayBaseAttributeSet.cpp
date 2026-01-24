// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayBaseAttributeSet.h"
#include "GameplayEffectExtension.h"
#include "GameplayEffectTypes.h"
#include "Net/UnrealNetwork.h"

void UPlayBaseAttributeSet::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UPlayBaseAttributeSet,Health)
	DOREPLIFETIME(UPlayBaseAttributeSet,Mana)
	DOREPLIFETIME(UPlayBaseAttributeSet,Armor)
	DOREPLIFETIME(UPlayBaseAttributeSet,Stamina)	
	DOREPLIFETIME(UPlayBaseAttributeSet,MaxHealth)
	DOREPLIFETIME(UPlayBaseAttributeSet,MaxMana)
	DOREPLIFETIME(UPlayBaseAttributeSet,MaxArmor)
	DOREPLIFETIME(UPlayBaseAttributeSet,MaxStamina)
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

