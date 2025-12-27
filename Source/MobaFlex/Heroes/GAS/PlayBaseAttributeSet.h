// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CoreUObject.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "AttributeSetMacro.h"
#include "PlayBaseAttributeSet.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FPlayAttributeEvent, float, EffectMagnitude, float, NewValue);

UCLASS()
class MOBAFLEX_API UPlayBaseAttributeSet : public UAttributeSet
{
public:
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

private:
	GENERATED_BODY()

public:
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayAttributeData Health;
	PLAY_ATTRIBUTE_ACCESSORS(UPlayBaseAttributeSet, Health);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayAttributeData MaxHealth;
	PLAY_ATTRIBUTE_ACCESSORS(UPlayBaseAttributeSet, MaxHealth);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayAttributeData Armor;
	PLAY_ATTRIBUTE_ACCESSORS(UPlayBaseAttributeSet, Armor);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayAttributeData MaxArmor;
	PLAY_ATTRIBUTE_ACCESSORS(UPlayBaseAttributeSet, MaxArmor);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayAttributeData Mana;
	PLAY_ATTRIBUTE_ACCESSORS(UPlayBaseAttributeSet, Mana);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayAttributeData MaxMana;
	PLAY_ATTRIBUTE_ACCESSORS(UPlayBaseAttributeSet, MaxMana);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayAttributeData Stamina;
	PLAY_ATTRIBUTE_ACCESSORS(UPlayBaseAttributeSet, Stamina);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayAttributeData MaxStamina;
	PLAY_ATTRIBUTE_ACCESSORS(UPlayBaseAttributeSet, MaxStamina);
};
