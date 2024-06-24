// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Attributes/AIBaseAttributes.h"
#include "NativeGameplayTags.h"
#include "AITDPhysicalAttrs.generated.h"

UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Gameplay_Damage);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Gameplay_DamageImmunity);

/**
 * The base class to define any Physical Attributes we might have on our characters/agents
 * Currently, we will start with just three Attributes:
 * Health
 * Strength
 * Endurance
 * 
 * But we can, and will, add more to this list. 
 */
UCLASS(Abstract)
class AITECHDEMONSTRATOR_API UAITDPhysicalAttrs : public UAIBaseAttributes
{
	GENERATED_BODY()

public:

	UAITDPhysicalAttrs();

	ATTRIBUTE_ACCESSORS(UAITDPhysicalAttrs, Damage);
	ATTRIBUTE_ACCESSORS(UAITDPhysicalAttrs, Healing);

	virtual void ClampAttribute(const FGameplayAttribute& Attribute, float& NewVal) const;

	UPROPERTY(VisibleAnywhere, Category="Config")
	TArray<FGameplayAttribute> AttrList;

private:
	
	//--------------------------------------------------------------------------------------------------------
	// META ATTRIBUTES - They don't really need to be tracked, but will kick in when any execution happens
	//--------------------------------------------------------------------------------------------------------

	// Incoming Healing. Mapped directly to +Health; over a curve to +Strength, +Endurance
	UPROPERTY(BlueprintReadOnly, Category = "PhysicalAttributes", Meta = (HideFromModifiers, AllowPrivateAccess = true))
	FGameplayAttributeData Healing;

	// Incoming Damage. Mapped directly to -Health; over a curve to -Strength, -Endurance
	UPROPERTY(BlueprintReadOnly, Category = "PhysicalAttributes", Meta = (HideFromModifiers, AllowPrivateAccess = true))
	FGameplayAttributeData Damage;

};
