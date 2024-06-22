// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Attributes/AIBaseAttributes.h"
#include "NativeGameplayTags.h"
#include "GameplayEffectExtension.h"
#include "AITDHealthSet.generated.h"

UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Gameplay_Damage);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Gameplay_DamageImmunity);

/**
 * 
 */
UCLASS()
class AITECHDEMONSTRATOR_API UAITDHealthSet : public UAIBaseAttributes
{
	GENERATED_BODY()

public:

	UAITDHealthSet();

	ATTRIBUTE_ACCESSORS(UAITDHealthSet, Health);
	ATTRIBUTE_ACCESSORS(UAITDHealthSet, MaxHealth);

	ATTRIBUTE_ACCESSORS(UAITDHealthSet, Damage);
	ATTRIBUTE_ACCESSORS(UAITDHealthSet, Healing);

	mutable FAITDAttributeChangedEvent HealthChanged;

	mutable FAITDAttributeChangedEvent MaxHealthChanged;

	mutable FAITDAttributeChangedEvent OutOfHealth;

	virtual bool PreGameplayEffectExecute(FGameplayEffectModCallbackData& Data) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	virtual void PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const override;
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) override;

	void ClampAttribute(const FGameplayAttribute& Attribute, float NewVal) const;

private:

	// Define Attributes and their related maxes
	UPROPERTY(BlueprintReadOnly, Category = "PhysicalAttributes", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData Health;

	UPROPERTY(BlueprintReadOnly, Category = "PhysicalAttributes", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxHealth;

	// Keep track of when health falls to 0
	bool bIsOutOfHealth;

	// Keep track of any changes we might experience
	float HealthBeforeAttributeChanged;
	float MaxHealthBeforeAttributeChanged;

	//--------------------------------------------------------------------------------------------------------
	// META ATTRIBUTES - They don't really need to be tracked, but will kick in when any execution happens
	//--------------------------------------------------------------------------------------------------------
	
	// Incoming Healing. Mapped directly to +Health; over a curve to +Strength, +Endurance
	UPROPERTY(BlueprintReadOnly, Category = "PhysicalAttributes", Meta = (HideFromModifiers, AllowPrivateAccess = true))
	FGameplayAttributeData Healing;

	// Incoming Damage. Mapped directly to -Health; over a curve to -Strength, -Endurance
	UPROPERTY(BlueprintReadOnly, Category = "PhysicalAttributes", Meta = (HideFromModifiers, AllowPrivateAccess = true))
	FGameplayAttributeData Damage;
	
};
