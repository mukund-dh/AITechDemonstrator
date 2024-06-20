// Fill out your copyright notice in the Description page of Project Settings.


#include "Attributes/AIBaseAttributes.h"

UAIBaseAttributes::UAIBaseAttributes()
{
}

UWorld* UAIBaseAttributes::GetWorld() const
{
	const UObject* Outer = GetOuter();
	check(Outer);

	return Outer->GetWorld();
}

UAbilitySystemComponent* UAIBaseAttributes::GetAbilitySystemComponent() const
{
	return GetOwningAbilitySystemComponent();
}
