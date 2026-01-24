#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "Abilities/GameplayAbility.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "MobaFlex/UI/LocalHeroWidget.h"
#include "MobaFlexCharacterBase.generated.h"

class UPlayBaseAttributeSet;

UCLASS()
class MOBAFLEX_API AMobaFlexCharacterBase : public ACharacter, public IAbilitySystemInterface
{
private:
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
	void Die();

	UFUNCTION()
	void OnMaxHealthChanged(float EffectMagnitude, float NewValue);
	void UpdateManaUI();
	void UpdateArmorUI();
	void UpdateStaminaUI();
	UFUNCTION()
	void OnMaxManaChanged(float EffectMagnitude, float NewValue);
	UFUNCTION()
	void OnMaxArmorChanged(float EffectMagnitude, float NewValue);
	UFUNCTION()
	void OnMaxStaminaChanged(float EffectMagnitude, float NewValue);
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	bool bSprint = false;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void BasicAttack();
	void JumpAbility();
	void SprintAbility_Start();
	void SprintAbility_End();
	void SetSprint(bool sprint);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	TObjectPtr<USpringArmComponent> CameraSpringArm;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	TObjectPtr<UCameraComponent> CameraInputComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	TObjectPtr<UAnimSequenceBase> DeathAnimation;

	UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	void UpdateHealthUI();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
	TObjectPtr<UPlayBaseAttributeSet> PlayBaseAttributeSet;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attribute Values")
	float Health = 100.0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attribute Values")
	float Mana = 100.0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attribute Values")
	float Stamina = 100.0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attribute Values")
	float Armor = 0.0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attribute Values")
	float MaxHealth = 100.0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attribute Values")
	float MaxMana = 100.0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attribute Values")
	float MaxStamina = 100.0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attribute Values")
	float MaxArmor = 0.0;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<ULocalHeroWidget> PlayerHUDClass;
	TObjectPtr<ULocalHeroWidget> PlayerHUD;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Abilities")
	TSubclassOf<UGameplayAbility> JumpAbilityClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Abilities")
	TSubclassOf<UGameplayAbility> SprintAbilityClass;

	
};
