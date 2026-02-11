#include "LocalHeroWidget.h"

void ULocalHeroWidget::UpdateHealth(float Health, float MaxHealth) const
{
	HealthTextBlock->SetText(FText::FromString(FString::FromInt(Health)));
	HealthProgressBar->SetPercent(Health / MaxHealth);
}

void ULocalHeroWidget::UpdateMana(float Mana, float MaxMana) const
{
	ManaTextBlock->SetText(FText::FromString(FString::FromInt(Mana)));
	ManaProgressBar->SetPercent(Mana / MaxMana);
}

void ULocalHeroWidget::UpdateStamina(float Stamina, float MaxStamina) const
{
	StaminaTextBlock->SetText(FText::FromString(FString::FromInt(Stamina)));
	StaminaProgressBar->SetPercent(Stamina / MaxStamina);
}

void ULocalHeroWidget::UpdateArmor(float Armor, float MaxArmor) const
{
	ArmorTextBlock->SetText(FText::FromString(FString::FromInt(Armor)));
	ArmorProgressBar->SetPercent(Armor / MaxArmor);
}
