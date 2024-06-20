// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "AITDTeamAgentInterface.h"
#include "GameFramework/PlayerState.h"
#include "AITDPlayerState.generated.h"

class UAITDAbilitySystemComponent;
class UAILizardBrainAttrs;
class UAITDPhysicalAttrs;

/**
 * 
 */
UCLASS()
class AITECHDEMONSTRATOR_API AAITDPlayerState : public APlayerState, public IAbilitySystemInterface, public IAITDTeamAgentInterface
{
	GENERATED_BODY()

public:

	AAITDPlayerState(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	UFUNCTION(BlueprintCallable, Category="AITD|Player")
	AController* GetAITDController() const;

	UFUNCTION(BlueprintCallable, Category="AITD|PlayerState")
	UAITDAbilitySystemComponent* GetAITDAbilitySystemComponent() const { return AbilitySystemComponent; }
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	//IAITDTeamAgentInterface
	virtual void SetGenericTeamId(const FGenericTeamId& NewTeamId) override;
	virtual FGenericTeamId GetGenericTeamId() const override;
	virtual FOnAITDTeamChangedDelegate* GetOnAITDTeamChangedDelegate() override;
	//~IAITDTeamAgentInterface

	UFUNCTION(BlueprintCallable, Category="AITD|Teams")
	int32 GetTeamID() const
	{
		return GenericTeamIDToInt(MyTeamID);
	}

	UFUNCTION(BlueprintCallable, Category = "AITD|Teams")
	int32 GetSquadID() const
	{
		return MySquadID;
	}

	void SetSquadID(int32 NewSquadID);

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="AITD|PlayerState")
	TObjectPtr<UAITDAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="AITD|PlayerState")
	TObjectPtr<const class UAILizardBrainAttrs> LizardBrainAttrs;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AITD|PlayerState")
	TObjectPtr<const class UAITDPhysicalAttrs> PhysicalAttrs;

private:

	UPROPERTY(VisibleAnywhere, Category = "AITD|AIPlayerState")
	FGenericTeamId MyTeamID;

	UPROPERTY(VisibleAnywhere, Category = "AITD|AIPlayerState")
	int32 MySquadID;
	
	UPROPERTY()
	FOnAITDTeamChangedDelegate AITDTeamChangedDelegate;
};
