#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "GameFramework/PlayerController.h"

#include "MobaFlexPlayerController.generated.h"

UCLASS()
class MOBAFLEX_API AMobaFlexPlayerController : public APlayerController
{
protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	
	void Move(const FInputActionInstance& InputActionInstance);
	void Look(const FInputActionInstance& InputActionInstance);
	void Jump(const FInputActionInstance& InputActionInstance);
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
