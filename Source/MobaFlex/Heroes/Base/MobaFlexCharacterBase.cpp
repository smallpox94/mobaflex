#include "MobaFlexCharacterBase.h"

#include "AbilitySystemComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "MobaFlex/Heroes/GAS/AbilityHelper.h"
#include "MobaFlex/Heroes/GAS/Effects/Jump/JumpAbility.h"

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
			
			PlayBaseAttributeSet->OnHealthChanged.AddDynamic(this, &AMobaFlexCharacterBase::OnHealthChanged);
			PlayBaseAttributeSet->OnManaChanged.AddDynamic(this, &AMobaFlexCharacterBase::OnManaChanged);
			PlayBaseAttributeSet->OnArmorChanged.AddDynamic(this, &AMobaFlexCharacterBase::OnArmorChanged);
			PlayBaseAttributeSet->OnStaminaChanged.AddDynamic(this, &AMobaFlexCharacterBase::OnStaminaChanged);
			//Giving Jump Ability
			AbilityHelper::GiveAbility(this, UJumpAbility::StaticClass(), false);
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
	AbilityHelper::ActivateAbility(this, UJumpAbility::StaticClass());
}

UAbilitySystemComponent* AMobaFlexCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AMobaFlexCharacterBase::OnHealthChanged(float EffectMagnitude, float NewValue)
{
	FString Msg = FString::Printf(TEXT("Health changed by %.2f to %.2f"), EffectMagnitude, NewValue);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, Msg);
	PlayBaseAttributeSet->Health.SetCurrentValue(FMath::Max(NewValue,0.0f));
	if(NewValue <= 0)
	{
		Destroy();
	}
}

void AMobaFlexCharacterBase::OnManaChanged(float EffectMagnitude, float NewValue)
{
	FString Msg = FString::Printf(TEXT("Mana changed by %.2f to %.2f"), EffectMagnitude, NewValue);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, Msg);
	PlayBaseAttributeSet->Mana.SetCurrentValue(FMath::Max(NewValue,0.0f));
}

void AMobaFlexCharacterBase::OnArmorChanged(float EffectMagnitude, float NewValue)
{
	FString Msg = FString::Printf(TEXT("Armor changed by %.2f to %.2f"), EffectMagnitude, NewValue);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Black, Msg);
	PlayBaseAttributeSet->Armor.SetCurrentValue(FMath::Max(NewValue,0.0f));
}

void AMobaFlexCharacterBase::OnStaminaChanged(float EffectMagnitude, float NewValue)
{
	FString Msg = FString::Printf(TEXT("Stamina changed by %.2f to %.2f"), EffectMagnitude, NewValue);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, Msg);
	PlayBaseAttributeSet->Stamina.SetCurrentValue(FMath::Max(NewValue,0.0f));
}

