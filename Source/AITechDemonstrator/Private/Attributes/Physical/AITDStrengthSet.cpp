// Fill out your copyright notice in the Description page of Project Settings.


#include "Attributes/Physical/AITDStrengthSet.h"
#include "GameplayEffectExtension.h"
#include "Abilities/AITDAbilitySystemComponent.h"


UE_DEFINE_GAMEPLAY_TAG(TAG_Agent_Strength, "Character.Traits.Physical.Strength");

UAITDStrengthSet::UAITDStrengthSet()
	: Strength(100.0f)
	, MaxStrength(100.0f)
{
	bIsStrengthZero = false;
	StrengthBeforeAttrChanged = 0.0f;
	MaxStrengthBeforeAttrChanged = 0.0f;

	GetAttributesFromSetClass(this->StaticClass(), AttrList);
}

bool UAITDStrengthSet::PreGameplayEffectExecute(FGameplayEffectModCallbackData& Data)
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
				// Do not take away any Strength.
				Data.EvaluatedData.Magnitude = 0.0f;
				return false;
			}
		}
	}

	// Save the current Strength
	StrengthBeforeAttrChanged = GetStrength();
	MaxStrengthBeforeAttrChanged = GetMaxStrength();

	return true;
}

void UAITDStrengthSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	float MinimumStrength = 0.0f;

	const FGameplayEffectContextHandle& EffectContext = Data.EffectSpec.GetEffectContext();
	AActor* Instigator = EffectContext.GetOriginalInstigator();
	AActor* Causer = EffectContext.GetEffectCauser();

	if (Data.EvaluatedData.Attribute == GetDamageAttribute())
	{
		// Convert into -Strength and then clamp
		SetStrength(FMath::Clamp(GetStrength() - GetDamage(), MinimumStrength, GetMaxStrength()));
		SetDamage(0.0f);
	}
	else if (Data.EvaluatedData.Attribute == GetHealingAttribute())
	{
		// Convert into +Strength and then clamo
		SetStrength(FMath::Clamp(GetStrength() + GetHealing(), MinimumStrength, GetStrength()));
		SetHealing(0.0f);
	}
	else if (Data.EvaluatedData.Attribute == GetStrengthAttribute())
	{
		// Clamp and fall into out of Strength handling below
		SetStrength(FMath::Clamp(GetStrength(), MinimumStrength, GetStrength()));
	}
	else if (Data.EvaluatedData.Attribute == GetMaxStrengthAttribute())
	{
		// Notify on any requested max Strength changes
		OnMaxStrengthChanged.Broadcast(Instigator, Causer, Data.EffectSpec, Data.EvaluatedData.Magnitude, MaxStrengthBeforeAttrChanged, GetMaxStrength());
	}

	// If Strength has actually changed activate callbacks
	if (GetStrength() != StrengthBeforeAttrChanged)
	{
		OnStrengthChanged.Broadcast(Instigator, Causer, Data.EffectSpec, Data.EvaluatedData.Magnitude, StrengthBeforeAttrChanged, GetStrength());
	}

	if ((GetStrength() <= 0.0f) && !bIsStrengthZero)
	{
		OnOutOfStrength.Broadcast(Instigator, Causer, Data.EffectSpec, Data.EvaluatedData.Magnitude, StrengthBeforeAttrChanged, GetStrength());
	}

	// Check Strength again in case an event above changed it.
	bIsStrengthZero = (GetStrength() <= 0.0f);
}

void UAITDStrengthSet::PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const
{
	Super::PreAttributeBaseChange(Attribute, NewValue);
	ClampAttribute(Attribute, NewValue);
}

void UAITDStrengthSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);
	ClampAttribute(Attribute, NewValue);
}

void UAITDStrengthSet::PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue)
{
	Super::PostAttributeChange(Attribute, OldValue, NewValue);

	if (Attribute == GetMaxStrengthAttribute())
	{
		// Make sure current Strength is not greater than the new max Strength.
		if (GetStrength() > NewValue)
		{
			UAITDAbilitySystemComponent* AITDASC = GetAbilitySystemComponent();
			check(AITDASC);

			AITDASC->ApplyModToAttribute(GetStrengthAttribute(), EGameplayModOp::Override, NewValue);
		}
	}

	if (bIsStrengthZero && (GetStrength() > 0.0f))
	{
		bIsStrengthZero = false;
	}
}

void UAITDStrengthSet::ClampAttribute(const FGameplayAttribute& Attribute, float& NewVal) const
{
	if (Attribute == GetMaxStrengthAttribute())
	{
		// Don't let the Max Health Value fall below 1.0
		NewVal = FMath::Max(GetMaxStrength(), 1.0f);
	}
	else
	{
		NewVal = FMath::Clamp(NewVal, 0.0f, GetMaxStrength());
	}
}
