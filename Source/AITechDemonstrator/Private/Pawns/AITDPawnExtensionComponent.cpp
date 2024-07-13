// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawns/AITDPawnExtensionComponent.h"
#include "Abilities/AITDAbilitySystemComponent.h"
#include "Components/GameFrameworkComponentDelegates.h"
#include "Components/GameFrameworkComponentManager.h"
#include "GameFramework/Controller.h"
#include "Misc/AITDGameplayTags.h"
#include "Pawns/AITDPawnData.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(AITDPawnExtensionComponent)

class UActorComponent;
const FName UAITDPawnExtensionComponent::NAME_ActorFeatureName("AITDPawnExtension");

UAITDPawnExtensionComponent::UAITDPawnExtensionComponent(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    PrimaryComponentTick.bStartWithTickEnabled = false;
    PrimaryComponentTick.bCanEverTick = false;

    PawnData = nullptr;
    AbilitySystemComponent = nullptr;
}

bool UAITDPawnExtensionComponent::CanChangeInitState(UGameFrameworkComponentManager* Manager, FGameplayTag CurrentState, FGameplayTag DesiredState) const
{
    check(Manager);

    APawn* Pawn = GetPawn<APawn>();
    if (!CurrentState.IsValid() && DesiredState == AITDGameplayTags::InitState_Spawned)
    {
        if (Pawn)
        {
            // If our pawn is valid, assume that we have already spawned
            return true;
        }

        const bool bHasAuthority = Pawn->HasAuthority();
        const bool bIsLocallyControlled = Pawn->IsLocallyControlled();

        if (bHasAuthority || bIsLocallyControlled)
        {
            // Check for being possessed by a controller
            if (!Pawn->GetController<AController>())
            {
                return false;
            }
        }

        return true;
    }
    else if (CurrentState == AITDGameplayTags::InitState_DataAvailable && DesiredState == AITDGameplayTags::InitState_DataInitialized)
    {
        // Transition to initialize if all states have their data available
        return Manager->HaveAllFeaturesReachedInitState(Pawn, AITDGameplayTags::InitState_DataAvailable);
    }
    else if (CurrentState == AITDGameplayTags::InitState_DataInitialized && DesiredState == AITDGameplayTags::InitState_GameplayReady)
    {
        return true;
    }

    return false;
}

void UAITDPawnExtensionComponent::HandleChangeInitState(UGameFrameworkComponentManager* Manager, FGameplayTag CurrentState, FGameplayTag DesiredState)
{
    if (DesiredState == AITDGameplayTags::InitState_DataInitialized)
    {
        // This is currently handled by all other components listening for this state change
    }
}

void UAITDPawnExtensionComponent::OnActorInitStateChanged(const FActorInitStateChangedParams& Params)
{
    if (Params.FeatureName != NAME_ActorFeatureName)
    {
        if (Params.FeatureState == AITDGameplayTags::InitState_DataAvailable)
        {
            CheckDefaultInitialization();
        }
    }
}

void UAITDPawnExtensionComponent::CheckDefaultInitialization()
{
    // Before processing our Init, try progressing any other features we may depend on
    CheckDefaultInitializationForImplementers();

    static const TArray<FGameplayTag> StateChain = { AITDGameplayTags::InitState_Spawned, AITDGameplayTags::InitState_DataAvailable, AITDGameplayTags::InitState_DataInitialized, AITDGameplayTags::InitState_GameplayReady };

    // This will try to progress from spawned (which is available in Begin Play) through the data initialization stages till we get to gameplay ready
    ContinueInitStateChain(StateChain);
}

void UAITDPawnExtensionComponent::SetPawnData(const UAITDPawnData* InData)
{
    check (InData);

    APawn* Pawn = GetPawnChecked<APawn>();

    if (Pawn->GetLocalRole() != ROLE_Authority)
    {
        return;
    }

    if (PawnData)
    {
        UE_LOG(LogTemp, Error, TEXT("Trying to set PawnData [%s] on pawn [%s] that already has valid PawnData [%s]."), *GetNameSafe(InData), *GetNameSafe(Pawn), *GetNameSafe(PawnData));
        return;
    }

    PawnData = InData;

    CheckDefaultInitialization();
}

void UAITDPawnExtensionComponent::InitializeAbilitySystem(UAITDAbilitySystemComponent* ASC, AActor* OwnerActor)
{
    check(ASC);
    check(OwnerActor);

    if (AbilitySystemComponent == ASC)
    {
        return;
    }

    if (AbilitySystemComponent)
    {
        UninitializeAbilitySystem();
    }

    APawn* Pawn = GetPawnChecked<APawn>();
    AActor* ExistingAvatar = ASC->GetAvatarActor();

    UE_LOG(LogTemp, Verbose, TEXT("Setting up ASC [%s] on pawn [%s] owner [%s], existing [%s] "), *GetNameSafe(ASC), *GetNameSafe(Pawn), *GetNameSafe(OwnerActor), *GetNameSafe(ExistingAvatar));

    if ((ExistingAvatar != nullptr) && (ExistingAvatar != Pawn))
    {
        UE_LOG(LogTemp, Log, TEXT("Existing avatar (authority=%d)"), ExistingAvatar->HasAuthority() ? 1 : 0);

        // There is already a pawn acting as the ASC's avatar, so we need to kick it out
		// This can happen on clients if they're lagged: their new pawn is spawned + possessed before the dead one is removed
        ensure(!ExistingAvatar->HasAuthority());

        if (UAITDPawnExtensionComponent* OtherExtensionComponent = FindPawnExtensionComponent(ExistingAvatar))
        {
            OtherExtensionComponent->UninitializeAbilitySystem();
        }

        AbilitySystemComponent = ASC;
        AbilitySystemComponent->InitAbilityActorInfo(OwnerActor, Pawn);

        if (ensure(PawnData))
        {
            //ASC->SetTagRelationshipMapping(PawnData->TagRelationshipMapping);
        }

        OnAbilitySystemInitialized.Broadcast();
    }
}

void UAITDPawnExtensionComponent::UninitializeAbilitySystem()
{
    if (!AbilitySystemComponent)
    {
        return;
    }

    // Uninitialize the ASC if we're still the avatar actor (otherwise another pawn already did it when they became the avatar actor)
    if (AbilitySystemComponent->GetAvatarActor() == GetOwner())
    {
        FGameplayTagContainer AbilityTypesToIgnore;
        AbilityTypesToIgnore.AddTag(AITDGameplayTags::Ability_Behaviour_SurvivesDeath);

        AbilitySystemComponent->CancelAbilities(nullptr, &AbilityTypesToIgnore);
        //AbilitySystemComponent->ClearAbilityInput();
        AbilitySystemComponent->RemoveAllGameplayCues();

        if (AbilitySystemComponent->GetOwnerActor() != nullptr)
        {
            AbilitySystemComponent->SetAvatarActor(nullptr);
        }
        else
        {
            // If an avatar actor doesn't exist, clear *ALL* actor info
            AbilitySystemComponent->ClearActorInfo();
        }

        OnAbilitySystemUninitialized.Broadcast();
    }

    AbilitySystemComponent = nullptr;
}

void UAITDPawnExtensionComponent::HandleControllerChanged()
{
    if (AbilitySystemComponent && AbilitySystemComponent->GetAvatarActor() == GetPawnChecked<APawn>())
    {
        ensure(AbilitySystemComponent->AbilityActorInfo->OwnerActor == AbilitySystemComponent->GetOwnerActor());
        if (AbilitySystemComponent->GetOwnerActor() == nullptr)
        {
            UninitializeAbilitySystem();
        }
        else
        {
            AbilitySystemComponent->RefreshAbilityActorInfo();
        }
    }

    CheckDefaultInitialization();
}

void UAITDPawnExtensionComponent::HandlePlayerStateReplicated()
{
    CheckDefaultInitialization();
}

void UAITDPawnExtensionComponent::SetupPlayerInputComponent()
{
    CheckDefaultInitialization();
}

void UAITDPawnExtensionComponent::OnAbilitySystemInitialized_RegisterAndCall(FSimpleMulticastDelegate::FDelegate Delegate)
{
    if (!OnAbilitySystemInitialized.IsBoundToObject(Delegate.GetUObject()))
    {
        OnAbilitySystemInitialized.Add(Delegate);
    }

    if (AbilitySystemComponent)
    {
        Delegate.Execute();
    }
}

void UAITDPawnExtensionComponent::OnAbilitySystemUninitialized_Register(FSimpleMulticastDelegate::FDelegate Delegate)
{
    if (!OnAbilitySystemUninitialized.IsBoundToObject(Delegate.GetUObject()))
    {
        OnAbilitySystemUninitialized.Add(Delegate);
    }
}

void UAITDPawnExtensionComponent::OnRegister()
{
    Super::OnRegister();

    const APawn* Pawn = GetPawn<APawn>();
    ensureAlwaysMsgf((Pawn != nullptr), TEXT("AITDPawnExtensionComponent on [%s] can only be added to Pawn actors."), *GetNameSafe(GetOwner()));

    TArray<UActorComponent*> PawnExtensionComponents;
    Pawn->GetComponents(UAITDPawnExtensionComponent::StaticClass(), PawnExtensionComponents);
    ensureAlwaysMsgf((PawnExtensionComponents.Num() == 1), TEXT("Only one AITDPawnExtensionComponent should exist on [%s]."), *GetNameSafe(GetOwner()));

    // Register the init state system early, this will only work with a game world.
    RegisterInitStateFeature();
}

void UAITDPawnExtensionComponent::BeginPlay()
{
    Super::BeginPlay();

    // Listen for changes to all features
    BindOnActorInitStateChanged(NAME_None, FGameplayTag(), false);

    // Notifies the state manager that we have spawned, then try rest of the default initialization
    ensure(TryToChangeInitState(AITDGameplayTags::InitState_Spawned));
    CheckDefaultInitialization();
}

void UAITDPawnExtensionComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
}
