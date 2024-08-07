// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "NativeGameplayTags.h"

/**
 * Gameplay Tag definitions for the game 
 */
namespace AITDGameplayTags
{
	AITECHDEMONSTRATOR_API		FGameplayTag FindTagByString(const FString& TagString, bool bMatchPartialString = false);
	
	AITECHDEMONSTRATOR_API		UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_ActivateFail_IsDead);
	AITECHDEMONSTRATOR_API		UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_ActivateFail_Cooldown);
	AITECHDEMONSTRATOR_API		UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_ActivateFail_Cost);
	AITECHDEMONSTRATOR_API		UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_ActivateFail_TagsBlocked);
	AITECHDEMONSTRATOR_API		UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_ActivateFail_TagsMissing);
	AITECHDEMONSTRATOR_API		UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_ActivateFail_Networking);
	AITECHDEMONSTRATOR_API		UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_ActivateFail_ActivationGroup);
	
	AITECHDEMONSTRATOR_API		UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Behaviour_SurvivesDeath);
	
	AITECHDEMONSTRATOR_API		UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Move);
	AITECHDEMONSTRATOR_API		UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Look_Mouse);
	AITECHDEMONSTRATOR_API		UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Look_Stick);
	AITECHDEMONSTRATOR_API		UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Crouch);
	AITECHDEMONSTRATOR_API		UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_AutoRun);
	
	AITECHDEMONSTRATOR_API		UE_DECLARE_GAMEPLAY_TAG_EXTERN(InitState_Spawned);
	AITECHDEMONSTRATOR_API		UE_DECLARE_GAMEPLAY_TAG_EXTERN(InitState_DataAvailable);
	AITECHDEMONSTRATOR_API		UE_DECLARE_GAMEPLAY_TAG_EXTERN(InitState_DataInitialized);
	AITECHDEMONSTRATOR_API		UE_DECLARE_GAMEPLAY_TAG_EXTERN(InitState_GameplayReady);

	AITECHDEMONSTRATOR_API		UE_DECLARE_GAMEPLAY_TAG_EXTERN(GameplayEvent_Death);
	AITECHDEMONSTRATOR_API		UE_DECLARE_GAMEPLAY_TAG_EXTERN(GameplayEvent_Reset);
	AITECHDEMONSTRATOR_API		UE_DECLARE_GAMEPLAY_TAG_EXTERN(GameplayEvent_RequestReset);

	AITECHDEMONSTRATOR_API		UE_DECLARE_GAMEPLAY_TAG_EXTERN(SetByCaller_Damage);
	AITECHDEMONSTRATOR_API		UE_DECLARE_GAMEPLAY_TAG_EXTERN(SetByCaller_Heal);

	AITECHDEMONSTRATOR_API		UE_DECLARE_GAMEPLAY_TAG_EXTERN(Status_Crouching);
	AITECHDEMONSTRATOR_API		UE_DECLARE_GAMEPLAY_TAG_EXTERN(Status_AutoRunning);
	AITECHDEMONSTRATOR_API		UE_DECLARE_GAMEPLAY_TAG_EXTERN(Status_Death);
	AITECHDEMONSTRATOR_API		UE_DECLARE_GAMEPLAY_TAG_EXTERN(Status_Death_Dying);
	AITECHDEMONSTRATOR_API		UE_DECLARE_GAMEPLAY_TAG_EXTERN(Status_Death_Dead);

	// These are mappings from movement mode enums to Gameplay Tags associated with those enums (below)
	AITECHDEMONSTRATOR_API		extern const TMap<uint8, FGameplayTag> MovementModeTagMap;
	AITECHDEMONSTRATOR_API		extern const TMap<uint8, FGameplayTag> CustomMovementModeTagMap;

	AITECHDEMONSTRATOR_API		UE_DECLARE_GAMEPLAY_TAG_EXTERN(Movement_Mode_Walking);
	AITECHDEMONSTRATOR_API		UE_DECLARE_GAMEPLAY_TAG_EXTERN(Movement_Mode_NavWalking);
	AITECHDEMONSTRATOR_API		UE_DECLARE_GAMEPLAY_TAG_EXTERN(Movement_Mode_Falling);
	AITECHDEMONSTRATOR_API		UE_DECLARE_GAMEPLAY_TAG_EXTERN(Movement_Mode_Swimming);
	AITECHDEMONSTRATOR_API		UE_DECLARE_GAMEPLAY_TAG_EXTERN(Movement_Mode_Flying);

	AITECHDEMONSTRATOR_API		UE_DECLARE_GAMEPLAY_TAG_EXTERN(Movement_Mode_Custom);
}
