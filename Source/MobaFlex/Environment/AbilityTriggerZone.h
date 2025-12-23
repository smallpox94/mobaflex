// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "GameplayAbilitySpec.h"
#include "AbilityTriggerZone.generated.h"

class UGameplayAbility;

UCLASS()
class MOBAFLEX_API AAbilityTriggerZone : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AAbilityTriggerZone();

protected:
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UBoxComponent> TriggerZone;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Abilities")
	TArray<TSubclassOf<UGameplayAbility>> AbilitiesToApply;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool ActivateOnApplying = true;

private:
};
