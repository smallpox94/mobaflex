#include "MobaFlexCharacterBase.h"

#include "AbilitySystemComponent.h"
#include "MobaFlexPlayerController.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "MobaFlex/GAS/PlayBaseAttributeSet.h"

// Sets default values
AMobaFlexCharacterBase::AMobaFlexCharacterBase()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	CameraSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraSpringArm"));
	CameraSpringArm->SetupAttachment(GetCapsuleComponent());
	CameraSpringArm->bUsePawnControlRotation = true;
	CameraSpringArm->TargetOffset = FVector(0.0f,0.0f,0.0f);
	CameraSpringArm->TargetArmLength = 350.0f;

	CameraInputComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraInputComponent->SetupAttachment(CameraSpringArm);

	USkeletalMeshComponent* SkeletalMeshComponent = GetMesh();
	SkeletalMeshComponent->SetRelativeLocation(FVector(0.0f, 0.0f, -90.0f));
	SkeletalMeshComponent->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));

	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	PlayBaseAttributeSet = CreateDefaultSubobject<UPlayBaseAttributeSet>(TEXT("PlayBaseAttributeSet"));
}

// Called when the game starts or when spawned
void AMobaFlexCharacterBase::BeginPlay()
{
	Super::BeginPlay();

	if(AbilitySystemComponent)
	{
		AbilitySystemComponent->InitAbilityActorInfo(this, this);
		if(PlayBaseAttributeSet)
		{
			PlayBaseAttributeSet->OnHealthChanged.AddDynamic(this, &AMobaFlexCharacterBase::OnHealthChanged);
			PlayBaseAttributeSet->OnManaChanged.AddDynamic(this, &AMobaFlexCharacterBase::OnManaChanged);
			PlayBaseAttributeSet->OnArmorChanged.AddDynamic(this, &AMobaFlexCharacterBase::OnArmorChanged);
			PlayBaseAttributeSet->OnStaminaChanged.AddDynamic(this, &AMobaFlexCharacterBase::OnStaminaChanged);
			PlayBaseAttributeSet->OnMaxHealthChanged.AddDynamic(this, &AMobaFlexCharacterBase::OnMaxHealthChanged);
			PlayBaseAttributeSet->OnMaxManaChanged.AddDynamic(this, &AMobaFlexCharacterBase::OnMaxManaChanged);
			PlayBaseAttributeSet->OnMaxArmorChanged.AddDynamic(this, &AMobaFlexCharacterBase::OnMaxArmorChanged);
			PlayBaseAttributeSet->OnMaxStaminaChanged.AddDynamic(this, &AMobaFlexCharacterBase::OnMaxStaminaChanged);
			
			PlayBaseAttributeSet->Health.SetBaseValue(Health);
			PlayBaseAttributeSet->Mana.SetBaseValue(Mana);
			PlayBaseAttributeSet->Stamina.SetBaseValue(Stamina);
			PlayBaseAttributeSet->Armor.SetBaseValue(Armor);
			PlayBaseAttributeSet->MaxHealth.SetBaseValue(MaxHealth);
			PlayBaseAttributeSet->MaxMana.SetBaseValue(MaxMana);
			PlayBaseAttributeSet->MaxStamina.SetBaseValue(MaxStamina);
			PlayBaseAttributeSet->MaxArmor.SetBaseValue(MaxArmor);
			
			PlayBaseAttributeSet->Health.SetCurrentValue(Health);
			PlayBaseAttributeSet->Mana.SetCurrentValue(Mana);
			PlayBaseAttributeSet->Stamina.SetCurrentValue(Stamina);
			PlayBaseAttributeSet->Armor.SetCurrentValue(Armor);
			PlayBaseAttributeSet->MaxHealth.SetCurrentValue(MaxHealth);
			PlayBaseAttributeSet->MaxMana.SetCurrentValue(MaxMana);
			PlayBaseAttributeSet->MaxStamina.SetCurrentValue(MaxStamina);
			PlayBaseAttributeSet->MaxArmor.SetCurrentValue(MaxArmor);
			//Giving Jump Ability
			AbilityHelper::GiveAbility(this, this->JumpAbilityClass, false);
			AbilityHelper::GiveAbility(this, this->SprintAbilityClass, false);
		}
	}
	
	if (PlayerHUDClass)
	{
		APlayerController* PC = Cast<APlayerController>(GetController());
		PlayerHUD = CreateWidget<ULocalHeroWidget>(PC, PlayerHUDClass);
		if (PlayerHUD)
		{
			PlayerHUD->AddToViewport();
			
			UpdateHealthUI();
			UpdateManaUI();
			UpdateArmorUI();
			UpdateStaminaUI();
		}
	}
}

// Called every frame
void AMobaFlexCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AMobaFlexCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AMobaFlexCharacterBase::BasicAttack()
{
	double currentTime = UGameplayStatics::GetTimeSeconds(GetWorld());
}

void AMobaFlexCharacterBase::JumpAbility()
{
	AbilityHelper::ActivateAbility(this, JumpAbilityClass);
}

void AMobaFlexCharacterBase::SprintAbility_Start()
{
	AbilityHelper::ActivateAbility(this, SprintAbilityClass);	
}

void AMobaFlexCharacterBase::SprintAbility_End()
{
	AbilityHelper::DeactivateAbility(this, SprintAbilityClass);	
}

void AMobaFlexCharacterBase::SetSprint(bool sprint)
{
	bSprint = sprint;
	if(sprint)
	{
		GetCharacterMovement()->MaxWalkSpeed *= 2.0f;
	}
	else
	{
		GetCharacterMovement()->MaxWalkSpeed /= 2.0f;
	}
}

UAbilitySystemComponent* AMobaFlexCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}


void AMobaFlexCharacterBase::OnHealthChanged(float EffectMagnitude, float NewValue)
{
	PlayBaseAttributeSet->Health.SetCurrentValue(FMath::Clamp(NewValue, 0.0, PlayBaseAttributeSet->MaxHealth.GetCurrentValue()));
	UpdateHealthUI();
	if(NewValue <= 0)
	{
		Die();
	}
}

void AMobaFlexCharacterBase::OnMaxHealthChanged(float EffectMagnitude, float NewValue)
{
	PlayBaseAttributeSet->MaxHealth.SetCurrentValue(FMath::Max(NewValue, PlayBaseAttributeSet->Health.GetCurrentValue()));
	UpdateHealthUI();
}

void AMobaFlexCharacterBase::UpdateHealthUI()
{
	if (PlayerHUD)
	{
		PlayerHUD->UpdateHealth(PlayBaseAttributeSet->Health.GetCurrentValue(), PlayBaseAttributeSet->MaxHealth.GetCurrentValue());
	}
}

void AMobaFlexCharacterBase::OnManaChanged(float EffectMagnitude, float NewValue)
{
	PlayBaseAttributeSet->Mana.SetCurrentValue(FMath::Clamp(NewValue, 0.0, PlayBaseAttributeSet->MaxMana.GetCurrentValue()));
	UpdateManaUI();
}

void AMobaFlexCharacterBase::OnMaxManaChanged(float EffectMagnitude, float NewValue)
{
	PlayBaseAttributeSet->MaxMana.SetCurrentValue(FMath::Max(NewValue, PlayBaseAttributeSet->Mana.GetCurrentValue()));
	UpdateManaUI();
}

void AMobaFlexCharacterBase::UpdateManaUI()
{
	if (PlayerHUD)
	{
		PlayerHUD->UpdateMana(PlayBaseAttributeSet->Mana.GetCurrentValue(), PlayBaseAttributeSet->MaxMana.GetCurrentValue());
	}
}


void AMobaFlexCharacterBase::OnArmorChanged(float EffectMagnitude, float NewValue)
{
	PlayBaseAttributeSet->Armor.SetCurrentValue(FMath::Clamp(NewValue, 0.0, PlayBaseAttributeSet->MaxArmor.GetCurrentValue()));
	UpdateArmorUI();
}

void AMobaFlexCharacterBase::OnMaxArmorChanged(float EffectMagnitude, float NewValue)
{
	PlayBaseAttributeSet->MaxArmor.SetCurrentValue(FMath::Max(NewValue, PlayBaseAttributeSet->Armor.GetCurrentValue()));
	UpdateArmorUI();
}

void AMobaFlexCharacterBase::UpdateArmorUI()
{
	if (PlayerHUD)
	{
		PlayerHUD->UpdateArmor(PlayBaseAttributeSet->Armor.GetCurrentValue(), PlayBaseAttributeSet->MaxArmor.GetCurrentValue());
	}
}

void AMobaFlexCharacterBase::OnStaminaChanged(float EffectMagnitude, float NewValue)
{
	PlayBaseAttributeSet->Stamina.SetCurrentValue(FMath::Clamp(NewValue, 0.0, PlayBaseAttributeSet->MaxStamina.GetCurrentValue()));
	UpdateStaminaUI();
}

void AMobaFlexCharacterBase::OnMaxStaminaChanged(float EffectMagnitude, float NewValue)
{
	PlayBaseAttributeSet->MaxStamina.SetCurrentValue(FMath::Max(NewValue, PlayBaseAttributeSet->Stamina.GetCurrentValue()));
	UpdateStaminaUI();
}

void AMobaFlexCharacterBase::UpdateStaminaUI()
{
	if (PlayerHUD)
	{
		PlayerHUD->UpdateStamina(PlayBaseAttributeSet->Stamina.GetCurrentValue(), PlayBaseAttributeSet->MaxStamina.GetCurrentValue());
	}
}

void AMobaFlexCharacterBase::Die()
{
	// Only runs on Server
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetCharacterMovement()->GravityScale = 0;
	GetCharacterMovement()->Velocity = FVector(0);

	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->CancelAllAbilities();
		AbilityHelper::ClearAllEffects(this);
	}

	AMobaFlexPlayerController* PC = Cast<AMobaFlexPlayerController>(GetController());
	PC->DisableInput(PC);
	
	if (DeathAnimation)
	{
		GetMesh()->PlayAnimation(DeathAnimation, false);
	}
	else
	{
		Destroy();
	}
}

