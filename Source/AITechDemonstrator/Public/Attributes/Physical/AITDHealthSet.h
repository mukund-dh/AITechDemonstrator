// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Attributes/AITDPhysicalAttrs.h"
#include "AITDHealthSet.generated.h"

UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Agent_Health);

/**
 * Declares the Health set for our agents/characters. This set contains the Health
 * and MaxHealth values.
 */
UCLASS(Blueprintable, BlueprintType)
class AITECHDEMONSTRATOR_API UAITDHealthSet : public UAITDPhysicalAttrs
{
	GENERATED_BODY()

public:

	UAITDHealthSet();

	ATTRIBUTE_ACCESSORS(UAITDHealthSet, Health);
	ATTRIBUTE_ACCESSORS(UAITDHealthSet, MaxHealth);

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FAITDAttributeChangedEvent OnMaxHealthChanged;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FAITDAttributeChangedEvent OnHealthChanged;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FAITDAttributeChangedEvent OnOutOfHealth;

	virtual bool PreGameplayEffectExecute(FGameplayEffectModCallbackData& Data) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	virtual void PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const override;
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) override;

	virtual void ClampAttribute(const FGameplayAttribute& Attribute, float& NewVal) const override;

private:

	// Define the Health Attribute
	UPROPERTY(BlueprintReadOnly, Category = "PhysicalAttributes", Meta = (HideFromModifiers, AllowPrivateAccess = true))
	FGameplayAttributeData Health;

	// Define the Maximum Health Attribute
	UPROPERTY(BlueprintReadOnly, Category = "PhysicalAttributes", Meta = (HideFromModifiers, AllowPrivateAccess = true))
	FGameplayAttributeData MaxHealth;

	bool bIsHealthZero;

	// Keep track of changes to attributes
	float HealthBeforeAttrChanged;
	float MaxHealthBeforeAttrChanged;
};
