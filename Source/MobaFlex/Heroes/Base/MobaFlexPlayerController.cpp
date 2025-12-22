#include "MobaFlexPlayerController.h"

#include "EnhancedInputComponent.h"
#include "MobaFlexCharacterBase.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"


void AMobaFlexPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (ULocalPlayer* localPlayer = GetLocalPlayer())
	{
		if (UEnhancedInputLocalPlayerSubsystem* InputSubSystem = localPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			InputSubSystem->AddMappingContext(InputMapping,0);
		}
	}
}

void AMobaFlexPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInput->BindAction(this->MoveAction, ETriggerEvent::Triggered, this, &AMobaFlexPlayerController::Move);
		EnhancedInput->BindAction(this->LookAction, ETriggerEvent::Triggered, this, &AMobaFlexPlayerController::Look);
		EnhancedInput->BindAction(this->JumpAction, ETriggerEvent::Triggered, this, &AMobaFlexPlayerController::Jump);
		EnhancedInput->BindAction(this->BasicAttackAction, ETriggerEvent::Triggered, this, &AMobaFlexPlayerController::BasicAttack);
	}
}

void AMobaFlexPlayerController::Move(const FInputActionInstance& InputActionInstance)
{
	FVector2D InputValue = InputActionInstance.GetValue().Get<FVector2D>();
	if (APawn* pawn = GetPawn())
	{
		FRotator rotator = FRotator(0.0f, GetControlRotation().Yaw, 0.0f);
		FVector forwardVector = rotator.Vector();
		FVector rightVector = UKismetMathLibrary::GetRightVector(rotator);
		FVector finalVector = forwardVector * InputValue.X + rightVector * InputValue.Y;
		pawn->AddMovementInput(finalVector);
	}
}

void AMobaFlexPlayerController::Look(const FInputActionInstance& InputActionInstance)
{
	FVector2D InputValue = InputActionInstance.GetValue().Get<FVector2D>();
	double deltaSec = UGameplayStatics::GetWorldDeltaSeconds(GetWorld());
	AddYawInput(InputValue.X * deltaSec * TurnRate);
	AddPitchInput(InputValue.Y * deltaSec * LookUp);
}

void AMobaFlexPlayerController::Jump(const FInputActionInstance& InputActionInstance)
{
	if (ACharacter* character = Cast<ACharacter>(GetPawn()))
	{
		character->Jump();
	}
}

void AMobaFlexPlayerController::BasicAttack(const FInputActionInstance& InputActionInstance)
{
	if (AMobaFlexCharacterBase* mobaCharacter = Cast<AMobaFlexCharacterBase>(GetPawn()))
	{
		mobaCharacter->BasicAttack();
	}
}

