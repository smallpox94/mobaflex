#pragma once

#define PLAY_ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
ATTRIBUTE_ACCESSORS_BASIC(ClassName, PropertyName) \
UPROPERTY() \
FPlayAttributeEvent On##PropertyName##Changed; \

#define BROADCAST_ATTRIBUTE_CHANGED_EVENT_WITH_TAG(PropertyName) \
if(Data.EvaluatedData.Attribute == Get##PropertyName##Attribute()) \
{ \
	On##PropertyName##Changed.Broadcast(Data.EvaluatedData.Magnitude, Get##PropertyName()); \
	UAbilitySystemComponent* TargetASC = GetOwningAbilitySystemComponent(); \
	if (!TargetASC) \
	{ \
		return; \
	} \
	if(Get##PropertyName() <= 0.0f && !Data.Target.HasMatchingGameplayTag(AbilityHelper::FindGameplayTag("MobaFlex.Character.No" #PropertyName ""))) \
	{ \
		TargetASC->AddMinimalReplicationGameplayTag(AbilityHelper::FindGameplayTag("MobaFlex.Character.No" #PropertyName ""));	\
	} \
	else if(Get##PropertyName() > 0.0f && Data.Target.HasMatchingGameplayTag(AbilityHelper::FindGameplayTag("MobaFlex.Character.No" #PropertyName "")))\
	{ \
	 	TargetASC->RemoveMinimalReplicationGameplayTag(AbilityHelper::FindGameplayTag("MobaFlex.Character.No" #PropertyName "")); \
	 } \
} \

#define BROADCAST_ATTRIBUTE_CHANGED_EVENT(PropertyName) \
if(Data.EvaluatedData.Attribute == Get##PropertyName##Attribute()) \
{ \
	On##PropertyName##Changed.Broadcast(Data.EvaluatedData.Magnitude, Get##PropertyName()); \
} \
