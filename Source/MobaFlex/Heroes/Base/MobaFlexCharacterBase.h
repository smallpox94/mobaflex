#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "MobaFlex/Heroes/GAS/PlayBaseAttributeSet.h"
#include "MobaFlexCharacterBase.generated.h"

UCLASS()
class MOBAFLEX_API AMobaFlexCharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMobaFlexCharacterBase();

protected:
	UFUNCTION()
	virtual void OnHealthChanged(float EffectMagnitude, float NewValue);
	UFUNCTION()
	virtual void OnManaChanged(float EffectMagnitude, float NewValue);
	UFUNCTION()
	virtual void OnArmorChanged(float EffectMagnitude, float NewValue);
	UFUNCTION()
	void OnStaminaChanged(float EffectMagnitude, float NewValue);
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void BasicAttack();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	TObjectPtr<USpringArmComponent> CameraSpringArm;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	TObjectPtr<UCameraComponent> CameraInputComponent;

	UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
	TObjectPtr<UPlayBaseAttributeSet> PlayBaseAttributeSet;
};
