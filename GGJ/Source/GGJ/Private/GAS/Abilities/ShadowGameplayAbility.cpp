// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Abilities/ShadowGameplayAbility.h"
#include "AbilitySystemComponent.h"
#include "GAS/ShadowAbilitySystemComponent.h"

void UShadowGameplayAbility::IncreaseEnergyBar()
{
	if (EnergyEffect)
	{
		UAbilitySystemComponent* ASC = GetAbilitySystemComponentFromActorInfo();
		FGameplayEffectContextHandle ContextHandle = ASC->MakeEffectContext();
		const FGameplayEffectSpecHandle EffectSpecHandle = ASC->MakeOutgoingSpec(EnergyEffect,1.f,ContextHandle);
		ASC->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());
		
		UShadowAbilitySystemComponent* US_ASC = Cast<UShadowAbilitySystemComponent>(ASC);
		if (US_ASC)
		{
			US_ASC->OnEnergyChanged();
		}
	}
}

void UShadowGameplayAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	// 触发能力结束委托
	OnAbilityEnded.Broadcast();
	
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}
