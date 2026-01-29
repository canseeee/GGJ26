// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "ShadowAbilitySystemLibrary.generated.h"

/**
 * 
 */
UCLASS()
class GGJ_API UShadowAbilitySystemLibrary : public UAbilitySystemBlueprintLibrary
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable)
	static void AddGameplayTagToASC(UAbilitySystemComponent* ASC, const FGameplayTag GameplayTag);

	UFUNCTION(BlueprintCallable)
	static void RemoveGameplayTagFromASC(UAbilitySystemComponent* ASC, const FGameplayTag GameplayTag);
};
