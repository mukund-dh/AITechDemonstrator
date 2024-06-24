// Fill out your copyright notice in the Description page of Project Settings.
#include "Attributes/Physical/AITDHealthSet.h"
#include "GameplayEffectExtension.h"
#include "Abilities/AITDAbilitySystemComponent.h"

UE_DEFINE_GAMEPLAY_TAG(TAG_Agent_Health, "Character.Traits.Physical.Health");

UAITDHealthSet::UAITDHealthSet()
	: Health(100.0f)
	, MaxHealth(100.0f)
{
	bIsHealthZero = false;
	HealthBeforeAttrChanged = 0.0f;
	MaxHealthBeforeAttrChanged = 0.0f;

	GetAttributesFromSetClass(this->StaticClass(), AttrList); 
}

bool UAITDHealthSet::PreGameplayEffectExecute(FGameplayEffectModCallbackData& Data)
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
				// Do not take away any health.
				Data.EvaluatedData.Magnitude = 0.0f;
				return false;
			}
		}
	}

	// Save the current health
	HealthBeforeAttrChanged = GetHealth();
	MaxHealthBeforeAttrChanged = GetMaxHealth();

	return true;
}

void UAITDHealthSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	float MinimumHealth = 0.0f;
	
	const FGameplayEffectContextHandle& EffectContext = Data.EffectSpec.GetEffectContext();
	AActor* Instigator = EffectContext.GetOriginalInstigator();
	AActor* Causer = EffectContext.GetEffectCauser();

	if (Data.EvaluatedData.Attribute == GetDamageAttribute())
	{
		// Convert into -Health and then clamp
		SetHealth(FMath::Clamp(GetHealth() - GetDamage(), MinimumHealth, GetMaxHealth()));
		SetDamage(0.0f);
	}
	else if (Data.EvaluatedData.Attribute == GetHealingAttribute())
	{
		// Convert into +Health and then clamo
		SetHealth(FMath::Clamp(GetHealth() + GetHealing(), MinimumHealth, GetHealth()));
		SetHealing(0.0f);
	}
	else if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		// Clamp and fall into out of health handling below
		SetHealth(FMath::Clamp(GetHealth(), MinimumHealth, GetHealth()));
	}
	else if (Data.EvaluatedData.Attribute == GetMaxHealthAttribute())
	{
		// Notify on any requested max health changes
		OnMaxHealthChanged.Broadcast(Instigator, Causer, Data.EffectSpec, Data.EvaluatedData.Magnitude, MaxHealthBeforeAttrChanged, GetMaxHealth());
	}

	// If health has actually changed activate callbacks
	if (GetHealth() != HealthBeforeAttrChanged)
	{
		OnHealthChanged.Broadcast(Instigator, Causer, Data.EffectSpec, Data.EvaluatedData.Magnitude, HealthBeforeAttrChanged, GetHealth());
	}

	if ((GetHealth() <= 0.0f) && !bIsHealthZero)
	{
		OnOutOfHealth.Broadcast(Instigator, Causer, Data.EffectSpec, Data.EvaluatedData.Magnitude, HealthBeforeAttrChanged, GetHealth());
	}

	// Check health again in case an event above changed it.
	bIsHealthZero = (GetHealth() <= 0.0f);
}

void UAITDHealthSet::PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const
{
	Super::PreAttributeBaseChange(Attribute, NewValue);
	ClampAttribute(Attribute, NewValue);
}

void UAITDHealthSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);
	ClampAttribute(Attribute, NewValue);
}

void UAITDHealthSet::PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue)
{
	Super::PostAttributeChange(Attribute, OldValue, NewValue);

	if (Attribute == GetMaxHealthAttribute())
	{
		// Make sure current health is not greater than the new max health.
		if (GetHealth() > NewValue)
		{
			UAITDAbilitySystemComponent* AITDASC = GetAbilitySystemComponent();
			check(AITDASC);

			AITDASC->ApplyModToAttribute(GetHealthAttribute(), EGameplayModOp::Override, NewValue);
		}
	}

	if (bIsHealthZero && (GetHealth() > 0.0f))
	{
		bIsHealthZero = false;
	}
}

void UAITDHealthSet::ClampAttribute(const FGameplayAttribute& Attribute, float& NewVal) const
{
	if (Attribute == GetMaxHealthAttribute())
	{
		// Don't let the Max Health Value fall below 1.0
		NewVal = FMath::Max(GetMaxHealth(), 1.0f);
	}
	else
	{
		NewVal = FMath::Clamp(NewVal, 0.0f, GetMaxHealth());
	}
}