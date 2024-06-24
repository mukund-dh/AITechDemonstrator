// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "AIBaseAttributes.generated.h"

class UAITDAbilitySystemComponent;
class UWorld;

/**
 * This macro defines a set of helper functions for accessing and initializing attributes.
 *
 * The following example of the macro:
 *		ATTRIBUTE_ACCESSORS(ULyraHealthSet, Health)
 * will create the following functions:
 *		static FGameplayAttribute GetHealthAttribute();
 *		float GetHealth() const;
 *		void SetHealth(float NewVal);
 *		void InitHealth(float NewVal);
 */
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

/*
 * Delegate used to broadcast events when an attribute changes. Some of these parameters may be null on clients
 * @param EffectInstigator	The original instigating actor for this event
 * @param EffectCauser		The physical actor that caused the change
 * @param EffectSpec		The full effect spec for this change
 * @param EffectMagnitude	The raw magnitude, this is before clamping
 * @param OldValue			The value of the attribute before it was changed
 * @param NewValue			The value after it was changed
*/
DECLARE_DYNAMIC_MULTICAST_DELEGATE_SixParams(FAITDAttributeChangedEvent, AActor*, EffectInstigator, AActor*, EffectCauser, const FGameplayEffectSpec, EffectSpec, float, Magnitude, float, OldValue, float, NewValue);

/**
 * 
 */
UCLASS(Abstract)
class AITECHDEMONSTRATOR_API UAIBaseAttributes : public UAttributeSet
{
	GENERATED_BODY()

public:
	
	// Constructor
	UAIBaseAttributes();

	UWorld* GetWorld() const override;
	
	UAITDAbilitySystemComponent* GetAbilitySystemComponent() const;
};
