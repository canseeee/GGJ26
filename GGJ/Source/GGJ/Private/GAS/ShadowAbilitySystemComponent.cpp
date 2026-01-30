// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/ShadowAbilitySystemComponent.h"

#include "GAS/ShadowAttributeSet.h"


void UShadowAbilitySystemComponent::AbilityActorInfoSet()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UShadowAbilitySystemComponent::EffectApplied);
}

void UShadowAbilitySystemComponent::AbilityInputTagPressed(const FGameplayTag& InputTag)
{
	if (!InputTag.IsValid()) return;
	FScopedAbilityListLock ActiveScopeLoc(*this);
	for (FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		if (AbilitySpec.DynamicAbilityTags.HasTagExact(InputTag))
		{
			AbilitySpecInputPressed(AbilitySpec);
			if(!AbilitySpec.IsActive())
			{
				if (AbilitySpec.Handle.IsValid())
				{
					TryActivateAbility(AbilitySpec.Handle);
				}
			}
			if (AbilitySpec.IsActive())
			{
				InvokeReplicatedEvent(EAbilityGenericReplicatedEvent::InputPressed, AbilitySpec.Handle, AbilitySpec.ActivationInfo.GetActivationPredictionKey());
			}
		}
	}
}

void UShadowAbilitySystemComponent::AbilityInputTagHeld(const FGameplayTag& InputTag)
{
	if (!InputTag.IsValid()) return;
	FScopedAbilityListLock ActiveScopeLoc(*this);
	for (FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		if (AbilitySpec.DynamicAbilityTags.HasTagExact(InputTag))
		{
			AbilitySpecInputPressed(AbilitySpec);
			if (!AbilitySpec.IsActive())
			{
				TryActivateAbility(AbilitySpec.Handle);
			}
		}
	}
}

void UShadowAbilitySystemComponent::AbilityInputTagReleased(const FGameplayTag& InputTag)
{
	if (!InputTag.IsValid()) return;
	FScopedAbilityListLock ActiveScopeLoc(*this);
	for (FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		if (AbilitySpec.DynamicAbilityTags.HasTagExact(InputTag) && AbilitySpec.IsActive())
		{
			AbilitySpecInputReleased(AbilitySpec);
			InvokeReplicatedEvent(EAbilityGenericReplicatedEvent::InputReleased, AbilitySpec.Handle, AbilitySpec.ActivationInfo.GetActivationPredictionKey());
		}
	}
}

void UShadowAbilitySystemComponent::EffectApplied(UAbilitySystemComponent* AbilitySystemComponent,const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle)
{
	for(auto& Tag : EffectSpec.GetDynamicAssetTags())
	{
		if(!Tag.MatchesTag(FGameplayTag::RequestGameplayTag("Effect.EnergyIncreased")))continue;
		if(EnergyGlobeArray.Num() >= 5)
		{
			EnergyGlobeArray.RemoveAt(0);
		}
		if(Tag.MatchesTagExact(FGameplayTag::RequestGameplayTag("Effect.EnergyIncreased.Green")))
		{
			EnergyGlobeArray.Add(EEnergyGlobeClass::Green);
			return;	
		}
		if(Tag.MatchesTagExact(FGameplayTag::RequestGameplayTag("Effect.EnergyIncreased.Red")))
		{
			EnergyGlobeArray.Add(EEnergyGlobeClass::Red);
			return;	
		}
		if(Tag.MatchesTagExact(FGameplayTag::RequestGameplayTag("Effect.EnergyIncreased.White")))
		{
			EnergyGlobeArray.Add(EEnergyGlobeClass::White);
			return;	
		}
	}
}

void UShadowAbilitySystemComponent::OnEnergyChanged()
{
	EnergyChanged.Broadcast(EnergyGlobeArray);
}