// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ShadowGameplayAbility.h"
#include "Interface/CombatInterface.h"
#include "ShadowMeleeAttackAbility.generated.h"

/**
 * 
 */
UCLASS()
class GGJ_API UShadowMeleeAttackAbility : public UShadowGameplayAbility, public ICombatInterface
{
	GENERATED_BODY()



public:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

	UFUNCTION(BlueprintCallable)
	UCapsuleComponent* GetCapsuleComponent();
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly,Category="Shadow | Data")
	UAnimMontage* MeleeAttackMontage;
	
};
