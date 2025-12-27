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
	
	BROADCAST_ATTRIBUTECHANGED_EVENT(Health)
	BROADCAST_ATTRIBUTECHANGED_EVENT(Mana)
	BROADCAST_ATTRIBUTECHANGED_EVENT(Armor)
	BROADCAST_ATTRIBUTECHANGED_EVENT(Stamina)
	BROADCAST_ATTRIBUTECHANGED_EVENT(MaxHealth)
	BROADCAST_ATTRIBUTECHANGED_EVENT(MaxMana)
	BROADCAST_ATTRIBUTECHANGED_EVENT(MaxArmor)
	BROADCAST_ATTRIBUTECHANGED_EVENT(MaxStamina)
}
