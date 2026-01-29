// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Abilities/ShadowGameplayAbility.h"

void UShadowGameplayAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	// 触发能力结束委托
	OnAbilityEnded.Broadcast();
	
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}
