// Fill out your copyright notice in the Description page of Project Settings.


#include "LocalPlayerMVVM.h"

float ULocalPlayerMVVM::GetHealthPercent() const
{
	ensure(MaxHealth != 0);
	return Health / MaxHealth;
}

FText ULocalPlayerMVVM::GetHealthInt() const
{
	return FText::FromString(FString::FromInt(FMath::CeilToInt(Health)));
}

void ULocalPlayerMVVM::SetHealth(float NewHealth)
{
	if (UE_MVVM_SET_PROPERTY_VALUE(Health, NewHealth))
	{
		UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(GetHealthPercent);
		UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(GetHealthInt);
	}
}

void ULocalPlayerMVVM::SetMaxHealth(float NewMaxHealth)
{
	if (UE_MVVM_SET_PROPERTY_VALUE(MaxHealth, NewMaxHealth))
	{
		UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(GetHealthPercent);
	}
}

float ULocalPlayerMVVM::GetStaminaPercent() const
{
	ensure(MaxStamina != 0);
	return Stamina / MaxStamina;
}

FText ULocalPlayerMVVM::GetStaminaInt() const
{
	return FText::FromString(FString::FromInt(FMath::CeilToInt(Stamina)));
}

void ULocalPlayerMVVM::SetStamina(float NewStamina)
{
	if (UE_MVVM_SET_PROPERTY_VALUE(Stamina, NewStamina))
	{
		UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(GetStaminaPercent);
		UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(GetStaminaInt);
	}
}

void ULocalPlayerMVVM::SetMaxStamina(float NewMaxStamina)
{
	if (UE_MVVM_SET_PROPERTY_VALUE(MaxStamina, NewMaxStamina))
	{
		UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(GetStaminaPercent);
	}
}

float ULocalPlayerMVVM::GetManaPercent() const
{
	ensure(MaxMana != 0);
	return Mana / MaxMana;
}

FText ULocalPlayerMVVM::GetManaInt() const
{
	return FText::FromString(FString::FromInt(FMath::CeilToInt(Mana)));
}

float ULocalPlayerMVVM::GetArmorPercent() const
{
	ensure(MaxArmor != 0);
	return Armor / MaxArmor;
}

FText ULocalPlayerMVVM::GetArmorInt() const
{
	return FText::FromString(FString::FromInt(FMath::CeilToInt(Armor)));
}

void ULocalPlayerMVVM::SetMana(float NewMana)
{
	if (UE_MVVM_SET_PROPERTY_VALUE(Mana, NewMana))
	{
		UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(GetManaPercent);
		UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(GetManaInt);
	}
}

void ULocalPlayerMVVM::SetMaxMana(float NewMaxMana)
{
	if (UE_MVVM_SET_PROPERTY_VALUE(MaxMana, NewMaxMana))
	{
		UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(GetManaPercent);
	}
}

void ULocalPlayerMVVM::SetArmor(float NewArmor)
{
	if (UE_MVVM_SET_PROPERTY_VALUE(Armor, NewArmor))
	{
		UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(GetArmorPercent);
		UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(GetArmorInt);
	}
}

void ULocalPlayerMVVM::SetMaxArmor(float NewMaxArmor)
{
	if (UE_MVVM_SET_PROPERTY_VALUE(MaxArmor, NewMaxArmor))
	{
		UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(GetArmorPercent);
	}
}
