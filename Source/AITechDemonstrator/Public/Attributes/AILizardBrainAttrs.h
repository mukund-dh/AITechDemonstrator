// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Attributes/AIBaseAttributes.h"
#include "AILizardBrainAttrs.generated.h"

/**
 * The base traits of any AI being.
 * Self Preservation - Higher Self Preservation makes the agent lean towards survival instincts
 * Aggression - Higher Aggression makes the agent's first response be that of attack
 * Intuition - How attuned the agent is to sensing danger
 * 
 * All of these are affected by the two physical traits defined for this project: Strength and Health
 * A decent implementation of these effects would be:
 * High Strength, High Health = Higher Aggression, Lower Self Preservation, Neutral Intuition
 * High Strength, Low Health = Neutral Aggression, Higher Self Preservation, Higher Intuition
 * Low Strength, High Health = Lower Aggression, Higher Self Preservation, Higher Intuition
 * Low Strength, Low Health = Lower Aggression, Higher Self Preservation, Lower Intuition
 * 
 * The above, of course, holds true for a normal enemy. In case we are fighting zombies, Health would
 * probably have no effect on the overall state of the lizard brain.
 * 
 */
UCLASS()
class AITECHDEMONSTRATOR_API UAILizardBrainAttrs : public UAIBaseAttributes
{
	GENERATED_BODY()
	
public:

	UAILizardBrainAttrs();

	ATTRIBUTE_ACCESSORS(UAILizardBrainAttrs, SelfPreservation);
	ATTRIBUTE_ACCESSORS(UAILizardBrainAttrs, Aggression);
	ATTRIBUTE_ACCESSORS(UAILizardBrainAttrs, Intuition);

private:

	UPROPERTY(BlueprintReadOnly, Category = "AI|LizardBrain", Meta = (HideFromModifiers, AllowPrivateAccess = true))
	FGameplayAttributeData SelfPreservation;

	UPROPERTY(BlueprintReadOnly, Category = "AI|LizardBrain", Meta = (HideFromModifiers, AllowPrivateAccess = true))
	FGameplayAttributeData Aggression;

	UPROPERTY(BlueprintReadOnly, Category = "AI|LizardBrain", Meta = (HideFromModifiers, AllowPrivateAccess = true))
	FGameplayAttributeData Intuition;
};
