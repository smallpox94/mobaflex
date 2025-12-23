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
	StaminaModifierInfo.ModifierOp = EGameplayModOp::Additive;
	StaminaModifierInfo.Attribute = UPlayBaseAttributeSet::GetStaminaAttribute();
	StaminaModifierInfo.ModifierMagnitude = FScalableFloat(-10.0f);

	Modifiers.Add(HealthModifierInfo);
	Modifiers.Add(StaminaModifierInfo);
}
