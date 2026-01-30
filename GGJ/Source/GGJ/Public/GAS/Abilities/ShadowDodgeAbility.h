// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ShadowGameplayAbility.h"
#include "ShadowDodgeAbility.generated.h"

/**
 * 
 */
UCLASS()
class GGJ_API UShadowDodgeAbility : public UShadowGameplayAbility
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	void Dodge();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite , Category="Shadow")
	UAnimMontage* DodgeMontage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite , Category="Shadow")
	float DodgeDistance;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite , Category="Shadow")
	float DodgeTime;
};
