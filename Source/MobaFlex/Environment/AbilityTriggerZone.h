// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseTriggerZone.h"
#include "GameplayAbilitySpec.h"
#include "GameplayEffect.h"
#include "AbilityTriggerZone.generated.h"

class UGameplayAbility;

UCLASS()
class MOBAFLEX_API AAbilityTriggerZone : public ABaseTriggerZone
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AAbilityTriggerZone();

protected:
	virtual void HandleOverlapBegin(AActor* OtherActor, const FHitResult& SweepResult) override;
	virtual void HandleOverlapEnd(AActor* OtherActor) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects")
	TArray<TSubclassOf<UGameplayEffect>> EffectsEntering;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects")
	bool RemoveEnteringEffectsOnExist = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects")
	TArray<TSubclassOf<UGameplayEffect>> EffectsLeaving;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool ActivateOnApplying = true;

private:
};
