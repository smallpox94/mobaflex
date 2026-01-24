// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseTriggerZone.h"
#include "GameplayEffect.h"
#include "PickupZone.generated.h"

UCLASS()
class MOBAFLEX_API APickupZone : public ABaseTriggerZone
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APickupZone();

protected:
	virtual void HandleOverlapBegin(AActor* OtherActor, const FHitResult& SweepResult) override;
	virtual void HandleOverlapEnd(AActor* OtherActor) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup")
	bool bDestroyOnPickup = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup")
	float RespawnTime = 0.0f;

	UPROPERTY(BlueprintReadOnly, Category = "Pickup")
	bool bIsActive = true;

	UFUNCTION(BlueprintNativeEvent, Category = "Pickup")
	void OnPickedUp(AActor* PickupActor);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects")
	TArray<TSubclassOf<UGameplayEffect>> EffectsOnPickup;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects")
	TArray<TSubclassOf<UGameplayAbility>> AbilitiesOnPickup;
private:
	FTimerHandle RespawnTimerHandle;
	void Respawn();
};
