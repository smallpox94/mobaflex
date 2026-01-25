// Fill out your copyright notice in the Description page of Project Settings.


#include "MobaFlexPlayerStateBase.h"

AMobaFlexPlayerStateBase::AMobaFlexPlayerStateBase()
{
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
}
