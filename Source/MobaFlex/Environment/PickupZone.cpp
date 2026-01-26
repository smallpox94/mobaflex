// Fill out your copyright notice in the Description page of Project Settings.

#include "PickupZone.h"
#include "TimerManager.h"
#include "MobaFlex/GAS/AbilityHelper.h"

// Sets default values
APickupZone::APickupZone()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

void APickupZone::HandleOverlapBegin(AActor* OtherActor, const FHitResult& SweepResult)
{
	if (!bIsActive)
	{
		return;
	}

	// Call Blueprint event
	OnPickedUp(OtherActor);

	if (bDestroyOnPickup)
	{
		if (RespawnTime > 0.0f)
		{
			bIsActive = false;
			SetActorHiddenInGame(true);
			SetActorEnableCollision(false);

			GetWorldTimerManager().SetTimer(RespawnTimerHandle, this, &APickupZone::Respawn, RespawnTime, false);
		}
		else
		{
			Destroy();
		}
	}
}

void APickupZone::HandleOverlapEnd(AActor* OtherActor)
{
	
}

void APickupZone::OnPickedUp_Implementation(AActor* PickupActor)
{
	for (TSubclassOf<UGameplayEffect>& Effect : EffectsOnPickup)
	{
		GetGameInstance()->GetSubsystem<UAbilityHelperSubSystem>()->Server_AddEffect(PickupActor, Effect, true);
	}
	
	for (TSubclassOf<UGameplayAbility>& ability : AbilitiesOnPickup)
	{
		GetGameInstance()->GetSubsystem<UAbilityHelperSubSystem>()->GiveAbility(PickupActor, ability, false);
	}
}

void APickupZone::Respawn()
{
	bIsActive = true;
	SetActorHiddenInGame(false);
	SetActorEnableCollision(true);
}
