// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "ShadowInputConfig.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FShadowInputAction
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly)
	const class UInputAction* InputAction = nullptr;

	UPROPERTY(EditDefaultsOnly)
	FGameplayTag InputTag = FGameplayTag();
};

UCLASS()
class GGJ_API UShadowInputConfig : public UDataAsset
{
	GENERATED_BODY()

public:

	const UInputAction* FindInputActionForTag(const FGameplayTag& InputTag, bool bLogNotFound = false)const;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FShadowInputAction> InputActions;
};