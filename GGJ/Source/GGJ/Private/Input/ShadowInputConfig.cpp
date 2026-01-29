// Fill out your copyright notice in the Description page of Project Settings.


#include "Input/ShadowInputConfig.h"

const UInputAction* UShadowInputConfig::FindInputActionForTag(const FGameplayTag& InputTag, bool bLogNotFound) const
{
	for(const FShadowInputAction& Action : InputActions)
	{
		if(Action.InputAction && Action.InputTag ==  InputTag)
		{
			return Action.InputAction;
		}
	}
	if(bLogNotFound)
	{
		UE_LOG(LogTemp, Error, TEXT("Can't find any input action for [%s],on InputConfig[%s]"), *InputTag.ToString(),*GetNameSafe(this));
	}
	
	return nullptr;
	
}