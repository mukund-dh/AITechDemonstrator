// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AbilitySystemInterface.h"
#include "AITDTeamAgentInterface.h"
#include "AITDAICon.generated.h"

namespace ETeamAttitude { enum type : int; }

class UAILizardBrainAttrs;
class UAbilitySystemComponent;
class UAIPerceptionComponent;

class AAITDPlayerState;

/**
 * 
 */
UCLASS()
class AITECHDEMONSTRATOR_API AAITDAICon : public AAIController, public IAITDTeamAgentInterface
{
	GENERATED_BODY()

public:

	AAITDAICon(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	// IAITDTeamAgentInterface
	virtual void SetGenericTeamId(const FGenericTeamId& NewTeamId) override;
	virtual FGenericTeamId GetGenericTeamId() const;
	virtual FOnAITDTeamChangedDelegate* GetOnAITDTeamChangedDelegate() override;
	ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const override;
	// ~IAITDTeamAgentInterface
	
public:
	
	UFUNCTION(BlueprintCallable, Category = "AITD|PlayerProps")
	AAITDPlayerState* GetAITDPlayerState() const;

	UFUNCTION(BlueprintCallable, Category = "AITD|AI Perception")
	void UpdateTeamAttitudeTowards(UAIPerceptionComponent* AIPerception);
	
};
