// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ShadowGameplayAbility.h"
#include "ShadowMeleeAttackAbility.generated.h"

/**
 * 
 */
UCLASS()
class GGJ_API UShadowMeleeAttackAbility : public UShadowGameplayAbility
{
	GENERATED_BODY()

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;


public:
	UPROPERTY(EditDefaultsOnly,Category="Shadow | Data")
	UAnimMontage* MeleeAttackMontage;
	
};
