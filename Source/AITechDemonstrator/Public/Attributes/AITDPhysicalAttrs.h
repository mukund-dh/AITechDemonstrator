// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Attributes/AIBaseAttributes.h"
#include "AITDPhysicalAttrs.generated.h"

/**
 * 
 */
UCLASS()
class AITECHDEMONSTRATOR_API UAITDPhysicalAttrs : public UAIBaseAttributes
{
	GENERATED_BODY()

public:

	UAITDPhysicalAttrs();

	ATTRIBUTE_ACCESSORS(UAITDPhysicalAttrs, Health);
	ATTRIBUTE_ACCESSORS(UAITDPhysicalAttrs, Strength);

private:

	UPROPERTY(BlueprintReadOnly, Category = "PhysicalAttributes", Meta = (HideFromModifiers, AllowPrivateAccess = true))
	FGameplayAttributeData Health;
	
	UPROPERTY(BlueprintReadOnly, Category = "PhysicalAttributes", Meta = (HideFromModifiers, AllowPrivateAccess = true))
	FGameplayAttributeData Strength;
};
