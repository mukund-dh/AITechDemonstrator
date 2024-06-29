// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/PawnComponent.h"
#include "Components/GameFrameworkInitStateInterface.h"
#include "AITDPawnExtensionComponent.generated.h"

namespace EEndPlayReason { enum Type : int; }

class UGameFrameworkComponentManager;
class UAITDAbilitySystemComponent;
class UAITDPawnData;

struct FActorInitStateChangedParams;
struct FFrame;
struct FGameplayTag;


/**
 * Component that adds functionality to the pawn so that it can be used for all kinds of pawns...eg., Characters, Vehicles, etc.
 * Also coordinates the initialization of other components.
 */
UCLASS()
class AITECHDEMONSTRATOR_API UAITDPawnExtensionComponent : public UPawnComponent, public IGameFrameworkInitStateInterface
{
	GENERATED_BODY()

public:

	UAITDPawnExtensionComponent(const FObjectInitializer& ObjectInitializer);

	static const FName NAME_ActorFeatureName;

	//~ Begin IGameFrameworkInitStateInterface interface
	virtual FName GetFeatureName() const override { return NAME_ActorFeatureName; }
	virtual bool CanChangeInitState(UGameFrameworkComponentManager* Manager, FGameplayTag CurrentState, FGameplayTag DesiredState) const override;
	virtual void HandleChangeInitState(UGameFrameworkComponentManager* Manager, FGameplayTag CurrentState, FGameplayTag DesiredState) override;
	virtual void OnActorInitStateChanged(const FActorInitStateChangedParams& Params) override;
	virtual void CheckDefaultInitialization() override;
	//~ End IGameFrameworkInitStateInterface interface

	UFUNCTION(BlueprintPure, Category = "AITD|Pawn")
	static UAITDPawnExtensionComponent* FindPawnExtensionComponent(const AActor* Actor) { return (Actor ? Actor->FindComponentByClass<UAITDPawnExtensionComponent>() : nullptr); }

	/** Get the Pawn Data */
	template <class T>
	const T* GetPawnData() { return Cast<T>(PawnData); }

	/** Set the Pawn Data */
	void SetPawnData(const UAITDPawnData* InData);

	/** Gets the current Ability System Component, which may be owned by a separate actor */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "AITD|Ability")
	UAITDAbilitySystemComponent* GetAbilitySystemComponent() const { return AbilitySystemComponent; }

	/** Must be called from the owning pawn to become the avatar actor */
	void InitializeAbilitySystem(UAITDAbilitySystemComponent* ASC, AActor* OwnerActor);

	/** Must be called from the owning pawn to remove itself as the avatar actor */
	void UninitializeAbilitySystem();

	/** Should be called by the owning pawn when its controller changes */
	void HandleControllerChanged();

	/** Should be called by the owning pawn when its player state is replicated */
	void HandlePlayerStateReplicated();

	/** Should be called by the owning pawn when the input component is setup */
	void SetupPlayerInputComponent();

	/** Register with the OnAbilitySystemInitialized delegate and broadcast if our pawn has been registered with the ability system component */
	void OnAbilitySystemInitialized_RegisterAndCall(FSimpleMulticastDelegate::FDelegate Delegate);

	/** Register with the OnAbilitySystemUninitialized delegate fired when our pawn is removed as the ability system's avatar actor */
	void OnAbilitySystemUninitialized_Register(FSimpleMulticastDelegate::FDelegate Delegate);

protected:

	virtual void OnRegister() override;
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	/** Delegate fired when our pawn becomes an ability system's avatar actor */
	FSimpleMulticastDelegate OnAbilitySystemInitialized;

	/** Delegate fired when our pawn is removed as an ability system's avatar actor */
	FSimpleMulticastDelegate OnAbilitySystemUninitialized;

	/** Pawn Data used to create the pawn. Specified from a spawn function or on a placed instance. */
	UPROPERTY(EditInstanceOnly, Category="AITD|Pawn")
	TObjectPtr<const UAITDPawnData> PawnData;

	/** Pointer to the ability system component which is cached for convenience */
	TObjectPtr<UAITDAbilitySystemComponent> AbilitySystemComponent;
	
};
