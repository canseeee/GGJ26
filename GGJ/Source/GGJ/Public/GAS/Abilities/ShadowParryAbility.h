// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ShadowGameplayAbility.h"
#include "ShadowParryAbility.generated.h"

/**
 * 
 */
UCLASS()
class GGJ_API UShadowParryAbility : public UShadowGameplayAbility
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite , Category="Shadow")
	UAnimMontage* ParryMontage;
};
