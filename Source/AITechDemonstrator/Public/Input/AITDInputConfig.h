// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "AITDInputConfig.generated.h"


class UInputAction;
struct FFrame;

/**
 * Struct used to map a gameplay tag and an input type
 */
USTRUCT(BlueprintType)
struct FAITDInputAction
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<const UInputAction> InputAction = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (Categories = "Input Tag"))
	FGameplayTag InputTag;
};

/**
 * Non-mutable type which contains the Input configuration
 */
UCLASS(BlueprintType, Const)
class AITECHDEMONSTRATOR_API UAITDInputConfig : public UDataAsset
{
	GENERATED_BODY()

public:

	UAITDInputConfig(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable, Category = "AITD|Pawn")
	const UInputAction* FindNativeInputActionForTag(const FGameplayTag& Tag, bool bLogNotFound = true) const;

	UFUNCTION(BlueprintCallable, Category = "AITD|Pawn")
	const UInputAction* FindAbilityInputActionForTag(const FGameplayTag& Tag, bool bLogNotFound = true) const;

public:
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (TitleProperty = "Input Actions"))
	TArray<FAITDInputAction> NativeActions;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (TitleProperty = "Input Actions"))
	TArray<FAITDInputAction> AbilityActions;

};
