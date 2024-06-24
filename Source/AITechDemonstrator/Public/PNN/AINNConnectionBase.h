// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Attributes/AITDPhysicalAttrs.h"
#include "AINNConnectionBase.generated.h"

/**
 * 
 */
UCLASS()
class AITECHDEMONSTRATOR_API UAINNConnectionBase : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AttributeEffectors")
	float Weight = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AttributeEffectors")
	float Bias = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Attribute")
	FGameplayTagContainer AttributeTag;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attribute")
	UAITDPhysicalAttrs* PhysicalAttr;
	
};
