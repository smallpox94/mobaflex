#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "OverheadWidget.generated.h"

UCLASS()
class MOBAFLEX_API UOverheadWidget : public UUserWidget
{
    GENERATED_BODY()

protected:
    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UProgressBar> HealthProgressBar;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UTextBlock> HealthTextBlock;

public:
    void UpdateHealth(float Health, float MaxHealth) const;
};
