// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayBaseAttributeSet.h"
#include "GameplayEffectExtension.h"
#include "GameplayEffectTypes.h"

void UPlayBaseAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
	
	BROADCAST_ATTRIBUTECHANGED_EVENT(Health)
	BROADCAST_ATTRIBUTECHANGED_EVENT(Mana)
	BROADCAST_ATTRIBUTECHANGED_EVENT(Armor)
	BROADCAST_ATTRIBUTECHANGED_EVENT(Stamina)
}
