// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ShapeComponent.h"
#include "GameFramework/Actor.h"
#include "BaseTriggerZone.generated.h"

UCLASS(Abstract)
class MOBAFLEX_API ABaseTriggerZone : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABaseTriggerZone();

protected:
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Override these in derived classes to implement specific behavior
	virtual void HandleOverlapBegin(AActor* OtherActor, const FHitResult& SweepResult);
	virtual void HandleOverlapEnd(AActor* OtherActor);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UShapeComponent> TriggerZone;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<USceneComponent> SceneBaseComp;
};
