// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Attributes/AITDPhysicalAttrs.h"
#include "AITDEnduranceSet.generated.h"

UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Agent_Endurance);

/**
 * Declares the Endurance set for our agents/characters. This set contains the Endurance
 * and MaxEndurance values.
 */
UCLASS(Blueprintable, BlueprintType)
class AITECHDEMONSTRATOR_API UAITDEnduranceSet : public UAITDPhysicalAttrs
{
	GENERATED_BODY()

public:

	UAITDEnduranceSet();

	ATTRIBUTE_ACCESSORS(UAITDEnduranceSet, Endurance);
	ATTRIBUTE_ACCESSORS(UAITDEnduranceSet, MaxEndurance);

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FAITDAttributeChangedEvent OnMaxEnduranceChanged;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FAITDAttributeChangedEvent OnEnduranceChanged;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FAITDAttributeChangedEvent OnOutOfEndurance;

	virtual bool PreGameplayEffectExecute(FGameplayEffectModCallbackData& Data) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	virtual void PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const override;
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) override;

	virtual void ClampAttribute(const FGameplayAttribute& Attribute, float& NewVal) const override;

private:

	// Define the Endurance Attribute
	UPROPERTY(BlueprintReadOnly, Category = "PhysicalAttributes", Meta = (HideFromModifiers, AllowPrivateAccess = true))
	FGameplayAttributeData Endurance;

	// Define the Max Endurance Attribute
	UPROPERTY(BlueprintReadOnly, Category = "PhysicalAttributes", Meta = (HideFromModifiers, AllowPrivateAccess = true))
	FGameplayAttributeData MaxEndurance;

	bool bIsEnduranceZero;

	// Keep track of changes to attributes
	float EnduranceBeforeAttrChanged;
	float MaxEnduranceBeforeAttrChanged;
	
};
