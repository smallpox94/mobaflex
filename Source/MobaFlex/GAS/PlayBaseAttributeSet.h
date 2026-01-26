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
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	
	UPROPERTY(BlueprintReadOnly, Replicated, ReplicatedUsing="OnRep_Health",Category = "Attributes")
	FGameplayAttributeData Health;
	PLAY_ATTRIBUTE_ACCESSORS(UPlayBaseAttributeSet, Health);
	UFUNCTION()
	void OnRep_Health();
	
	UPROPERTY(BlueprintReadOnly, Replicated, ReplicatedUsing="OnRep_MaxHealth",Category = "Attributes")
	FGameplayAttributeData MaxHealth;
	PLAY_ATTRIBUTE_ACCESSORS(UPlayBaseAttributeSet, MaxHealth);
	UFUNCTION()
	void OnRep_MaxHealth();
    	
	UPROPERTY(BlueprintReadOnly, Replicated, ReplicatedUsing="OnRep_Armor",Category = "Attributes")
	FGameplayAttributeData Armor;
	PLAY_ATTRIBUTE_ACCESSORS(UPlayBaseAttributeSet, Armor);
	UFUNCTION()
	void OnRep_Armor();
	
	UPROPERTY(BlueprintReadOnly, Replicated, ReplicatedUsing="OnRep_MaxArmor",Category = "Attributes")
	FGameplayAttributeData MaxArmor;
	PLAY_ATTRIBUTE_ACCESSORS(UPlayBaseAttributeSet, MaxArmor);
	UFUNCTION()
	void OnRep_MaxArmor();
	
	UPROPERTY(BlueprintReadOnly, Replicated, ReplicatedUsing="OnRep_Mana",Category = "Attributes")
	FGameplayAttributeData Mana;
	PLAY_ATTRIBUTE_ACCESSORS(UPlayBaseAttributeSet, Mana);
	UFUNCTION()
	void OnRep_Mana();
	
	UPROPERTY(BlueprintReadOnly, Replicated, ReplicatedUsing="OnRep_MaxMana",Category = "Attributes")
	FGameplayAttributeData MaxMana;
	PLAY_ATTRIBUTE_ACCESSORS(UPlayBaseAttributeSet, MaxMana);
	UFUNCTION()
	void OnRep_MaxMana();
	
	UPROPERTY(BlueprintReadOnly, Replicated, ReplicatedUsing="OnRep_Stamina",Category = "Attributes")
	FGameplayAttributeData Stamina;
	PLAY_ATTRIBUTE_ACCESSORS(UPlayBaseAttributeSet, Stamina);
	UFUNCTION()
	void OnRep_Stamina();
	
	UPROPERTY(BlueprintReadOnly, Replicated, ReplicatedUsing="OnRep_MaxStamina",Category = "Attributes")
	FGameplayAttributeData MaxStamina;
	PLAY_ATTRIBUTE_ACCESSORS(UPlayBaseAttributeSet, MaxStamina);
	UFUNCTION()
	void OnRep_MaxStamina();
};
