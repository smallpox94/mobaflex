#include "MobaFlexCharacterBase.h"

#include "AbilitySystemComponent.h"
#include "MobaFlexPlayerController.h"
#include "MobaFlexPlayerStateBase.h"
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
			GetGameInstance()->GetSubsystem<UAbilityHelperSubSystem>()->Server_GiveAbility(this, this->JumpAbilityClass, false);
			GetGameInstance()->GetSubsystem<UAbilityHelperSubSystem>()->Server_GiveAbility(this, this->SprintAbilityClass, false);
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

//On Server
void AMobaFlexCharacterBase::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	
	AMobaFlexPlayerStateBase* PS = GetPlayerState<AMobaFlexPlayerStateBase>();
	if(PS)
	{
		AbilitySystemComponent = Cast<UAbilitySystemComponent>(PS->GetAbilitySystemComponent());
		PS->GetAbilitySystemComponent()->InitAbilityActorInfo(PS, this);
	}
}

//On Client
void AMobaFlexCharacterBase::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	AMobaFlexPlayerStateBase* PS = GetPlayerState<AMobaFlexPlayerStateBase>();
	if(PS)
	{
		AbilitySystemComponent = Cast<UAbilitySystemComponent>(PS->GetAbilitySystemComponent());
		AbilitySystemComponent->InitAbilityActorInfo(PS, this);
	}
}

void AMobaFlexCharacterBase::BasicAttack()
{
	double currentTime = UGameplayStatics::GetTimeSeconds(GetWorld());
}

void AMobaFlexCharacterBase::JumpAbility()
{
	GetGameInstance()->GetSubsystem<UAbilityHelperSubSystem>()->Server_ActivateAbility(this, JumpAbilityClass);
}

void AMobaFlexCharacterBase::SprintAbility_Start()
{
	GetGameInstance()->GetSubsystem<UAbilityHelperSubSystem>()->Server_ActivateAbility(this, SprintAbilityClass);	
}

void AMobaFlexCharacterBase::SprintAbility_End()
{
	GetGameInstance()->GetSubsystem<UAbilityHelperSubSystem>()->Server_DeactivateAbility(this, SprintAbilityClass);	
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

void AMobaFlexCharacterBase::UpdateHealthUI()
{
	if (PlayerHUD)
	{
		PlayerHUD->UpdateHealth(PlayBaseAttributeSet->Health.GetCurrentValue(), PlayBaseAttributeSet->MaxHealth.GetCurrentValue());
	}
}

void AMobaFlexCharacterBase::UpdateManaUI()
{
	if (PlayerHUD)
	{
		PlayerHUD->UpdateMana(PlayBaseAttributeSet->Mana.GetCurrentValue(), PlayBaseAttributeSet->MaxMana.GetCurrentValue());
	}
}

void AMobaFlexCharacterBase::UpdateArmorUI()
{
	if (PlayerHUD)
	{
		PlayerHUD->UpdateArmor(PlayBaseAttributeSet->Armor.GetCurrentValue(), PlayBaseAttributeSet->MaxArmor.GetCurrentValue());
	}
}

void AMobaFlexCharacterBase::UpdateStaminaUI()
{
	if (PlayerHUD)
	{
		PlayerHUD->UpdateStamina(PlayBaseAttributeSet->Stamina.GetCurrentValue(), PlayBaseAttributeSet->MaxStamina.GetCurrentValue());
	}
}

void AMobaFlexCharacterBase::Client_Die_Implementation()
{
	Dead = true;
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetCharacterMovement()->GravityScale = 0;
	GetCharacterMovement()->Velocity = FVector(0);

	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->CancelAllAbilities();
		GetGameInstance()->GetSubsystem<UAbilityHelperSubSystem>()->Server_ClearAllEffects(this);
	}

	AMobaFlexPlayerController* PC = Cast<AMobaFlexPlayerController>(GetController());
	if (PC)
	{
		PC->DisableInput(PC);
	}
	
	if (DeathAnimation)
	{
		GetMesh()->PlayAnimation(DeathAnimation, false);
	}
	else
	{
		Destroy();
	}
}

