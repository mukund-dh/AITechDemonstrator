// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GenericTeamAgentInterface.h"
#include "AITDTeamAgentInterface.generated.h"

template <typename InterfaceType> class TScriptInterface;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnAITDTeamChangedDelegate, UObject*, Object, int32, OldTeamIndex, int32, NewTeamIndex);


inline int32 GenericTeamIDToInt(FGenericTeamId ID)
{
	return (ID == FGenericTeamId::NoTeam) ? INDEX_NONE : (int32)ID;
}


inline FGenericTeamId IntToGenericTeamId(int32 ID)
{
	return (ID == INDEX_NONE) ? FGenericTeamId::NoTeam : FGenericTeamId((uint8)ID);
}

// This class does not need to be modified.
UINTERFACE(Meta=(CannotImplementInterfaceInBlueprints))
class UAITDTeamAgentInterface : public UGenericTeamAgentInterface
{
	GENERATED_UINTERFACE_BODY()
};

/**
 * 
 */
class AITECHDEMONSTRATOR_API IAITDTeamAgentInterface : public IGenericTeamAgentInterface
{
	GENERATED_IINTERFACE_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	virtual FOnAITDTeamChangedDelegate* GetOnAITDTeamChangedDelegate() { return nullptr; }

	static void ConditionalBroadcastTeamChanged(TScriptInterface<IAITDTeamAgentInterface> This, FGenericTeamId OldTeamID, FGenericTeamId NewTeamID);

	FOnAITDTeamChangedDelegate& GetTeamChangedDelegateChecked()
	{
		FOnAITDTeamChangedDelegate* Result = GetOnAITDTeamChangedDelegate();
		check(Result);
		return *Result;
	}
};
