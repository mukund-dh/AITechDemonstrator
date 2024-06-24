// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Attributes/AITDPhysicalAttrs.h"
#include "AITDStrengthSet.generated.h"

UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Agent_Strength);

/**
 * Declares the Strength set for our agents/characters. This set contains the Strength
 * and MaxStrength values.
 */
UCLASS(Blueprintable, BlueprintType)
class AITECHDEMONSTRATOR_API UAITDStrengthSet : public UAITDPhysicalAttrs
{
	GENERATED_BODY()
	
public:

	UAITDStrengthSet();

	ATTRIBUTE_ACCESSORS(UAITDStrengthSet, Strength);
	ATTRIBUTE_ACCESSORS(UAITDStrengthSet, MaxStrength);

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FAITDAttributeChangedEvent OnMaxStrengthChanged;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FAITDAttributeChangedEvent OnStrengthChanged;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FAITDAttributeChangedEvent OnOutOfStrength;

	virtual bool PreGameplayEffectExecute(FGameplayEffectModCallbackData& Data) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	virtual void PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const override;
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) override;

	virtual void ClampAttribute(const FGameplayAttribute& Attribute, float& NewVal) const override;

private:

	// Define the Strength Attribute
	UPROPERTY(BlueprintReadOnly, Category = "PhysicalAttributes", Meta = (HideFromModifiers, AllowPrivateAccess = true))
	FGameplayAttributeData Strength;

	// Define the Max Strength Attribute
	UPROPERTY(BlueprintReadOnly, Category = "PhysicalAttributes", Meta = (HideFromModifiers, AllowPrivateAccess = true))
	FGameplayAttributeData MaxStrength;

	bool bIsStrengthZero;

	// Keep track of changes to attributes
	float StrengthBeforeAttrChanged;
	float MaxStrengthBeforeAttrChanged;

};
