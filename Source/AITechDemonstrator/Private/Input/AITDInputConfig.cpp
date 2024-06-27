// Fill out your copyright notice in the Description page of Project Settings.


#include "AITDInputConfig.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(AITDInputConfig)


UAITDInputConfig::UAITDInputConfig(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

const UInputAction* UAITDInputConfig::FindNativeInputActionForTag(const FGameplayTag& Tag, bool bLogNotFound) const
{
	for (const FAITDInputAction NA : NativeActions)
	{
		if (NA.InputAction && (NA.InputTag == Tag))
		{
			return NA.InputAction;
		}
	}

	return nullptr;
}

const UInputAction* UAITDInputConfig::FindAbilityInputActionForTag(const FGameplayTag& Tag, bool bLogNotFound) const
{
	for (const FAITDInputAction AA : AbilityActions)
	{
		if (AA.InputAction && (AA.InputTag == Tag))
		{
			return AA.InputAction;
		}
	}

	return nullptr;
}
