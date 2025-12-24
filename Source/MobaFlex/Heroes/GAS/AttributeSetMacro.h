#pragma once

#include "CoreMinimal.h"

#define PLAY_ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
ATTRIBUTE_ACCESSORS_BASIC(ClassName, PropertyName) \
UPROPERTY() \
FPlayAttributeEvent On##PropertyName##Changed;


#define BROADCAST_ATTRIBUTECHANGED_EVENT(PropertyName) \
if(Data.EvaluatedData.Attribute == Get##PropertyName##Attribute()) \
{ \
	On##PropertyName##Changed.Broadcast(Data.EvaluatedData.Magnitude, Get##PropertyName()); \
}