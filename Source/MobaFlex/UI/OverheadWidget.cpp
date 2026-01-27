#include "OverheadWidget.h"

void UOverheadWidget::UpdateHealth(float Health, float MaxHealth) const
{
    if (HealthTextBlock)
    {
        HealthTextBlock->SetText(FText::FromString(FString::FromInt(FMath::RoundToInt(Health))));
    }
    if (HealthProgressBar)
    {
        HealthProgressBar->SetPercent(MaxHealth > 0 ? Health / MaxHealth : 0.0f);
    }
}
