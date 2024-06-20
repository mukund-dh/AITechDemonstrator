// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/AITDAICon.h"
#include "Controllers/AITDPlayerState.h"
#include "Attributes/AILizardBrainAttrs.h"
#include "AbilitySystemComponent.h"

AAITDAICon::AAITDAICon(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{

	bWantsPlayerState = true;
	bStopAILogicOnUnposses = false;
}

void AAITDAICon::SetGenericTeamId(const FGenericTeamId& NewTeamId)
{
	// Setting the GenericTeamId can only ever happen in the Player State.
	AAITDPlayerState* PS = GetAITDPlayerState();
	if (PS)
	{
		PS->SetGenericTeamId(NewTeamId);
	}
}

FGenericTeamId AAITDAICon::GetGenericTeamId() const
{
	if (IAITDTeamAgentInterface* PSWithTeamInterface = Cast<IAITDTeamAgentInterface>(PlayerState))
	{
		return PSWithTeamInterface->GetGenericTeamId();
	}

	return FGenericTeamId::NoTeam;
}

FOnAITDTeamChangedDelegate* AAITDAICon::GetOnAITDTeamChangedDelegate()
{
	return nullptr;
}

ETeamAttitude::Type AAITDAICon::GetTeamAttitudeTowards(const AActor& Other) const
{
	if (const APawn* OtherPawn = Cast<APawn>(&Other))
	{
		if (const IAITDTeamAgentInterface* TeamAgent = Cast<IAITDTeamAgentInterface>(OtherPawn->GetController()))
		{
			FGenericTeamId OtherId = TeamAgent->GetGenericTeamId();

			if (OtherId.GetId() != GetGenericTeamId().GetId())
			{
				ETeamAttitude::Hostile;
			}
			else
			{
				ETeamAttitude::Friendly;
			}
		}
	}

	return ETeamAttitude::Neutral;
}

AAITDPlayerState* AAITDAICon::GetAITDPlayerState() const
{
	return GetPlayerState<AAITDPlayerState>();
}

void AAITDAICon::UpdateTeamAttitudeTowards(UAIPerceptionComponent* AIPerception)
{
}
