// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CoreUObject.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "AttributeSetMacro.h"
#include "AbilityHelper.h"
#include "PlayBaseAttributeSet.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FPlayAttributeEvent, float, EffectMagnitude, float, NewValue);

UCLASS()
class MOBAFLEX_API UPlayBaseAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	
public:
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	
	UPROPERTY(BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData Health;
	PLAY_ATTRIBUTE_ACCESSORS(UPlayBaseAttributeSet, Health);
	UPROPERTY(BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData MaxHealth;
	PLAY_ATTRIBUTE_ACCESSORS(UPlayBaseAttributeSet, MaxHealth);
	
	UPROPERTY(BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData Armor;
	PLAY_ATTRIBUTE_ACCESSORS(UPlayBaseAttributeSet, Armor);
	UPROPERTY(BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData MaxArmor;
	PLAY_ATTRIBUTE_ACCESSORS(UPlayBaseAttributeSet, MaxArmor);
	
	UPROPERTY(BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData Mana;
	PLAY_ATTRIBUTE_ACCESSORS(UPlayBaseAttributeSet, Mana);
	UPROPERTY(BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData MaxMana;
	PLAY_ATTRIBUTE_ACCESSORS(UPlayBaseAttributeSet, MaxMana);
	
	UPROPERTY(BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData Stamina;
	PLAY_ATTRIBUTE_ACCESSORS(UPlayBaseAttributeSet, Stamina);
	UPROPERTY(BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData MaxStamina;
	PLAY_ATTRIBUTE_ACCESSORS(UPlayBaseAttributeSet, MaxStamina);

};
