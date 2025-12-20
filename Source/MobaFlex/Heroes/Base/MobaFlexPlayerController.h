// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputMappingContext.h"
#include "GameFramework/PlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "MobaFlexPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class MOBAFLEX_API AMobaFlexPlayerController : public APlayerController
{
protected:
	virtual void SetupInputComponent() override;

	virtual void BeginPlay() override;

private:
	GENERATED_BODY()

public:
	// *** Current Mapping Context ***
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputMappingContext* InputMapping;
	// *** Input Actions ***
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UInputAction> MoveAction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UInputAction> LookAction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UInputAction> JumpAction;
};
