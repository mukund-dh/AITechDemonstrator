// Fill out your copyright notice in the Description page of Project Settings.


#include "Attributes/AIBaseAttributes.h"
#include "Abilities/AITDAbilitySystemComponent.h"

UAIBaseAttributes::UAIBaseAttributes()
{
}

UWorld* UAIBaseAttributes::GetWorld() const
{
	const UObject* Outer = GetOuter();
	check(Outer);

	return Outer->GetWorld();
}

UAITDAbilitySystemComponent* UAIBaseAttributes::GetAbilitySystemComponent() const
{
	return Cast<UAITDAbilitySystemComponent>(GetOwningAbilitySystemComponent());
}
