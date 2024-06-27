// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawns/AITDPawnData.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(AITDPawnData)

UAITDPawnData::UAITDPawnData(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PawnClass = nullptr;
	InputConfig = nullptr;
	DefaultCameraMode = nullptr;
}
