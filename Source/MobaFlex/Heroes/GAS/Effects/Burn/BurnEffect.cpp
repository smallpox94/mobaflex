// Fill out your copyright notice in the Description page of Project Settings.


#include "BurnEffect.h"

#include "MobaFlex/Heroes/GAS/PlayBaseAttributeSet.h"

UBurnEffect::UBurnEffect()
{
	DurationPolicy = EGameplayEffectDurationType::HasDuration;
	DurationMagnitude = FGameplayEffectModifierMagnitude(FScalableFloat(5.0f));
	Period = 1.0f;

	FGameplayModifierInfo HealthModifierInfo;
	HealthModifierInfo.ModifierOp = EGameplayModOp::Additive;
	HealthModifierInfo.Attribute = UPlayBaseAttributeSet::GetHealthAttribute();
	HealthModifierInfo.ModifierMagnitude = FScalableFloat(-5.0f);

	FGameplayModifierInfo StaminaModifierInfo;
	HealthModifierInfo.ModifierOp = EGameplayModOp::Additive;
	HealthModifierInfo.Attribute = UPlayBaseAttributeSet::GetStaminaAttribute();
	HealthModifierInfo.ModifierMagnitude = FScalableFloat(-10.0f);

	Modifiers.Add(HealthModifierInfo);
	Modifiers.Add(StaminaModifierInfo);
}
