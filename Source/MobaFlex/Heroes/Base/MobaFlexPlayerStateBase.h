// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "GameFramework/PlayerState.h"
#include "MobaFlexPlayerStateBase.generated.h"

/**
 * 
 */
UCLASS()
class MOBAFLEX_API AMobaFlexPlayerStateBase : public APlayerState
{
	GENERATED_BODY()
	
public:
	AMobaFlexPlayerStateBase();

	UFUNCTION(BlueprintCallable)
	UAbilitySystemComponent* GetAbilitySystemComponent() const { return AbilitySystemComponent; }
protected:
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
};
