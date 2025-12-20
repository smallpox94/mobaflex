// Fill out your copyright notice in the Description page of Project Settings.


#include "MobaFlexPlayerController.h"

void AMobaFlexPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	
}

void AMobaFlexPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (ULocalPlayer* localPlayer = GetLocalPlayer())
	{
		if (UEnhancedInputLocalPlayerSubsystem* InputComponent = localPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			InputComponent->AddMappingContext(InputMapping, 0);
		}
	}
}
