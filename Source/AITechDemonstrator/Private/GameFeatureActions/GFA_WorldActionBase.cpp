// Fill out your copyright notice in the Description page of Project Settings.


#include "GameFeatureActions/GFA_WorldActionBase.h"
#include "Engine/GameInstance.h"
#include "Engine/World.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(GFA_WorldActionBase)

void UGFA_WorldActionBase::OnGameFeatureActivating(FGameFeatureActivatingContext& Context)
{
	GameInstanceStartHandles.FindOrAdd(Context) = FWorldDelegates::OnStartGameInstance.AddUObject(this, 
		&UGFA_WorldActionBase::HandleGameInstanceStart, FGameFeatureStateChangeContext(Context));

	// Add to any worlds with associated game instances which have already been initialized
	for (const FWorldContext& WorldContext : GEngine->GetWorldContexts())
	{
		if (Context.ShouldApplyToWorldContext(WorldContext))
		{
			AddToWorld(WorldContext, Context);
		}
	}
}

void UGFA_WorldActionBase::OnGameFeatureDeactivating(FGameFeatureDeactivatingContext& Context)
{
	FDelegateHandle* Handle = GameInstanceStartHandles.Find(Context);
	if (ensure(Handle))
	{
		FWorldDelegates::OnStartGameInstance.Remove(*Handle);
	}
}

void UGFA_WorldActionBase::HandleGameInstanceStart(UGameInstance* GameInstance, FGameFeatureStateChangeContext ChangeContext)
{
	if (FWorldContext* WorldContext = GameInstance->GetWorldContext())
	{
		if (ChangeContext.ShouldApplyToWorldContext(*WorldContext))
		{
			AddToWorld(*WorldContext, ChangeContext);
		}
	}
}
