// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ActiveGameplayEffectHandle.h"
#include "AttributeSet.h"
#include "GameplayTagContainer.h"
#include "GameplayAbilitySpecHandle.h"

#include "AITDAbilitySet.generated.h"

class UAttributeSet;
class UGameplayEffect;
class UAITDAbilitySystemComponent;
class UGameplayAbility; //Change this to UAITDGameplayAbility

USTRUCT(BlueprintType)
struct FAITDAbilitySet_GameplayAbility
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AITD Ability Set|Ability")
	TSubclassOf<UGameplayAbility> AITDGameplayAbility = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AITD Ability Set|Ability")
	int32 AbilityLevel = 1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AITD Ability Set|Ability")
	FGameplayTag InputTag;
};

USTRUCT(BlueprintType)
struct FAITDAbilitySet_GameplayEffect
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AITD Ability Set|Effect")
	TSubclassOf<UGameplayEffect> GameplayEffect = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AITD Ability Set|Effect")
	float EffectLevel = 1.0f;
};

USTRUCT(BlueprintType)
struct FAITDAbilitySet_AttributeSet
{
	GENERATED_BODY()

public:
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AITD Ability Set|Attributes")
	TSubclassOf<UAttributeSet> AITDAttributeSet;

};

USTRUCT(BlueprintType)
struct FAITDAbilitySet_GrantedHandles
{
	GENERATED_BODY()

public:

	void AddAbilitySpecHandle(const FGameplayAbilitySpecHandle& Handle);
	void AddGameplayEffectHandle(const FActiveGameplayEffectHandle& Handle);
	void AddAttributeSet(UAttributeSet* Set);

	void TakeFromAbilitySystem(UAITDAbilitySystemComponent* ASC);

protected:

	UPROPERTY()
	TArray<FGameplayAbilitySpecHandle> AbilitySpecHandles;

	UPROPERTY()
	TArray<FActiveGameplayEffectHandle> ActiveGameplayEffectHandles;

	UPROPERTY()
	TArray<TObjectPtr<UAttributeSet>> AttributeSets;

};

/**
 * AITD Ability Set
 * Non mutable data asset used to grant abilities and ability effects
 */
UCLASS()
class AITECHDEMONSTRATOR_API UAITDAbilitySet : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:

	UAITDAbilitySet(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	void GiveToAbilitySystem(UAITDAbilitySystemComponent* ASC, FAITDAbilitySet_GrantedHandles* OutGrantedHandles, UObject* SourceObject = nullptr) const;

protected:

	UPROPERTY(EditDefaultsOnly, Category = "Gameplay Abilities", meta = (TitleProperty=Ability))
	TArray<FAITDAbilitySet_GameplayAbility> GrantedGameplayAbility;

	UPROPERTY(EditDefaultsOnly, Category = "Gameplay Abilities", meta = (TitleProperty = Ability))
	TArray<FAITDAbilitySet_GameplayEffect> GrantedGameplayEffects;

	UPROPERTY(EditDefaultsOnly, Category = "Gameplay Abilities", meta = (TitleProperty = Ability))
	TArray<FAITDAbilitySet_AttributeSet> GrantedAttributes;
	
};
