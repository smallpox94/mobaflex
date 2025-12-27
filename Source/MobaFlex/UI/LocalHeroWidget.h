#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "LocalHeroWidget.generated.h"

UCLASS()
class MOBAFLEX_API ULocalHeroWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> HealthTextBlock;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> ManaTextBlock;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> StaminaTextBlock;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> ArmorTextBlock;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UProgressBar> HealthProgressBar;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UProgressBar> ManaProgressBar;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UProgressBar> StaminaProgressBar;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UProgressBar> ArmorProgressBar;
public:
	void UpdateHealth(float Health, float MaxHealth) const;
	void UpdateMana(float Mana, float MaxMana) const;
	void UpdateStamina(float Stamina, float MaxStamina) const;
	void UpdateArmor(float Armor, float MaxArmor) const;
};
