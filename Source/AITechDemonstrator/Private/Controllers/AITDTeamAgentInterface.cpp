// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/AITDTeamAgentInterface.h"

// Add default functionality here for any IAITDTeamAgentInterface functions that are not pure virtual.

UAITDTeamAgentInterface::UAITDTeamAgentInterface(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void IAITDTeamAgentInterface::ConditionalBroadcastTeamChanged(TScriptInterface<IAITDTeamAgentInterface> This, FGenericTeamId OldTeamID, FGenericTeamId NewTeamID)
{
	if (OldTeamID != NewTeamID)
	{
		int32 OldID = GenericTeamIDToInt(OldTeamID);
		int32 NewID = GenericTeamIDToInt(NewTeamID);

		UObject* ThisObject = This.GetObject();

		This.GetInterface()->GetTeamChangedDelegateChecked().Broadcast(ThisObject, OldID, NewID);
	}
}
