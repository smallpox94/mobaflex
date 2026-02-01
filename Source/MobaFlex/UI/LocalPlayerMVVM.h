// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MVVMViewModelBase.h"

#include "LocalPlayerMVVM.generated.h"

/**
 * 
 */
UCLASS()
class MOBAFLEX_API ULocalPlayerMVVM : public UMVVMViewModelBase
{
	GENERATED_BODY()
protected:
	UPROPERTY(BlueprintReadWrite, FieldNotify, Setter, Getter)
	float Health = 100.0f;
	UPROPERTY(BlueprintReadWrite, FieldNotify, Setter, Getter)
	float MaxHealth = 100.0f;
	UPROPERTY(BlueprintReadWrite, FieldNotify, Setter, Getter)
	float Stamina = 100.0f;
	UPROPERTY(BlueprintReadWrite, FieldNotify, Setter, Getter)
	float MaxStamina = 100.0f;
	UPROPERTY(BlueprintReadWrite, FieldNotify, Setter, Getter)
	float Mana = 100.0f;
	UPROPERTY(BlueprintReadWrite, FieldNotify, Setter, Getter)
	float MaxMana = 100.0f;
	UPROPERTY(BlueprintReadWrite, FieldNotify, Setter, Getter)
	float Armor = 100.0f;
	UPROPERTY(BlueprintReadWrite, FieldNotify, Setter, Getter)
	float MaxArmor = 100.0f;
	
	UFUNCTION(BlueprintPure, FieldNotify)
	float GetHealthPercent() const;
	UFUNCTION(BlueprintPure, FieldNotify)
	FText GetHealthInt() const;
	UFUNCTION(BlueprintPure, FieldNotify)
	float GetStaminaPercent() const;
	UFUNCTION(BlueprintPure, FieldNotify)
	FText GetStaminaInt() const;
	UFUNCTION(BlueprintPure, FieldNotify)
	float GetManaPercent() const;
	UFUNCTION(BlueprintPure, FieldNotify)
	FText GetManaInt() const;
	UFUNCTION(BlueprintPure, FieldNotify)
	float GetArmorPercent() const;
	UFUNCTION(BlueprintPure, FieldNotify)
	FText GetArmorInt() const;
public:
	float GetHealth() const {return Health;}
	float GetMaxHealth() const {return MaxHealth;}
	void SetHealth(float NewHealth);
	void SetMaxHealth(float NewMaxHealth);
	
	float GetStamina() const {return Stamina;}
	float GetMaxStamina() const {return MaxStamina;}
	void SetStamina(float NewStamina);
	void SetMaxStamina(float NewMaxStamina);
	
	float GetMana() const {return Mana;}
	float GetMaxMana() const {return MaxMana;}
	void SetMana(float NewMana);
	void SetMaxMana(float NewMaxMana);
	
	float GetArmor() const {return Armor;}
	float GetMaxArmor() const {return MaxArmor;}
	void SetArmor(float NewArmor);
	void SetMaxArmor(float NewMaxArmor);
};