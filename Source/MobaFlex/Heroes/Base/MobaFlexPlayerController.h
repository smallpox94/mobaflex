#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "GameFramework/PlayerController.h"

#include "MobaFlexPlayerController.generated.h"

UCLASS()
class MOBAFLEX_API AMobaFlexPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	
	void Move(const FInputActionInstance& InputActionInstance);
	void Look(const FInputActionInstance& InputActionInstance);
	void Jump(const FInputActionInstance& InputActionInstance);
	void BasicAttack(const FInputActionInstance& InputActionInstance);

public:
	// *** Input Parameters
	double TurnRate = 45.0f;
	double LookUp = 45.0f;
	
	// *** Current Mapping Context ***
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputMappingContext* InputMapping;
	// *** Input Actions ***
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	TObjectPtr<UInputAction> MoveAction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	TObjectPtr<UInputAction> LookAction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	TObjectPtr<UInputAction> JumpAction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	TObjectPtr<UInputAction> BasicAttackAction;
};
