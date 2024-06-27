// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "AITDPawnData.generated.h"

class APawn;
class UAITDAbilitySet;
class UAITDAbilityTagRelationshipMap;
class UAITDCameraMode;
class UAITDInputConfig;


/**
 * Non-mutable data asset used to define a pawn
 */
UCLASS(BlueprintType, Const, meta = (DisplayName = "AITD Pawn Data"))
class AITECHDEMONSTRATOR_API UAITDPawnData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:

	UAITDPawnData(const FObjectInitializer& ObjectInitializer);

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AITD|Pawn")
	TSubclassOf<APawn> PawnClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AITD|Abilities")
	TArray<TObjectPtr<UAITDAbilitySet>> AbilitySets;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AITD|Abilities")
	TObjectPtr<UAITDAbilityTagRelationshipMap> TagRelationshipMapping;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AITD|Input")
	TObjectPtr<UAITDInputConfig> InputConfig;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AITD|CameraMode")
	TSubclassOf<UAITDCameraMode> DefaultCameraMode;
	
};
