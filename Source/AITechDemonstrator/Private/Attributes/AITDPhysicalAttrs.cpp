// Fill out your copyright notice in the Description page of Project Settings.


#include "Attributes/AITDPhysicalAttrs.h"
#include "GameplayEffectExtension.h"
#include "Abilities/AITDAbilitySystemComponent.h"

UE_DEFINE_GAMEPLAY_TAG(TAG_Gameplay_Damage, "Gameplay.Damage");
UE_DEFINE_GAMEPLAY_TAG(TAG_Gameplay_DamageImmunity, "Gameplay.Damage.Immunity");

UAITDPhysicalAttrs::UAITDPhysicalAttrs()
{
}

void UAITDPhysicalAttrs::ClampAttribute(const FGameplayAttribute& Attribute, float& NewVal) const
{
}