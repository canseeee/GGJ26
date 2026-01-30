// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Abilities/ShadowGameplayAbility.h"
#include "AbilitySystemComponent.h"

void UShadowGameplayAbility::IncreaseEnergyBar()
{
	UAbilitySystemComponent* ASC = GetAbilitySystemComponentFromActorInfo();
	FGameplayEffectContextHandle ContextHandle = ASC->MakeEffectContext();
	const FGameplayEffectSpecHandle EffectSpecHandle = ASC->MakeOutgoingSpec(EnergyEffect,1.f,ContextHandle);
	ASC->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());
}

void UShadowGameplayAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	// 触发能力结束委托
	OnAbilityEnded.Broadcast();
	
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}
