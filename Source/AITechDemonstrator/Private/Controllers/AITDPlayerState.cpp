// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/AITDPlayerState.h"
#include "Controllers/AITDAICon.h"
#include "Controllers/AITDPlayerController.h"
#include "Attributes/AILizardBrainAttrs.h"
#include "Attributes/AITDPhysicalAttrs.h"
#include "Abilities/AITDAbilitySystemComponent.h"

AAITDPlayerState::AAITDPlayerState(const FObjectInitializer& ObjectInitializer)
{
	AbilitySystemComponent = CreateDefaultSubobject<UAITDAbilitySystemComponent>(TEXT("Ability System Component"));
	LizardBrainAttrs = CreateDefaultSubobject<UAILizardBrainAttrs>(TEXT("Lizard Brain Attributes"));
	PhysicalAttrs = CreateDefaultSubobject<UAITDPhysicalAttrs>(TEXT("Physical Attributes"));

	MyTeamID = FGenericTeamId::NoTeam;
	MySquadID = INDEX_NONE;
}

AController* AAITDPlayerState::GetAITDController() const
{
	// Can return an AI Controller OR a player controller based on 
	// what this player state is parented to.
	return Cast<AController>(GetOwner());
}

UAbilitySystemComponent* AAITDPlayerState::GetAbilitySystemComponent() const
{
	return GetAITDAbilitySystemComponent();
}

void AAITDPlayerState::SetGenericTeamId(const FGenericTeamId& NewTeamId)
{
	if (HasAuthority())
	{
		const FGenericTeamId OldTeamID = MyTeamID;

		MyTeamID = NewTeamId;
		ConditionalBroadcastTeamChanged(this, OldTeamID, NewTeamId);
	}
}

FGenericTeamId AAITDPlayerState::GetGenericTeamId() const
{
	return MyTeamID;
}

FOnAITDTeamChangedDelegate* AAITDPlayerState::GetOnAITDTeamChangedDelegate()
{
	return &AITDTeamChangedDelegate;
}

void AAITDPlayerState::SetSquadID(int32 NewSquadID)
{
	if (HasAuthority())
	{
		MySquadID = NewSquadID;
	}
}
