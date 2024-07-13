// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/PawnComponent.h"
#include "Components/GameFrameworkInitStateInterface.h"
#include "GameFeatureActions/GFA_AddInputContextMapping.h"
#include "GameplayAbilitySpecHandle.h"
#include "AITDHeroComponent.generated.h"

namespace EEndPlayReason { enum Type : int;}

class UGameFrameworkComponentManager;
class UInputComponent;
// Insert AITD Camera Mode Here
class UAITDInputConfig;
class UObject;
struct FActorInitStateChangedParams;
struct FFrame;
struct FGameplayTag;
struct FInputActionValue;

/**
 * 
 */
UCLASS(Blueprintable, meta = (BlueprintSpawnableComponent))
class AITECHDEMONSTRATOR_API UAITDHeroComponent : public UPawnComponent
{
	GENERATED_BODY()

public:
	
	UAITDHeroComponent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	/** Returns the Hero Component if one exists on the given character */
	UFUNCTION(BlueprintPure, Category = "AITD|Hero")
	static UAITDHeroComponent* GetHeroComponent (const AActor* InActor) { return (InActor ? InActor->FindComponentByClass<UAITDHeroComponent>() : nullptr); }
	
	/** Overrides the camera mode based on the active gameplay ability */
	//void SetAbilityCameraMode(TSubclassOf<UAITDCameraMode> CameraMode, const FGameplayAbilitySpecHandle& OwningSpecHandle);
};
