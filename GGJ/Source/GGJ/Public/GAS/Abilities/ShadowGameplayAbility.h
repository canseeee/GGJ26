// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "ShadowGameplayAbility.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAbilityEndedDelegate);

/**
 * 
 */
UCLASS()
class GGJ_API UShadowGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Input")
	FGameplayTag InputTag;

	// 能力结束委托，用于BTTask等待能力完成
	UPROPERTY(BlueprintAssignable, Category = "Ability")
	FOnAbilityEndedDelegate OnAbilityEnded;

	UPROPERTY(BlueprintReadWrite, EditAnywhere,Category="GE")
	TSubclassOf<UGameplayEffect> EnergyEffect;

	UFUNCTION(BlueprintCallable)
	void IncreaseEnergyBar();
protected:
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
};
