// Fill out your copyright notice in the Description page of Project Settings.


#include "FireCue.h"


// Sets default values
AFireCue::AFireCue()
{
	
}

bool AFireCue::OnActive_Implementation(AActor* MyTarget, const FGameplayCueParameters& Parameters)
{
	return Super::OnActive_Implementation(MyTarget, Parameters);
}

bool AFireCue::WhileActive_Implementation(AActor* MyTarget, const FGameplayCueParameters& Parameters)
{
	return Super::WhileActive_Implementation(MyTarget, Parameters);
}

bool AFireCue::OnRemove_Implementation(AActor* MyTarget, const FGameplayCueParameters& Parameters)
{
	return Super::OnRemove_Implementation(MyTarget, Parameters);
}

