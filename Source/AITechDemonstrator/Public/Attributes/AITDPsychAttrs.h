// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Attributes/AIBaseAttributes.h"
#include "AITDPsychAttrs.generated.h"

USTRUCT(BlueprintType)
struct FTraitInputBase
{
	GENERATED_USTRUCT_BODY()

public:
	
	UPROPERTY(BlueprintReadWrite, Category = "Trait Effect Properties")
	float TraitWeight;

	UPROPERTY(BlueprintReadWrite, Category = "Trait Effect Properties")
	float TraitValue;

	UPROPERTY(BlueprintReadWrite, Category = "Trait Effect Properties")
	FGameplayAttribute BaseAttribute;

};

/**
 * Base class for handling Psychological Attributes of an agent
 * So this has an attribute with a set value, and then a struct which 
 * defines multiple inputs based on how something affects this particular attribute
 */
UCLASS(Abstract)
class AITECHDEMONSTRATOR_API UAITDPsychAttrs : public UAIBaseAttributes
{
	GENERATED_BODY()

public:

	UAITDPsychAttrs();

	ATTRIBUTE_ACCESSORS(UAITDPsychAttrs, AttrVal);

	mutable FAITDAttributeChangedEvent OnPsychAttrChanged;

	UFUNCTION(BlueprintCallable, Category = "LayerInputs")
	void AddInputForCompute(const FTraitInputBase& LayerInput);

	UFUNCTION(BlueprintCallable, Category = "LayerInputs")
	void SetAttributeBias(float NewBias);

	UFUNCTION(BlueprintPure, BlueprintCallable, Category = "LayerInputs")
	float GetAttributeBias() const;

private:

	UPROPERTY(BlueprintReadOnly, Category = "PsychologicalAttributes", Meta = (HideFromModifiers, AllowPrivateAccess = true))
	FGameplayAttributeData AttrVal;

	// Keep track of changes
	float AttrValBeforeChange;

	//--------------------------------------------------------------------------------------------------------
	// META ATTRIBUTES - They don't really need to be tracked, but will kick in when any execution happens
	//--------------------------------------------------------------------------------------------------------

	TArray<FTraitInputBase> Inputs;

	float bias;

	
};
