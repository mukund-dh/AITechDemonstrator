// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Attributes/AIBaseAttributes.h"
#include "AITDPhysicalAttrs.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class AITECHDEMONSTRATOR_API UAITDPhysicalAttrs : public UAIBaseAttributes
{
	GENERATED_BODY()

public:

	UAITDPhysicalAttrs();

	ATTRIBUTE_ACCESSORS(UAITDPhysicalAttrs, Health);
	ATTRIBUTE_ACCESSORS(UAITDPhysicalAttrs, Strength);
	ATTRIBUTE_ACCESSORS(UAITDPhysicalAttrs, Endurance);

	ATTRIBUTE_ACCESSORS(UAITDPhysicalAttrs, MaxHealth);
	ATTRIBUTE_ACCESSORS(UAITDPhysicalAttrs, MaxStrength);
	ATTRIBUTE_ACCESSORS(UAITDPhysicalAttrs, MaxEndurance);

	ATTRIBUTE_ACCESSORS(UAITDPhysicalAttrs, Damage);
	ATTRIBUTE_ACCESSORS(UAITDPhysicalAttrs, Healing);

	//UPROPERTY()
	mutable FAITDAttributeChangedEvent OnHealthChanged;

private:

	// Define Attributes and their related maxes
	UPROPERTY(BlueprintReadOnly, Category = "PhysicalAttributes", Meta = (HideFromModifiers, AllowPrivateAccess = true))
	FGameplayAttributeData Health;

	UPROPERTY(BlueprintReadOnly, Category = "PhysicalAttributes", Meta = (HideFromModifiers, AllowPrivateAccess = true))
	FGameplayAttributeData MaxHealth;
	
	UPROPERTY(BlueprintReadOnly, Category = "PhysicalAttributes", Meta = (HideFromModifiers, AllowPrivateAccess = true))
	FGameplayAttributeData Strength;

	UPROPERTY(BlueprintReadOnly, Category = "PhysicalAttributes", Meta = (HideFromModifiers, AllowPrivateAccess = true))
	FGameplayAttributeData MaxStrength;

	UPROPERTY(BlueprintReadOnly, Category = "PhysicalAttributes", Meta = (HideFromModifiers, AllowPrivateAccess = true))
	FGameplayAttributeData Endurance;

	UPROPERTY(BlueprintReadOnly, Category = "PhysicalAttributes", Meta = (HideFromModifiers, AllowPrivateAccess = true))
	FGameplayAttributeData MaxEndurance;

	// Keep track of any changes we might experience
	float HealthBeforeAttributeChanged;
	float MaxHealthBeforeAttributeChanged;
	float StrengthBeforeAttributeChanged;
	float MaxStrengthBeforeAttributeChanged;
	float EnduranceBeforeAttributeChanged;
	float MaxEnduranceBeforeAttributeChanged;

	// META ATTRIBUTES

	// Incoming Healing. Mapped directly to +Health; over a curve to +Strength, +Endurance
	UPROPERTY(BlueprintReadOnly, Category = "PhysicalAttributes", Meta = (HideFromModifiers, AllowPrivateAccess = true))
	FGameplayAttributeData Healing;

	// Incoming Damage. Mapped directly to -Health; over a curve to -Strength, -Endurance
	UPROPERTY(BlueprintReadOnly, Category = "PhysicalAttributes", Meta = (HideFromModifiers, AllowPrivateAccess = true))
	FGameplayAttributeData Damage;

};
