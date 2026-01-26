#pragma once

template<typename T>
void ClampAttributeValue(T Attribute, T AttributeToMatch, float& NewValue, float maxValue, float MinValue = 0.0f)
{
	if (Attribute == AttributeToMatch)
	{
		NewValue = FMath::Clamp(NewValue, MinValue, maxValue);
	}
}

#define PLAY_ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
ATTRIBUTE_ACCESSORS_BASIC(ClassName, PropertyName) \
UPROPERTY() \
FPlayAttributeEvent On##PropertyName##Changed; \
UFUNCTION() \
virtual void OnRep_##PropertyName(const FGameplayAttributeData& Old##PropertyName) \
{ \
		GAMEPLAYATTRIBUTE_REPNOTIFY(UPlayBaseAttributeSet, PropertyName, Old##PropertyName); \
} \

#define BROADCAST_ATTRIBUTE_CHANGED_EVENT_WITH_TAG(PropertyName) \
if(Data.EvaluatedData.Attribute == Get##PropertyName##Attribute()) \
{ \
	float currentValue = Get##PropertyName(); \
	float clampedValue = FMath::Clamp(currentValue, 0.0f, GetMax##PropertyName()); \
	if(clampedValue != currentValue) \
	{ \
		Set##PropertyName(clampedValue);\
		currentValue = clampedValue; \
	} \
	On##PropertyName##Changed.Broadcast(Data.EvaluatedData.Magnitude, currentValue); \
	UAbilitySystemComponent* TargetASC = GetOwningAbilitySystemComponent(); \
	if (!TargetASC) \
	{ \
		return; \
	} \
	if(currentValue <= 0.0f && !Data.Target.HasMatchingGameplayTag(UAbilityHelperSubSystem::FindGameplayTag("MobaFlex.Character.No" #PropertyName ""))) \
	{ \
		TargetASC->AddMinimalReplicationGameplayTag(UAbilityHelperSubSystem::FindGameplayTag("MobaFlex.Character.No" #PropertyName ""));	\
	} \
	else if(currentValue > 0.0f && Data.Target.HasMatchingGameplayTag(UAbilityHelperSubSystem::FindGameplayTag("MobaFlex.Character.No" #PropertyName "")))\
	{ \
	 	TargetASC->RemoveMinimalReplicationGameplayTag(UAbilityHelperSubSystem::FindGameplayTag("MobaFlex.Character.No" #PropertyName "")); \
	 } \
} 

#define BROADCAST_ATTRIBUTE_CHANGED_EVENT(PropertyName) \
if(Data.EvaluatedData.Attribute == Get##PropertyName##Attribute()) \
{ \
	On##PropertyName##Changed.Broadcast(Data.EvaluatedData.Magnitude, Get##PropertyName()); \
} 