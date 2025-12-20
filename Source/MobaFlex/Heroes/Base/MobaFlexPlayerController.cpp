#include "MobaFlexPlayerController.h"

#include "EnhancedInputComponent.h"

void AMobaFlexPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (ULocalPlayer* localPlayer = GetLocalPlayer())
	{
		if (UEnhancedInputLocalPlayerSubsystem* InputSubSystem = localPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			InputSubSystem->AddMappingContext(InputMapping, 0);
			
		}
	}
}

void AMobaFlexPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(InputComponent);

	EnhancedInput->BindAction(this->MoveAction, ETriggerEvent::Triggered, this, &AMobaFlexPlayerController::Move);
	EnhancedInput->BindAction(this->LookAction, ETriggerEvent::Triggered, this, &AMobaFlexPlayerController::Look);
	EnhancedInput->BindAction(this->JumpAction, ETriggerEvent::Triggered, this, &AMobaFlexPlayerController::Jump);
}

void AMobaFlexPlayerController::Move(const FInputActionInstance& InputActionInstance)
{
	
}

void AMobaFlexPlayerController::Look(const FInputActionInstance& InputActionInstance)
{
	
}

void AMobaFlexPlayerController::Jump(const FInputActionInstance& InputActionInstance)
{
	
}

