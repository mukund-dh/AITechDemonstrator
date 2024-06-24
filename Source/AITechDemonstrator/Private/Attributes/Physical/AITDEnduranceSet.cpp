// Fill out your copyright notice in the Description page of Project Settings.


#include "Attributes/Physical/AITDEnduranceSet.h"
#include "GameplayEffectExtension.h"
#include "Abilities/AITDAbilitySystemComponent.h"


UE_DEFINE_GAMEPLAY_TAG(TAG_Agent_Endurance, "Character.Traits.Physical.Endurance");

UAITDEnduranceSet::UAITDEnduranceSet()
	: Endurance(100.0f)
	, MaxEndurance(100.0f)
{
	bIsEnduranceZero = false;
	EnduranceBeforeAttrChanged = 0.0f;
	MaxEnduranceBeforeAttrChanged = 0.0f;

	GetAttributesFromSetClass(this->StaticClass(), AttrList);
}

bool UAITDEnduranceSet::PreGameplayEffectExecute(FGameplayEffectModCallbackData& Data)
{
	if (!Super::PreGameplayEffectExecute(Data))
	{
		return false;
	}

	if (Data.EvaluatedData.Attribute == GetDamageAttribute())
	{
		if (Data.EvaluatedData.Magnitude > 0.0f)
		{
			if (Data.Target.HasMatchingGameplayTag(TAG_Gameplay_DamageImmunity))
			{
				// Do not take away any Endurance.
				Data.EvaluatedData.Magnitude = 0.0f;
				return false;
			}
		}
	}

	// Save the current Endurance
	EnduranceBeforeAttrChanged = GetEndurance();
	MaxEnduranceBeforeAttrChanged = GetMaxEndurance();

	return true;
}

void UAITDEnduranceSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	float MinimumEndurance = 0.0f;

	const FGameplayEffectContextHandle& EffectContext = Data.EffectSpec.GetEffectContext();
	AActor* Instigator = EffectContext.GetOriginalInstigator();
	AActor* Causer = EffectContext.GetEffectCauser();

	if (Data.EvaluatedData.Attribute == GetDamageAttribute())
	{
		// Convert into -Endurance and then clamp
		SetEndurance(FMath::Clamp(GetEndurance() - GetDamage(), MinimumEndurance, GetMaxEndurance()));
		SetDamage(0.0f);
	}
	else if (Data.EvaluatedData.Attribute == GetHealingAttribute())
	{
		// Convert into +Endurance and then clamo
		SetEndurance(FMath::Clamp(GetEndurance() + GetHealing(), MinimumEndurance, GetEndurance()));
		SetHealing(0.0f);
	}
	else if (Data.EvaluatedData.Attribute == GetEnduranceAttribute())
	{
		// Clamp and fall into out of Endurance handling below
		SetEndurance(FMath::Clamp(GetEndurance(), MinimumEndurance, GetEndurance()));
	}
	else if (Data.EvaluatedData.Attribute == GetMaxEnduranceAttribute())
	{
		// Notify on any requested max Endurance changes
		OnMaxEnduranceChanged.Broadcast(Instigator, Causer, Data.EffectSpec, Data.EvaluatedData.Magnitude, MaxEnduranceBeforeAttrChanged, GetMaxEndurance());
	}

	// If Endurance has actually changed activate callbacks
	if (GetEndurance() != EnduranceBeforeAttrChanged)
	{
		OnEnduranceChanged.Broadcast(Instigator, Causer, Data.EffectSpec, Data.EvaluatedData.Magnitude, EnduranceBeforeAttrChanged, GetEndurance());
	}

	if ((GetEndurance() <= 0.0f) && !bIsEnduranceZero)
	{
		OnOutOfEndurance.Broadcast(Instigator, Causer, Data.EffectSpec, Data.EvaluatedData.Magnitude, EnduranceBeforeAttrChanged, GetEndurance());
	}

	// Check Endurance again in case an event above changed it.
	bIsEnduranceZero = (GetEndurance() <= 0.0f);
}

void UAITDEnduranceSet::PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const
{
	Super::PreAttributeBaseChange(Attribute, NewValue);
	ClampAttribute(Attribute, NewValue);
}

void UAITDEnduranceSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);
	ClampAttribute(Attribute, NewValue);
}

void UAITDEnduranceSet::PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue)
{
	Super::PostAttributeChange(Attribute, OldValue, NewValue);

	if (Attribute == GetMaxEnduranceAttribute())
	{
		// Make sure current Endurance is not greater than the new max Endurance.
		if (GetEndurance() > NewValue)
		{
			UAITDAbilitySystemComponent* AITDASC = GetAbilitySystemComponent();
			check(AITDASC);

			AITDASC->ApplyModToAttribute(GetEnduranceAttribute(), EGameplayModOp::Override, NewValue);
		}
	}

	if (bIsEnduranceZero && (GetEndurance() > 0.0f))
	{
		bIsEnduranceZero = false;
	}
}

void UAITDEnduranceSet::ClampAttribute(const FGameplayAttribute& Attribute, float& NewVal) const
{
	if (Attribute == GetMaxEnduranceAttribute())
	{
		// Don't let the Max Health Value fall below 1.0
		NewVal = FMath::Max(GetMaxEndurance(), 1.0f);
	}
	else
	{
		NewVal = FMath::Clamp(NewVal, 0.0f, GetMaxEndurance());
	}
}
