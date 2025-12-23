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
private:
	GENERATED_BODY()

public:
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayAttributeData Health;
	PLAY_ATTRIBUTE_ACCESSORS(UPlayBaseAttributeSet, Health);

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayAttributeData Armor;
	PLAY_ATTRIBUTE_ACCESSORS(UPlayBaseAttributeSet, Armor);
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayAttributeData Mana;
	PLAY_ATTRIBUTE_ACCESSORS(UPlayBaseAttributeSet, Mana);
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayAttributeData Stamina;
	PLAY_ATTRIBUTE_ACCESSORS(UPlayBaseAttributeSet, Stamina);
};
