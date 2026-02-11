#include "MobaFlexCharacterBase.h"

#include "AbilitySystemComponent.h"
#include "MobaFlexPlayerController.h"
#include "MobaFlexPlayerStateBase.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "MobaFlex/GAS/PlayBaseAttributeSet.h"
#include "View/MVVMView.h"

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
    
    // Create overhead widget component
    OverheadWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("OverheadWidget"));
    OverheadWidgetComponent->SetupAttachment(GetRootComponent());
    OverheadWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
    OverheadWidgetComponent->SetDrawSize(FVector2D(200.0f, 40.0f));
    OverheadWidgetComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 120.0f));
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
            // Only give abilities on the server
            if (HasAuthority())
            {
                GetGameInstance()->GetSubsystem<UAbilityHelperSubSystem>()->Server_GiveAbility(this, this->JumpAbilityClass, false);
                GetGameInstance()->GetSubsystem<UAbilityHelperSubSystem>()->Server_GiveAbility(this, this->SprintAbilityClass, false);
            }
		}
	}
	
	if (PlayerHUDClass)
	{
		APlayerController* PC = Cast<APlayerController>(GetController());
		if (UUserWidget* PlayerHUD = CreateWidget<UUserWidget>(PC, PlayerHUDClass))
		{
			//Create View Models
			LocalPlayerHUDViewModel = NewObject<ULocalPlayerMVVM>();
			UpdateHealthVM();
			UpdateManaVM();
			UpdateArmorVM();
			UpdateStaminaVM();
			if (UMVVMView* View = Cast<UMVVMView>(PlayerHUD->GetExtension(UMVVMView::StaticClass())))
			{
				bool result = View->SetViewModel(FName("LocalPlayerMVVM"), LocalPlayerHUDViewModel);
			}
			PlayerHUD->AddToViewport();
		}
	}

    // Configure overhead widget component
    if (OverheadWidgetComponent && OverheadWidgetClass)
    {
        OverheadWidgetComponent->SetWidgetClass(OverheadWidgetClass);
        // If this is locally controlled player, hide overhead (don't show own overhead)
        if (IsLocallyControlled())
        {
            OverheadWidgetComponent->SetVisibility(false);
        }
    	else
    	{
	    	UpdateHealthVM();
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

void AMobaFlexCharacterBase::UpdateHealthVM()
{
	if (LocalPlayerHUDViewModel && IsLocallyControlled())
	{
		LocalPlayerHUDViewModel->SetHealth(PlayBaseAttributeSet->Health.GetCurrentValue());
		LocalPlayerHUDViewModel->SetMaxHealth(PlayBaseAttributeSet->MaxHealth.GetCurrentValue());
	}

    if (OverheadWidgetComponent)
    {
        UOverheadWidget* OW = Cast<UOverheadWidget>(OverheadWidgetComponent->GetUserWidgetObject());
        if (OW)
        {
            OW->UpdateHealth(PlayBaseAttributeSet->Health.GetCurrentValue(), PlayBaseAttributeSet->MaxHealth.GetCurrentValue());
        }
    }
}

void AMobaFlexCharacterBase::UpdateManaVM()
{
	if (LocalPlayerHUDViewModel)
	{
		LocalPlayerHUDViewModel->SetMana(PlayBaseAttributeSet->Mana.GetCurrentValue());
		LocalPlayerHUDViewModel->SetMaxMana(PlayBaseAttributeSet->MaxMana.GetCurrentValue());
	}
}

void AMobaFlexCharacterBase::UpdateArmorVM()
{
	if (LocalPlayerHUDViewModel)
	{
		LocalPlayerHUDViewModel->SetArmor(PlayBaseAttributeSet->Armor.GetCurrentValue());
		LocalPlayerHUDViewModel->SetMaxArmor(PlayBaseAttributeSet->MaxArmor.GetCurrentValue());
	}
}

void AMobaFlexCharacterBase::UpdateStaminaVM()
{
	if (LocalPlayerHUDViewModel)
	{
		LocalPlayerHUDViewModel->SetStamina(PlayBaseAttributeSet->Stamina.GetCurrentValue());
		LocalPlayerHUDViewModel->SetMaxStamina(PlayBaseAttributeSet->MaxStamina.GetCurrentValue());
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

