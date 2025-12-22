#pragma once

#include "CoreMinimal.h"
#include "CoreUObject.h"
#include "AbilitySystemComponent.h"

#define PLAY_ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName) \
UPROPERTY() \
FPlayAttributeEvent On##PropertyName##Changed;

#define BROADCAST_ATTRIBUTECHANGED_EVENT(PropertyName) \
if(Data.EvaluatedData.Attribute == Get##PropertyName##Attribute()) \
{ \
	On##PropertyName##Changed.Broadcast(Data.EvaluatedData.Magnitude, Get##PropertyName()); \
}