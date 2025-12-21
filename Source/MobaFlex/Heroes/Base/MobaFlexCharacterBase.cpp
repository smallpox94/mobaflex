#include "MobaFlexCharacterBase.h"

#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AMobaFlexCharacterBase::AMobaFlexCharacterBase()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	CameraSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraSpringArm"));
	CameraSpringArm->SetupAttachment(GetCapsuleComponent());
	CameraSpringArm->bUsePawnControlRotation = true;
	
	CameraInputComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraInputComponent->SetupAttachment(CameraSpringArm);
}

// Called when the game starts or when spawned
void AMobaFlexCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
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

